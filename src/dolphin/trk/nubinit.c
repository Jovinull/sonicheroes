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
extern void usr_put_initialize(void);
extern int TRKInitializeEventQueue(void);
extern int TRKInitializeMessageBuffers(void);
extern int TRKInitializeDispatcher(void);
extern int TRKInitializeIntDrivenUART(u32, u32, u32, volatile u8**);
extern void TRKTargetSetInputPendingPtr(volatile u8*);
extern int TRKInitializeSerialHandler(void);
extern int TRKInitializeTarget(void);

u32 gTRKBigEndian[1];
extern volatile u8* gTRKInputPendingPtr[];

static inline int TRKInitializeEndian(void)
{
	u8 endian[4];
	int result = 0;

	gTRKBigEndian[0] = 1;
	endian[0]        = 0x12;
	endian[1]        = 0x34;
	endian[2]        = 0x56;
	endian[3]        = 0x78;

	if (*(u32*)endian == 0x12345678) {
		gTRKBigEndian[0] = 1;
	} else if (*(u32*)endian == 0x78563412) {
		gTRKBigEndian[0] = 0;
	} else {
		result = 1;
	}
	return result;
}

// Printed once, over whatever link the board support brought up.
void TRKNubWelcome(void)
{
	TRK_board_display("MetroTRK for GAMECUBE v0.10");
}

int TRKTerminateNub(void)
{
	fn_801CA4C0();
	return 0;
}

int TRKInitializeNub(void)
{
	int result;
	int uartResult;

	result = TRKInitializeEndian();

	if (result == 0) {
		usr_put_initialize();
	}
	if (result == 0) {
		result = TRKInitializeEventQueue();
	}
	if (result == 0) {
		result = TRKInitializeMessageBuffers();
	}
	if (result == 0) {
		result = TRKInitializeDispatcher();
	}
	if (result == 0) {
		uartResult = TRKInitializeIntDrivenUART(0xE100, 1, 0, gTRKInputPendingPtr);
		TRKTargetSetInputPendingPtr(gTRKInputPendingPtr[0]);
		if (uartResult != 0) {
			result = uartResult;
		}
	}
	if (result == 0) {
		result = TRKInitializeSerialHandler();
	}
	if (result == 0) {
		result = TRKInitializeTarget();
	}
	return result;
}
