#include "types.h"

extern "C" {
void adxf_LoadPtBothNw(s32, s32, s32, u32, s32, void*, void*, s32, s32);
extern u8 lbl_8041D1B0[];

void ADXF_LoadPartitionNw(s32 ptid, s32 fno, s32 flen, void* buf)
{
	adxf_LoadPtBothNw(
	    ptid, 0, 0, fno, flen, buf, (void*)(((u32)(lbl_8041D1B0 + 0x20)) & 0xffffffe0u), 0x800, 0);
}
}
