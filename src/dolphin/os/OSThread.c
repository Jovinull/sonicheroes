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
// Six of the twenty one functions match. The other fifteen are not written yet
// rather than written and failing, and nothing here is a transcription.

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

typedef struct OSMutexQueue {
	void* head; // 0x0
	void* tail; // 0x4
} OSMutexQueue; // 0x8

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
	void* mutex;             // 0x2F0
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
#else
extern OSThread* __OSCurrentThread;
#endif

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
