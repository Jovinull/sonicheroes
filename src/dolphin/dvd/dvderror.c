#include "types.h"

// The drive reports failures as a 32 bit code. SRAM only has one byte for the
// last error, so the code gets folded down: the low 24 bits are looked up in a
// table to get a position, and the high byte scales it.

// Only the byte at 0x24 matters here.
typedef struct OSSramEx {
	u8 pad[0x24];  // 0x00
	u8 dvdErrorCode; // 0x24
} OSSramEx;

extern OSSramEx* __OSLockSramEx(void);
extern BOOL      __OSUnlockSramEx(BOOL commit);

static u32 ErrorTable[] = {
	0x00000000, 0x00023A00, 0x00062800, 0x00030200, 0x00031100, 0x00052000,
	0x00052001, 0x00052100, 0x00052400, 0x00052401, 0x00052402, 0x000B5A01,
	0x00056300, 0x00020401, 0x00020400, 0x00040800, 0x00100007, 0x00000000,
};

// Returns u8, and the narrowing has to come from the return type rather than a
// cast on the returned value. An explicit (u8) inside the return suppresses the
// loop unrolling the original has, which costs sixty points on this function.
//
// The original calls this rather than folding it in, so it has to stay a
// function.
#pragma dont_inline on
static u8 ErrorCode2Num(u32 errorCode)
{
	u32 i;

	for (i = 0; i < 18; i++) {
		if (errorCode == ErrorTable[i]) {
			return i;
		}
	}

	// A whole band of codes collapses onto one slot rather than getting
	// eighteen entries of its own.
	if (errorCode >= 0x00100000 && errorCode <= 0x00100008) {
		return 0x11;
	}

	return 0x1D;
}
#pragma dont_inline off

void __DVDStoreErrorCode(u32 errorCode)
{
	u8  num;
	u32 status;

	if (errorCode == 0x01234567) {
		num = 0xFF;
	} else if (errorCode == 0x01234568) {
		num = 0xFE;
	} else {
		status = errorCode >> 24;
		num    = ErrorCode2Num(errorCode & 0x00FFFFFF);
		if (status >= 6) {
			status = 6;
		}
		num = num + status * 30;
	}

	__OSLockSramEx()->dvdErrorCode = (u8)num;
	__OSUnlockSramEx(TRUE);
}
