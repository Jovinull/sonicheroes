#include "types.h"

// The debugger nub's event queue.
//
// Built with GC/1.3.2 like the rest of TRK, not with the 1.2.5n the Dolphin SDK
// uses. See the TRK entry in configure.py.
//
// The translation unit runs from TRKNubMainLoop at 0x801C9418 to 0x801C9738,
// where nubinit.c starts. The six functions in that range add up to exactly
// 0x320 bytes, which is the whole span, so nothing else belongs here. What sits
// before it is a run of thin float wrappers that ends at 0x801C9418 and is a
// different file.
//
// Functions are in the order the original emits them.

// One queued event. Only the fields the written functions touch are named.
typedef struct TRKEvent {
	u8 type;    // 0x00
	u8 pad[3];  // 0x01
	u32 unk04;  // 0x04
	int buffer; // 0x08, a buffer handle, minus one when there is none
} TRKEvent;

typedef struct TRKEventQueue {
	u8 mutex[4];
	int count;
	int next;
	TRKEvent events[2];
	u32 eventID;
} TRKEventQueue;

typedef enum DSError {
	kNoError        = 0,
	kEventQueueFull = 0x100,
} DSError;

// The queue itself, 0x28 bytes in .bss. The three helpers below take its
// address and are small enough to be lock or list primitives.
TRKEventQueue lbl_803EE0C8;

extern void fn_801CDAD4(void* queue);
extern void fn_801CDADC(void* queue);
extern void fn_801CDAE4(void* queue);
extern void fn_801CA2F4(int buffer);
extern void* fn_80003268(void* dst, const void* src, u32 size);

extern void* TRKGetBuffer(int buffer);
extern void TRKDispatchMessage(void* buffer);
extern void TRKTargetInterrupt(TRKEvent* event);
extern void TRKTargetSupportRequest(void);
extern void TRKGetInput(void);
extern int TRKTargetStopped(void);
extern void TRKTargetContinue(void);
extern volatile u8* gTRKInputPendingPtr[];

int TRKGetNextEvent(TRKEvent* event);
void TRKDestructEvent(TRKEvent* event);

void TRKNubMainLoop(void)
{
	TRKEvent event;
	int done           = 0;
	int inputActivated = 0;

	while (done == 0) {
		if (TRKGetNextEvent(&event) != 0) {
			inputActivated = 0;
			switch (event.type) {
				case 2:
					TRKDispatchMessage(TRKGetBuffer(event.buffer));
					break;
				case 1:
					done = 1;
					break;
				case 3:
				case 4:
					TRKTargetInterrupt(&event);
					break;
				case 5:
					TRKTargetSupportRequest();
					break;
				case 0:
				default:
					break;
			}
			TRKDestructEvent(&event);
		} else if (inputActivated == 0 || *gTRKInputPendingPtr[0] != 0) {
			inputActivated = 1;
			TRKGetInput();
		} else {
			if (TRKTargetStopped() == 0) {
				TRKTargetContinue();
			}
			inputActivated = 0;
		}
	}
}

// Hands the event's buffer back. The event itself is not freed: it belongs to
// the queue and gets reused.
void TRKDestructEvent(TRKEvent* event)
{
	fn_801CA2F4(event->buffer);
}

// Puts an event back into its empty state, with no buffer attached.
void fn_801C9534(TRKEvent* event, u8 type)
{
	event->type   = type;
	event->unk04  = 0;
	event->buffer = -1;
}

DSError fn_801C954C(TRKEvent* event)
{
	DSError result = kNoError;
	int slot;

	fn_801CDADC(&lbl_803EE0C8);
	if (lbl_803EE0C8.count == 2) {
		result = kEventQueueFull;
	} else {
		slot = (lbl_803EE0C8.next + lbl_803EE0C8.count) % 2;
		fn_80003268(&lbl_803EE0C8.events[slot], event, sizeof(TRKEvent));
		lbl_803EE0C8.events[slot].unk04 = lbl_803EE0C8.eventID;
		lbl_803EE0C8.eventID++;
		if (lbl_803EE0C8.eventID < 0x100) {
			lbl_803EE0C8.eventID = 0x100;
		}
		lbl_803EE0C8.count++;
	}
	fn_801CDAD4(&lbl_803EE0C8);
	return result;
}

int TRKGetNextEvent(TRKEvent* event)
{
	int result = 0;

	fn_801CDADC(&lbl_803EE0C8);
	if (lbl_803EE0C8.count > 0) {
		fn_80003268(event, &lbl_803EE0C8.events[lbl_803EE0C8.next], sizeof(TRKEvent));
		lbl_803EE0C8.count--;
		lbl_803EE0C8.next++;
		if (lbl_803EE0C8.next == 2) {
			lbl_803EE0C8.next = 0;
		}
		result = 1;
	}
	fn_801CDAD4(&lbl_803EE0C8);
	return result;
}

int TRKInitializeEventQueue(void)
{
	fn_801CDAE4(&lbl_803EE0C8);
	fn_801CDADC(&lbl_803EE0C8);

	lbl_803EE0C8.count   = 0;
	lbl_803EE0C8.next    = 0;
	lbl_803EE0C8.eventID = 0x100;

	fn_801CDAD4(&lbl_803EE0C8);

	return 0;
}
