// Normalises a flag word of the 0x12F atomic plugin unit (HYPOTHESIS): using the flags as given,
// bit 0x8 combined with one of 0x8000/0x20000/0x40000/0x80000/0x100000 paired with
// 0x8/0x20/0x40/0x80/0x100 keeps only that high bit, bit 0x8 clears 0x1, 0x4 and 0x20 when they
// are set, a word with neither 0x8 nor 0x1 gains 0x1, and a word without 0x30000000 gains
// 0x20000000. Returns the result. The meaning of the bits is UNKNOWN.
#include "types.h"

extern "C" {
u32 fn_801FCCE0(u32 flags)
{
	s32 bit0  = flags & 1;
	s32 bit2  = (flags >> 2) & 1;
	s32 bit3  = (flags >> 3) & 1;
	s32 bit5  = (flags >> 5) & 1;
	s32 bit6  = (flags >> 6) & 1;
	s32 bit7  = (flags >> 7) & 1;
	s32 bit8  = (flags >> 8) & 1;
	s32 bit15 = (flags >> 15) & 1;
	s32 bit17 = (flags >> 17) & 1;
	s32 bit18 = (flags >> 18) & 1;
	s32 bit19 = (flags >> 19) & 1;
	s32 bit20 = (flags >> 20) & 1;

	if (bit3 == 1 && bit15 == 1) {
		flags &= 0x8000;
	}
	if (bit5 == 1 && bit17 == 1) {
		flags &= 0x20000;
	}
	if (bit6 == 1 && bit18 == 1) {
		flags &= 0x40000;
	}
	if (bit7 == 1 && bit19 == 1) {
		flags &= 0x80000;
	}
	if (bit8 == 1 && bit20 == 1) {
		flags &= 0x100000;
	}
	if (bit3 == 1 && bit0 == 1) {
		flags &= ~0x1;
	}
	if (bit3 == 1 && bit2 == 1) {
		flags &= ~0x4;
	}
	if (bit3 == 1 && bit5 == 1) {
		flags &= ~0x20;
	}
	if (bit3 == 0 && bit0 == 0) {
		flags |= 0x1;
	}
	if (!(flags & 0x30000000)) {
		flags |= 0x20000000;
	}
	return flags;
}
}
