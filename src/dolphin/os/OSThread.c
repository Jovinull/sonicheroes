#include "dolphin/os.h"

// The thread scheduler. Sits between OSSync and OSTime in the DOL and owns the
// run queue the whole system schedules against.
//
// The translation unit runs from the switch callback at 0x801D6310 to the end
// of OSClearStack at 0x801D75A8. The bound is read rather than argued: the
// range is bracketed by two units that were already placed, OSSync.c ending at
// 0x801D6310 and OSTime.c starting at 0x801D75A8, and every data symbol in it
// is one the Dolphin SDK's OSThread.c is known to own. RunQueue is 0x100 bytes
// at 0x803F23B8, which is the thirty two eight byte queues of OS_PRIORITY_MAX,
// and RunQueueBits, RunQueueHint and Reschedule sit together in .sbss at
// 0x8042CB98 with SwitchThreadCallback alone in .sdata at 0x8042BF48.
//
// Names here are the SDK's, not dtk's, because this file is stock Dolphin and
// the symbol table already spelled ten of the twenty one entry points. Three
// more are named here from what they do: the four byte function at 0x801D6310
// is what SwitchThreadCallback is initialised to, 0x801D647C hands back
// __OSCurrentThread, and 0x801D74F4 hands back a thread's base priority. The
// rest keep their fn_ names until there is a reason to change them.
//
// OSThread and OSThreadQueue are declared here rather than in
// include/dolphin/os.h because dvd.c and dvdfs.c each carry their own copy of
// OSThreadQueue already. Moving all three into the header is the right end
// state, and is what the header's own note about OSContext asks for, but it
// means editing those two units, so it is left for a change that does only
// that.
//
// Ten of the twenty one functions match. Five more are written and close:
// OSWakeupThread at 97%, SetEffectivePriority at 96%, OSExitThread at 94%,
// OSSleepThread at 93% and OSSetThreadPriority at 91%. Six are not written.
//
// The unit is built with -inline noauto, like Pad.c. Under -inline auto the
// compiler folds __OSGetEffectivePriority, OSWakeupThread and UnsetRun into
// their callers where the original emits bl, and that alone cost forty points
// on SetEffectivePriority and fifty on OSExitThread. What the original does
// expand is SetRun, AddPrio and the reschedule test, so those carry the inline
// keyword instead. The reschedule test is spelled as DoReschedule because the
// original expands it at every call site inside the unit while still emitting
// __OSReschedule for the units that call it from outside; making the exported
// function the helper's out of line body is what produces both.
//
// AddPrio's walk has to be a while loop with the test in its condition. Written
// as a for loop with a break the compiler hoists thread->priority out, and the
// original reloads it every iteration.
//
//
// UnsetRun and __OSGetEffectivePriority are named from what they do, and the
// second of them is where the OSMutex layout above comes from: it walks a
// thread's held mutexes through a link at 0x10 and reads each one's waiting
// queue at 0x0.

typedef s32 OSPriority;

typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
	OSThread* head; // 0x0
	OSThread* tail; // 0x4
} OSThreadQueue;    // 0x8

typedef struct OSThreadLink {
	OSThread* next; // 0x0
	OSThread* prev; // 0x4
} OSThreadLink;     // 0x8

typedef struct OSMutex OSMutex;

typedef struct OSMutexQueue {
	OSMutex* head; // 0x0
	OSMutex* tail; // 0x4
} OSMutexQueue;    // 0x8

typedef struct OSMutexLink {
	OSMutex* next; // 0x0
	OSMutex* prev; // 0x4
} OSMutexLink;     // 0x8

// Read out of __OSGetEffectivePriority, which walks a thread's held mutexes
// through 0x10 and reads each one's waiting queue at 0x0.
struct OSMutex {
	OSThreadQueue queue; // 0x00
	OSThread* thread;    // 0x08
	s32 count;           // 0x0C
	OSMutexLink link;    // 0x10
}; // 0x18

struct OSThread {
	OSContext context;       // 0x000
	u16 state;               // 0x2C8
	u16 attr;                // 0x2CA
	s32 suspend;             // 0x2CC
	OSPriority priority;     // 0x2D0 the priority it runs at right now
	OSPriority base;         // 0x2D4 the priority it was created with
	void* val;               // 0x2D8
	OSThreadQueue* queue;    // 0x2DC
	OSThreadLink link;       // 0x2E0
	OSThreadQueue queueJoin; // 0x2E8
	OSMutex* mutex;          // 0x2F0
	OSMutexQueue queueMutex; // 0x2F4
	OSThreadLink linkActive; // 0x2FC
	u8* stackBase;           // 0x304
	u32* stackEnd;           // 0x308
	s32 error;               // 0x30C
	void* specific[2];       // 0x310
}; // 0x318

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

#ifdef __MWERKS__
extern OSThread* __OSCurrentThread : 0x800000E4;
extern OSThreadQueue __OSActiveThreadQueue : 0x800000DC;
#else
extern OSThread* __OSCurrentThread;
extern OSThreadQueue __OSActiveThreadQueue;
#endif

extern void __OSUnlockAllMutex(OSThread* thread);

static void SelectThread(BOOL yield);

// Replaced by OSSetSwitchThreadCallback and called on every context switch.
// Does nothing until the debugger nub installs its own.
static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to) { }

// The run queue proper: one list per priority, with a bitmap and a hint so the
// scheduler does not have to walk all thirty two to find the highest ready.
static OSThreadQueue RunQueue[32]; // 0x803F23B8
static u32 RunQueueBits;           // 0x8042CB98
static BOOL RunQueueHint;          // 0x8042CB9C
static s32 Reschedule;             // 0x8042CBA0

// In .sdata rather than .sbss, so it is initialised non-zero: it starts out
// pointing at the do-nothing callback below.
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback; // 0x8042BF48

void OSInitThreadQueue(OSThreadQueue* queue)
{
	queue->head = queue->tail = NULL;
}

OSThread* OSGetCurrentThread(void)
{
	return __OSCurrentThread;
}

// Counts up, so nested disables need matching enables. Both of these hand back
// the count as it was before the change, not after.
s32 OSDisableScheduler(void)
{
	BOOL enabled;
	s32 count;

	enabled = OSDisableInterrupts();
	count   = Reschedule++;
	OSRestoreInterrupts(enabled);

	return count;
}

s32 OSEnableScheduler(void)
{
	BOOL enabled;
	s32 count;

	enabled = OSDisableInterrupts();
	count   = Reschedule--;
	OSRestoreInterrupts(enabled);

	return count;
}

OSPriority OSGetThreadPriority(OSThread* thread)
{
	return thread->base;
}

// Takes a thread off whichever queue it is on. Clearing the last thread at a
// priority also clears that priority's bit in the run queue bitmap.
static void UnsetRun(OSThread* thread)
{
	OSThreadQueue* queue;
	OSThread* next;
	OSThread* prev;

	queue = thread->queue;
	next  = thread->link.next;
	prev  = thread->link.prev;

	if (next == NULL) {
		queue->tail = prev;
	} else {
		next->link.prev = prev;
	}
	if (prev == NULL) {
		queue->head = next;
	} else {
		prev->link.next = next;
	}
	if (queue->head == NULL) {
		RunQueueBits &= ~(1 << (31 - thread->priority));
	}
	thread->queue = NULL;
}

// A thread runs at the highest priority among its own and those of the threads
// waiting on the mutexes it holds, which is what stops priority inversion.
static OSPriority __OSGetEffectivePriority(OSThread* thread)
{
	OSPriority priority;
	OSMutex* mutex;

	priority = thread->base;
	for (mutex = thread->queueMutex.head; mutex != NULL; mutex = mutex->link.next) {
		OSThread* blocked = mutex->queue.head;
		if (blocked != NULL && blocked->priority < priority) {
			priority = blocked->priority;
		}
	}
	return priority;
}

// Paints the unused part of the current thread's stack with a byte, from the
// stack's end up to wherever the stack pointer is now.
void OSClearStack(u8 val)
{
	u32 pattern;
	u32* p;
	u32* stackEnd;

	pattern  = (val << 24) | (val << 16) | (val << 8) | val;
	p        = (u32*)OSGetStackPointer();
	stackEnd = __OSCurrentThread->stackEnd + 1;
	while (stackEnd < p) {
		*stackEnd++ = pattern;
	}
}

// Thread states, read off the switch in SetEffectivePriority.
#define OS_THREAD_STATE_READY    1
#define OS_THREAD_STATE_RUNNING  2
#define OS_THREAD_STATE_WAITING  4
#define OS_THREAD_STATE_MORIBUND 8

// Bit 0 of attr, read off the test in OSExitThread.
#define OS_THREAD_ATTR_DETACHED 1

// Puts a thread on its priority's run queue and marks that priority ready.
// Written through thread->queue rather than a local, which is what makes the
// compiler read the queue back between the field stores.
static inline void SetRun(OSThread* thread)
{
	OSThread* tail;

	thread->queue = &RunQueue[thread->priority];

	tail = thread->queue->tail;
	if (tail == NULL) {
		thread->queue->head = thread;
	} else {
		tail->link.next = thread;
	}
	thread->link.prev   = tail;
	thread->link.next   = NULL;
	thread->queue->tail = thread;

	RunQueueBits |= 1 << (31 - thread->priority);
	RunQueueHint = TRUE;
}

// Inserts a thread into a queue kept in priority order, ahead of the first
// entry that is strictly lower priority.
static inline void AddPrio(OSThreadQueue* queue, OSThread* thread)
{
	OSThread* after;
	OSThread* prev;

	after = queue->head;
	while (after != NULL && after->priority <= thread->priority) {
		after = after->link.next;
	}

	if (after == NULL) {
		prev = queue->tail;
		if (prev == NULL) {
			queue->head = thread;
		} else {
			prev->link.next = thread;
		}
		thread->link.prev = prev;
		thread->link.next = NULL;
		queue->tail       = thread;
	} else {
		thread->link.next = after;
		prev              = after->link.prev;
		after->link.prev  = thread;
		thread->link.prev = prev;
		if (prev == NULL) {
			queue->head = thread;
		} else {
			prev->link.next = thread;
		}
	}
}

// Moves a thread to a new priority. A ready thread changes run queue, a
// waiting one is re-sorted where it waits, and a running one only sets the
// hint so the next reschedule picks it up. Returns the thread holding the
// mutex this one is blocked on, so the caller can walk the chain.
static OSThread* SetEffectivePriority(OSThread* thread, OSPriority priority)
{
	switch (thread->state) {
		case OS_THREAD_STATE_READY:
			UnsetRun(thread);
			thread->priority = priority;
			SetRun(thread);
			break;

		case OS_THREAD_STATE_WAITING: {
			OSThread* next = thread->link.next;
			OSThread* prev = thread->link.prev;

			if (next == NULL) {
				thread->queue->tail = prev;
			} else {
				next->link.prev = prev;
			}
			if (prev == NULL) {
				thread->queue->head = next;
			} else {
				prev->link.next = next;
			}

			thread->priority = priority;
			AddPrio(thread->queue, thread);
			if (thread->mutex != NULL) {
				return thread->mutex->thread;
			}
			break;
		}

		case OS_THREAD_STATE_RUNNING:
			RunQueueHint     = TRUE;
			thread->priority = priority;
			break;
	}

	return NULL;
}

// The original expands this test at every call site inside the unit while
// still emitting the copy other units call, so it is spelled once as an inline
// helper and __OSReschedule is that helper's out of line body.
static inline void DoReschedule(void)
{
	if (RunQueueHint) {
		SelectThread(FALSE);
	}
}

void __OSReschedule(void)
{
	DoReschedule();
}

// Blocks the current thread on a queue until someone wakes it.
void OSSleepThread(OSThreadQueue* queue)
{
	BOOL enabled;
	OSThread* thread;

	enabled = OSDisableInterrupts();

	thread        = __OSCurrentThread;
	thread->state = OS_THREAD_STATE_WAITING;
	thread->queue = queue;
	AddPrio(queue, thread);

	RunQueueHint = TRUE;
	DoReschedule();

	OSRestoreInterrupts(enabled);
}

// Wakes every thread on a queue, not just the head. A suspended one becomes
// ready without being put back on the run queue.
void OSWakeupThread(OSThreadQueue* queue)
{
	BOOL enabled;
	OSThread* thread;

	enabled = OSDisableInterrupts();

	while ((thread = queue->head) != NULL) {
		OSThread* next = thread->link.next;
		if (next == NULL) {
			queue->tail = NULL;
		} else {
			next->link.prev = NULL;
		}
		queue->head = next;

		thread->state = OS_THREAD_STATE_READY;
		if (thread->suspend <= 0) {
			SetRun(thread);
		}
	}

	DoReschedule();

	OSRestoreInterrupts(enabled);
}

// Ends the current thread. A detached thread leaves the active list and its
// state goes to zero; an attached one stays there as moribund so whoever joins
// it can still read the value it exited with.
void OSExitThread(void* val)
{
	BOOL enabled;
	OSThread* thread;

	enabled = OSDisableInterrupts();
	thread  = __OSCurrentThread;
	OSClearContext(&thread->context);

	if (thread->attr & OS_THREAD_ATTR_DETACHED) {
		OSThread* next = thread->linkActive.next;
		OSThread* prev = thread->linkActive.prev;

		if (next == NULL) {
			__OSActiveThreadQueue.tail = prev;
		} else {
			next->linkActive.prev = prev;
		}
		if (prev == NULL) {
			__OSActiveThreadQueue.head = next;
		} else {
			prev->linkActive.next = next;
		}
		thread->state = 0;
	} else {
		thread->state = OS_THREAD_STATE_MORIBUND;
	}

	thread->val = val;
	__OSUnlockAllMutex(thread);
	OSWakeupThread(&thread->queueJoin);

	RunQueueHint = TRUE;
	DoReschedule();

	OSRestoreInterrupts(enabled);
}

// Changes a thread's base priority. Raising it can unblock the thread holding
// a mutex this one waits on, so the walk follows that chain until it runs out.
BOOL OSSetThreadPriority(OSThread* thread, OSPriority priority)
{
	BOOL enabled;

	if (priority < 0 || priority > 31) {
		return FALSE;
	}

	enabled = OSDisableInterrupts();
	if (thread->base != priority) {
		thread->base = priority;
		while (thread != NULL) {
			OSPriority effective;

			if (thread->suspend > 0) {
				break;
			}
			effective = __OSGetEffectivePriority(thread);
			if (thread->priority == effective) {
				break;
			}
			thread = SetEffectivePriority(thread, effective);
		}
		DoReschedule();
	}
	OSRestoreInterrupts(enabled);

	return TRUE;
}
