#include "types.h"

// DSP bootstrap and halt. The translation unit runs from __OSInitAudioSystem
// at 0x801D1C90 to the end of __OSStopAudioSystem at 0x801D1F24, with the DSP
// init microcode as its .data. Before it is OSArena, after it is OSCache.

typedef u32 OSTick;

#ifdef __MWERKS__
volatile u16 __DSPRegs[] : 0xCC005000;
#else
extern volatile u16 __DSPRegs[];
#endif

extern void* memcpy(void* dst, const void* src, u32 n);
extern void DCFlushRange(void* addr, u32 nBytes);
extern void* OSGetArenaHi(void);
extern OSTick OSGetTick(void);

// The bootstrap the DSP runs once out of reset. These bytes are taken from the
// Dolphin SDK source.
// clang-format off
static u8 DSPInitCode[128] = {
	0x02, 0x9F, 0x00, 0x10, 0x02, 0x9F, 0x00, 0x33, 0x02, 0x9F, 0x00, 0x34, 0x02, 0x9F, 0x00, 0x35,
	0x02, 0x9F, 0x00, 0x36, 0x02, 0x9F, 0x00, 0x37, 0x02, 0x9F, 0x00, 0x38, 0x02, 0x9F, 0x00, 0x39,
	0x12, 0x06, 0x12, 0x03, 0x12, 0x04, 0x12, 0x05, 0x00, 0x80, 0x80, 0x00, 0x00, 0x88, 0xFF, 0xFF,
	0x00, 0x84, 0x10, 0x00, 0x00, 0x64, 0x00, 0x1D, 0x02, 0x18, 0x00, 0x00, 0x81, 0x00, 0x1C, 0x1E,
	0x00, 0x44, 0x1B, 0x1E, 0x00, 0x84, 0x08, 0x00, 0x00, 0x64, 0x00, 0x27, 0x19, 0x1E, 0x00, 0x00,
	0x00, 0xDE, 0xFF, 0xFC, 0x02, 0xA0, 0x80, 0x00, 0x02, 0x9C, 0x00, 0x28, 0x16, 0xFC, 0x00, 0x54,
	0x16, 0xFD, 0x43, 0x48, 0x00, 0x21, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF,
	0x02, 0xFF, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on

void __OSInitAudioSystem(void)
{
	u32 tick;
	u16 status;
	u32 padding;

	memcpy((u8*)OSGetArenaHi() - 0x80, (void*)0x81000000, 0x80);
	memcpy((void*)0x81000000, DSPInitCode, 0x80);
	DCFlushRange((void*)0x81000000, 0x80);

	__DSPRegs[9] = 0x43;
	__DSPRegs[5] = 0x8AC;
	__DSPRegs[5] |= 1;
	while (__DSPRegs[5] & 1) {
	}

	__DSPRegs[0] = 0;
	while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000) {
	}

	*(u32*)&__DSPRegs[16] = 0x01000000;
	*(u32*)&__DSPRegs[18] = 0;
	*(u32*)&__DSPRegs[20] = 0x20;

	status = __DSPRegs[5];
	while (!(status & 0x20)) {
		status = __DSPRegs[5];
	}
	__DSPRegs[5] = status;

	tick = OSGetTick();
	while ((s32)(OSGetTick() - tick) < 0x892) {
	}

	*(u32*)&__DSPRegs[16] = 0x01000000;
	*(u32*)&__DSPRegs[18] = 0;
	*(u32*)&__DSPRegs[20] = 0x20;

	status = __DSPRegs[5];
	while (!(status & 0x20)) {
		status = __DSPRegs[5];
	}
	__DSPRegs[5] = status;

	__DSPRegs[5] &= ~0x800;
	while (__DSPRegs[5] & 0x400) {
	}
	__DSPRegs[5] &= ~4;

	status = __DSPRegs[2];
	while (!(status & 0x8000)) {
		status = __DSPRegs[2];
	}
	(void)__DSPRegs[3];
	(void)(status != 42069);
	__DSPRegs[5] |= 4;

	__DSPRegs[5] = 0x8AC;
	__DSPRegs[5] |= 1;
	while (__DSPRegs[5] & 1) {
	}

	memcpy((void*)0x81000000, (u8*)OSGetArenaHi() - 0x80, 0x80);
}

void __OSStopAudioSystem(void)
{
	u32 status;

	__DSPRegs[5]  = 0x804;
	status        = __DSPRegs[27];
	__DSPRegs[27] = status & ~0x8000;

	status = __DSPRegs[5];
	while (status & 0x400) {
		status = __DSPRegs[5];
	}
	status = __DSPRegs[5];
	while (status & 0x200) {
		status = __DSPRegs[5];
	}

	__DSPRegs[5] = 0x8AC;
	__DSPRegs[0] = 0;
	while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000) {
	}

	status = OSGetTick();
	while ((s32)(OSGetTick() - status) < 0x2C) {
	}

	__DSPRegs[5] |= 1;
	status = __DSPRegs[5];
	while (status & 1) {
		status = __DSPRegs[5];
	}
}
