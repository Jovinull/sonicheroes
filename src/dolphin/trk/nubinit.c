#include "types.h"

// Bringing the debugger nub up and taking it down. WORK IN PROGRESS: two
// functions are written, TRKInitializeNub is still assembly in the build.
//
// Built with GC/1.3.2 like the rest of TRK, not with the 1.2.5n the Dolphin SDK
// uses. See the TRK entry in configure.py.
//
// The translation unit runs from TRKNubWelcome at 0x801C9738 to 0x801C98B8.
// Before it is the event queue file, which ends with TRKInitializeEventQueue.
// It owns the banner string in .rodata at 0x8023D340.
//
// TRKNubWelcome reads as 99 percent rather than 100, and the missing percent is
// not code. Both instructions that reference the banner are identical; what
// differs is the name of the symbol they point at. dtk numbers anonymous
// rodata across the whole DOL and calls this one @62, while the compiler
// numbers literals within one object and calls ours @5. Nothing written here
// can reconcile those two counters.
//
// Functions are in the order the original emits them.

extern void TRK_board_display(const char* msg);
extern void fn_801CA4C0(void);

// Printed once, over whatever link the board support brought up.
void TRKNubWelcome(void) { TRK_board_display("MetroTRK for GAMECUBE v0.10"); }

int TRKTerminateNub(void)
{
	fn_801CA4C0();
	return 0;
}

// TRKInitializeNub belongs here, still unwritten.
