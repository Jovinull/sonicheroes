#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"
#include "dolphin/types.h"

// MetroTRK mem_TRK.c: the nub memory fill, 0x801CDBFC to 0x801CDCB8.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/mem_TRK.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.
// TRK_memcpy and TRK_memset, the rest of the SDK file, live in .init at
// 0x80003238 and are left in the extracted .init split with the vector table.

void TRK_fill_mem(void* dest, int value, unsigned long length)
{
#define cDest ((unsigned char*)dest)
#define lDest ((unsigned long*)dest)
	unsigned long val = (unsigned char)value;
	unsigned long i;
	lDest = (unsigned long*)dest;
	cDest = (unsigned char*)dest;

	cDest--;

	if (length >= 32) {
		i = ~(unsigned long)dest & 3;

		if (i) {
			length -= i;
			do {
				*++cDest = val;
			} while (--i);
		}

		if (val) {
			val |= val << 24 | val << 16 | val << 8;
		}

		lDest = (unsigned long*)(cDest + 1) - 1;

		i = length >> 5;
		if (i) {
			do {
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
			} while (--i);
		}

		i = (length & 31) >> 2;

		if (i) {
			do {
				*++lDest = val;
			} while (--i);
		}

		cDest = (unsigned char*)(lDest + 1) - 1;

		length &= 3;
	}

	if (length) {
		do {
			*++cDest = val;
		} while (--length);
	}

#undef cDest
#undef lDest
}
