// adx_crs: ADX critical section wrappers over the SVM lock.
// .text 0x802127B0-0x80212800 (3 functions), .bss 0x80411220-0x80411228.
// Boundary: MKD adx_crs.o (Unlock, Lock, Init); adxcrs_lvl is written only by
// ADXCRS_Init.

#include "types.h"

extern void fn_8022291C(void); /* SVM_Unlock */
extern void fn_802229AC(void); /* SVM_Lock */

s32 adxcrs_lvl = 0;
s32 adxcrs_msk = 0;

void ADXCRS_Init(void)
{
	adxcrs_lvl = 0;
}

void ADXCRS_Lock(void)
{
	fn_802229AC();
}

void ADXCRS_Unlock(void)
{
	fn_8022291C();
}
