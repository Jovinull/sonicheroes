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

#define ENQUEUE_THREAD(thread, queue, member)                                                      \
	do {                                                                                           \
		OSThread* prev = (queue)->tail;                                                            \
		if (prev == NULL) {                                                                        \
			(queue)->head = (thread);                                                              \
		} else {                                                                                   \
			prev->member.next = (thread);                                                          \
		}                                                                                          \
		(thread)->member.prev = prev;                                                              \
		(thread)->member.next = NULL;                                                              \
		(queue)->tail         = (thread);                                                          \
	} while (0)

#define DEQUEUE_THREAD(thread, queue, member)                                                      \
	do {                                                                                           \
		OSThread* next = (thread)->member.next;                                                    \
		OSThread* prev = (thread)->member.prev;                                                    \
		if (next == NULL) {                                                                        \
			(queue)->tail = prev;                                                                  \
		} else {                                                                                   \
			next->member.prev = prev;                                                              \
		}                                                                                          \
		if (prev == NULL) {                                                                        \
			(queue)->head = next;                                                                  \
		} else {                                                                                   \
			prev->member.next = next;                                                              \
		}                                                                                          \
	} while (0)

#define ENQUEUE_THREAD_PRIO(thread, queue, member)                                                 \
	do {                                                                                           \
		OSThread* prev;                                                                            \
		OSThread* next;                                                                            \
		for (next = (queue)->head; next != NULL && next->priority <= (thread)->priority;           \
		    next  = next->member.next) {                                                           \
		}                                                                                          \
		if (next == NULL) {                                                                        \
			ENQUEUE_THREAD(thread, queue, member);                                                 \
		} else {                                                                                   \
			(thread)->member.next = next;                                                          \
			prev                  = next->member.prev;                                             \
			next->member.prev     = (thread);                                                      \
			(thread)->member.prev = prev;                                                          \
			if (prev == NULL) {                                                                    \
				(queue)->head = (thread);                                                          \
			} else {                                                                               \
				prev->member.next = (thread);                                                      \
			}                                                                                      \
		}                                                                                          \
	} while (0)

#define DEQUEUE_HEAD(thread, queue, member)                                                        \
	do {                                                                                           \
		OSThread* next = (thread)->member.next;                                                    \
		if (next == NULL) {                                                                        \
			(queue)->tail = NULL;                                                                  \
		} else {                                                                                   \
			next->member.prev = NULL;                                                              \
		}                                                                                          \
		(queue)->head = next;                                                                      \
	} while (0)

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

#ifdef __MWERKS__
extern OSThread* __OSCurrentThread : 0x800000E4;
extern OSThread* __OSActiveThreadQueueData[2] : 0x800000DC;
#define OS_ACTIVE_QUEUE (*(OSThreadQueue*)__OSActiveThreadQueueData)
#else
extern OSThread* __OSCurrentThread;
extern OSThreadQueue __OSActiveThreadQueue;
#define OS_ACTIVE_QUEUE __OSActiveThreadQueue
#endif

// Replaced by OSSetSwitchThreadCallback and called on every context switch.
// Does nothing until the debugger nub installs its own.
static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to) { }

// The run queue proper: one list per priority, with a bitmap and a hint so the
// scheduler does not have to walk all thirty two to find the highest ready.
static OSThreadQueue RunQueue[32]; // 0x803F23B8
static OSThread IdleThread;
static OSThread DefaultThread;
static OSContext IdleContext;
static volatile u32 RunQueueBits;  // 0x8042CB98
static volatile BOOL RunQueueHint; // 0x8042CB9C
static volatile s32 Reschedule;    // 0x8042CBA0

// In .sdata rather than .sbss, so it is initialised non-zero: it starts out
// pointing at the do-nothing callback below.
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback; // 0x8042BF48

extern u8 _stack_addr[];
extern u8 _stack_end[];
extern OSContext* OSGetCurrentContext(void);
extern u32 OSSaveContext(OSContext* context);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern void OSLoadContext(OSContext* context);
extern void OSInitContext(OSContext* context, void* pc, void* stack);
extern void __OSUnlockAllMutex(OSThread* thread);
typedef void (*OSErrorHandler)(u16 error, OSContext* context, ...);
extern OSErrorHandler __OSErrorTable[];
extern u32 __OSFpscrEnableBits;
void OSInitThreadQueue(OSThreadQueue* queue);
void OSClearStack(u8 val);
void fn_801D6BAC(void* val);
void OSWakeupThread(OSThreadQueue* queue);

void __OSThreadInit(void)
{
	OSThread* thread = &DefaultThread;
	s32 priority;

	thread->state    = 2;
	thread->attr     = 1;
	thread->priority = thread->base = 16;
	thread->suspend                 = 0;
	thread->val                     = (void*)-1;
	thread->mutex                   = NULL;
	OSInitThreadQueue(&thread->queueJoin);
	thread->queueMutex.head = thread->queueMutex.tail = NULL;

	*(OSContext**)0x800000D8 = &thread->context;
	OSClearContext(&thread->context);
	OSSetCurrentContext(&thread->context);

	thread->stackBase = _stack_addr;
	thread->stackEnd  = (u32*)_stack_end;
	*thread->stackEnd = 0xDEADBABE;

	SwitchThreadCallback(__OSCurrentThread, thread);
	__OSCurrentThread = thread;
	OSClearStack(0);

	RunQueueBits = 0;
	RunQueueHint = FALSE;
	for (priority = 0; priority <= 31; priority++) {
		OSInitThreadQueue(&RunQueue[priority]);
	}

	OSInitThreadQueue(&OS_ACTIVE_QUEUE);
	ENQUEUE_THREAD(thread, &OS_ACTIVE_QUEUE, linkActive);
	OSClearContext(&IdleContext);
	Reschedule = 0;
}

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

static inline void SetRun(OSThread* thread)
{
	thread->queue = &RunQueue[thread->priority];
	ENQUEUE_THREAD(thread, thread->queue, link);
	RunQueueBits |= 1 << (31 - thread->priority);
	RunQueueHint = TRUE;
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

static inline OSPriority GetEffectivePriorityInline(OSThread* thread)
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

OSThread* fn_801D65AC(OSThread* thread, OSPriority priority)
{
	switch (thread->state) {
		case 1:
			UnsetRun(thread);
			thread->priority = priority;
			SetRun(thread);
			break;
		case 4:
			DEQUEUE_THREAD(thread, thread->queue, link);
			thread->priority = priority;
			ENQUEUE_THREAD_PRIO(thread, thread->queue, link);
			if (thread->mutex != NULL) {
				return thread->mutex->thread;
			}
			break;
		case 2:
			RunQueueHint     = TRUE;
			thread->priority = priority;
			break;
	}
	return NULL;
}

static OSThread* SelectThread(BOOL yield)
{
	OSContext* currentContext;
	OSThread* currentThread;
	OSThread* nextThread;
	OSPriority priority;
	OSThreadQueue* queue;
	OSContext* context;

	if (Reschedule > 0) {
		return NULL;
	}

	currentContext = OSGetCurrentContext();
	currentThread  = __OSCurrentThread;
	context        = &currentThread->context;
	if (currentContext != context) {
		return NULL;
	}

	if (currentThread != NULL) {
		if (currentThread->state == 2) {
			if (yield == FALSE) {
				priority = __cntlzw(RunQueueBits);
				if (currentThread->priority <= priority) {
					return NULL;
				}
			}
			currentThread->state = 1;
			SetRun(currentThread);
		}
		if (!(currentThread->context.state & 2) && OSSaveContext(context) != 0) {
			return NULL;
		}
	}

	if (RunQueueBits == 0) {
		SwitchThreadCallback(__OSCurrentThread, NULL);
		__OSCurrentThread = NULL;
		OSSetCurrentContext(&IdleContext);
		do {
			OSEnableInterrupts();
			while (RunQueueBits == 0) {
			}
			OSDisableInterrupts();
		} while (RunQueueBits == 0);
		OSClearContext(&IdleContext);
	}

	RunQueueHint = FALSE;
	priority     = __cntlzw(RunQueueBits);
	queue        = &RunQueue[priority];
	nextThread   = queue->head;
	DEQUEUE_HEAD(nextThread, queue, link);
	if (queue->head == NULL) {
		RunQueueBits &= ~(1 << (31 - priority));
	}
	nextThread->queue = NULL;
	nextThread->state = 2;

	SwitchThreadCallback(__OSCurrentThread, nextThread);
	__OSCurrentThread = nextThread;
	OSSetCurrentContext(&nextThread->context);
	OSLoadContext(&nextThread->context);
	return nextThread;
}

#pragma inline auto
void __OSReschedule(void)
{
	if (RunQueueHint) {
		SelectThread(FALSE);
	}
}

#define RESCHEDULE()                                                                               \
	do {                                                                                           \
		if (RunQueueHint) {                                                                        \
			SelectThread(FALSE);                                                                   \
		}                                                                                          \
	} while (0)

static inline void UpdatePriority(OSThread* thread)
{
	OSPriority priority;

	do {
		if (thread->suspend > 0) {
			break;
		}
		priority = __OSGetEffectivePriority(thread);
		if (thread->priority == priority) {
			break;
		}
		thread = fn_801D65AC(thread, priority);
	} while (thread != NULL);
}

BOOL fn_801D69C4(OSThread* thread_, void* func, void* param, void* stackBase, u32 stackSize,
    OSPriority priority, u16 attr)
{
	BOOL enabled;
	u32 i;
	u32* stack;
	OSThread* thread;
	u32 stack1;
	u32 stack2;

	if (priority < 0 || priority > 31) {
		return FALSE;
	}

	thread                  = thread_;
	thread->state           = 1;
	thread->attr            = attr & 1;
	thread->base            = priority;
	thread->priority        = priority;
	thread->suspend         = 1;
	thread->val             = (void*)-1;
	thread->mutex           = NULL;
	thread->queueJoin.tail  = NULL;
	thread->queueJoin.head  = NULL;
	thread->queueMutex.tail = NULL;
	thread->queueMutex.head = NULL;
	stack                   = (u32*)((u32)stackBase & 0xFFFFFFF8);
	stack[-2]               = 0;
	stack[-1]               = 0;
	OSInitContext(&thread->context, func, stack - 2);
	thread->context.lr     = (u32)fn_801D6BAC;
	thread->context.gpr[3] = (u32)param;
	thread->stackBase      = stackBase;
	thread->stackEnd       = (u32*)((u32)stackBase - stackSize);
	*thread->stackEnd      = 0xDEADBABE;
	thread->error          = 0;
	thread->specific[0]    = NULL;
	thread->specific[1]    = NULL;

	enabled = OSDisableInterrupts();
	if (__OSErrorTable[16] != NULL) {
		thread->context.srr1 |= 0x900;
		thread->context.state |= 1;
		thread->context.fpscr = (__OSFpscrEnableBits & 0xF8) | 4;
		for (i = 0; i < 32; i++) {
			*(u64*)&thread->context.fpr[i] = 0xFFFFFFFFFFFFFFFF;
			*(u64*)&thread->context.psf[i] = 0xFFFFFFFFFFFFFFFF;
		}
	}
	{
		OSThread** link;
		OSThread* prev;

		link = __OSActiveThreadQueueData;
		prev = *++link;
		if (prev == NULL) {
			__OSActiveThreadQueueData[0] = thread;
		} else {
			prev->linkActive.next = thread;
		}
		thread->linkActive.prev = prev;
		thread->linkActive.next = NULL;
		*link                   = thread;
	}
	OSRestoreInterrupts(enabled);
	return TRUE;
}

void fn_801D6BAC(void* val)
{
	OSThread* thread;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	thread  = __OSCurrentThread;
	OSClearContext(&thread->context);

	if (thread->attr & 1) {
		DEQUEUE_THREAD(thread, &OS_ACTIVE_QUEUE, linkActive);
		thread->state = 0;
	} else {
		thread->state = 8;
		thread->val   = val;
	}
	__OSUnlockAllMutex(thread);
	OSWakeupThread(&thread->queueJoin);
	RunQueueHint = TRUE;
	if (RunQueueHint) {
		SelectThread(FALSE);
	}
	OSRestoreInterrupts(enabled);
}

void OSCancelThread(OSThread* thread)
{
	BOOL enabled;

	enabled = OSDisableInterrupts();
	switch (thread->state) {
		case 1:
			if (thread->suspend <= 0) {
				UnsetRun(thread);
			}
			break;
		case 2:
			RunQueueHint = TRUE;
			break;
		case 4:
			DEQUEUE_THREAD(thread, thread->queue, link);
			thread->queue = NULL;
			if (thread->suspend <= 0 && thread->mutex != NULL) {
				UpdatePriority(thread->mutex->thread);
			}
			break;
		default:
			OSRestoreInterrupts(enabled);
			return;
	}

	OSClearContext(&thread->context);
	if (thread->attr & 1) {
		DEQUEUE_THREAD(thread, &OS_ACTIVE_QUEUE, linkActive);
		thread->state = 0;
	} else {
		thread->state = 8;
	}
	__OSUnlockAllMutex(thread);
	OSWakeupThread(&thread->queueJoin);
	RESCHEDULE();
	OSRestoreInterrupts(enabled);
}

s32 fn_801D6E4C(OSThread* thread)
{
	BOOL enabled;
	s32 suspend;

	enabled = OSDisableInterrupts();
	suspend = thread->suspend--;
	if (thread->suspend < 0) {
		thread->suspend = 0;
	} else if (thread->suspend == 0) {
		switch (thread->state) {
			case 1:
				thread->priority = GetEffectivePriorityInline(thread);
				SetRun(thread);
				break;
			case 4:
				DEQUEUE_THREAD(thread, thread->queue, link);
				thread->priority = GetEffectivePriorityInline(thread);
				ENQUEUE_THREAD_PRIO(thread, thread->queue, link);
				if (thread->mutex != NULL) {
					UpdatePriority(thread->mutex->thread);
				}
				break;
		}
		RESCHEDULE();
	}
	OSRestoreInterrupts(enabled);
	return suspend;
}

s32 fn_801D70D4(OSThread* thread)
{
	BOOL enabled;
	s32 suspend;

	enabled = OSDisableInterrupts();
	suspend = thread->suspend++;
	if (suspend == 0) {
		switch (thread->state) {
			case 2:
				RunQueueHint  = TRUE;
				thread->state = 1;
				break;
			case 1:
				UnsetRun(thread);
				break;
			case 4:
				DEQUEUE_THREAD(thread, thread->queue, link);
				thread->priority = 32;
				ENQUEUE_THREAD(thread, thread->queue, link);
				if (thread->mutex != NULL) {
					UpdatePriority(thread->mutex->thread);
				}
				break;
		}
		RESCHEDULE();
	}
	OSRestoreInterrupts(enabled);
	return suspend;
}

void OSSleepThread(OSThreadQueue* queue)
{
	BOOL enabled;
	OSThread* thread;

	enabled       = OSDisableInterrupts();
	thread        = __OSCurrentThread;
	thread->state = 4;
	thread->queue = queue;
	ENQUEUE_THREAD_PRIO(thread, queue, link);
	RunQueueHint = TRUE;
	RESCHEDULE();
	OSRestoreInterrupts(enabled);
}

void OSWakeupThread(OSThreadQueue* queue)
{
	BOOL enabled;
	OSThread* thread;

	enabled = OSDisableInterrupts();
	while (queue->head != NULL) {
		thread = queue->head;
		DEQUEUE_HEAD(thread, queue, link);
		thread->state = 1;
		if (thread->suspend <= 0) {
			SetRun(thread);
		}
	}
	RESCHEDULE();
	OSRestoreInterrupts(enabled);
}

s32 fn_801D7434(OSThread* thread, OSPriority priority)
{
	BOOL enabled;

	if (priority < 0 || priority > 31) {
		return FALSE;
	}
	enabled = OSDisableInterrupts();
	if (thread->base != priority) {
		thread->base = priority;
		UpdatePriority(thread);
		RESCHEDULE();
	}
	OSRestoreInterrupts(enabled);
	return TRUE;
}

OSPriority OSGetThreadPriority(OSThread* thread)
{
	return thread->base;
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
