#include "types.h"

// The drive serves one command at a time, so anything arriving while it is busy
// waits here. Four queues, one per priority, each a circular doubly linked list
// whose head is a sentinel that points at itself when empty.

#define NULL 0
#define TRUE 1
#define FALSE 0

#define DVD_MAX_QUEUE 4

typedef int BOOL;

// Only the first two fields matter to this file; the rest of the block belongs
// to whoever owns the command.
typedef struct DVDCommandBlock {
	struct DVDCommandBlock* next; // 0x00
	struct DVDCommandBlock* prev; // 0x04
} DVDCommandBlock;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

// Eight bytes per entry, not a whole command block. The head only ever needs
// its two links, and the original reserves exactly 0x20 for the four of them.
static DVDCommandBlock WaitingQueue[DVD_MAX_QUEUE];

void __DVDClearWaitingQueue(void)
{
	int i;

	for (i = 0; i < DVD_MAX_QUEUE; i++) {
		DVDCommandBlock* head = &WaitingQueue[i];

		head->next = head;
		head->prev = head;
	}
}

BOOL __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block)
{
	BOOL enabled = OSDisableInterrupts();
	DVDCommandBlock* head = &WaitingQueue[prio];

	head->prev->next = block;
	block->prev      = head->prev;
	block->next      = head;
	head->prev       = block;

	OSRestoreInterrupts(enabled);
	return TRUE;
}

DVDCommandBlock* __DVDPopWaitingQueue(void)
{
	BOOL enabled;
	int  i;
	DVDCommandBlock* tmp;

	// Disabled once around the whole scan, not once per queue. The restore
	// immediately followed by another disable on the found path is the
	// original's shape, not an accident of this rewrite.
	enabled = OSDisableInterrupts();

	for (i = 0; i < DVD_MAX_QUEUE; i++) {
		if (WaitingQueue[i].next != &WaitingQueue[i]) {
			OSRestoreInterrupts(enabled);

			enabled = OSDisableInterrupts();
			tmp     = WaitingQueue[i].next;

			WaitingQueue[i].next = tmp->next;
			tmp->next->prev      = &WaitingQueue[i];
			OSRestoreInterrupts(enabled);

			tmp->next = NULL;
			tmp->prev = NULL;
			return tmp;
		}
	}

	OSRestoreInterrupts(enabled);
	return NULL;
}

BOOL __DVDCheckWaitingQueue(void)
{
	BOOL enabled = OSDisableInterrupts();
	int  i;

	for (i = 0; i < DVD_MAX_QUEUE; i++) {
		if (WaitingQueue[i].next != &WaitingQueue[i]) {
			OSRestoreInterrupts(enabled);
			return TRUE;
		}
	}

	OSRestoreInterrupts(enabled);
	return FALSE;
}

BOOL __DVDDequeueWaitingQueue(DVDCommandBlock* block)
{
	BOOL enabled = OSDisableInterrupts();
	DVDCommandBlock* prev = block->prev;
	DVDCommandBlock* next = block->next;

	if (prev == NULL || next == NULL) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	prev->next = next;
	next->prev = prev;

	OSRestoreInterrupts(enabled);
	return TRUE;
}
