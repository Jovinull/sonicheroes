#include "types.h"

// The debugger nub's event queue. WORK IN PROGRESS: three functions are
// written, three are still assembly in the build.
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
	s32 buffer; // 0x08, a buffer handle, minus one when there is none
} TRKEvent;

// The queue itself, 0x28 bytes in .bss. The three helpers below take its
// address and are small enough to be lock or list primitives.
extern u8 lbl_803EE0C8[];

extern void fn_801CDAD4(void* queue);
extern void fn_801CDADC(void* queue);
extern void fn_801CDAE4(void* queue);
extern void fn_801CA2F4(s32 buffer);

// TRKNubMainLoop belongs here, still unwritten.

// Hands the event's buffer back. The event itself is not freed: it belongs to
// the queue and gets reused.
void TRKDestructEvent(TRKEvent* event)
{
	fn_801CA2F4(event->buffer);
}

// Puts an event back into its empty state, with no buffer attached.
static void fn_801C9534(TRKEvent* event, u8 type)
{
	event->type   = type;
	event->unk04  = 0;
	event->buffer = -1;
}

// fn_801C954C and TRKGetNextEvent belong here, still unwritten.

int TRKInitializeEventQueue(void)
{
	fn_801CDAE4(lbl_803EE0C8);
	fn_801CDADC(lbl_803EE0C8);

	*(u32*)(lbl_803EE0C8 + 0x4)  = 0;
	*(u32*)(lbl_803EE0C8 + 0x8)  = 0;
	*(u32*)(lbl_803EE0C8 + 0x24) = 0x100;

	fn_801CDAD4(lbl_803EE0C8);

	return 0;
}
