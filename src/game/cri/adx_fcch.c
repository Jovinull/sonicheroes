// CRI ADXF_Ocbi (adx_fcch): .text 0x8021BE38..0x8021BE58, no data.
// Boundary: MKD adx_fcch.o holds exactly this function.

#include "types.h"

extern void DCInvalidateRange(void* addr, u32 nbytes);

void ADXF_Ocbi(void* buf, u32 size)
{
	DCInvalidateRange(buf, size);
}
