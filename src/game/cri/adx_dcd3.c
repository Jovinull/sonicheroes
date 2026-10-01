// adx_dcd3: stereo-as-mono decode switch.
// .text 0x80213014-0x80213020 (1 function), .bss 0x80411228-0x8041122C.
// Boundary: PS2 symbols put ADX_SetDecodeSteAsMonoSw at the head of adx_dcd3,
// between adx_dcd and adx_dcd5/adx_errs; its flag (MKD adx_dcd3.c name) is read
// by the ADX_DecodeSte4 dispatcher in adx_dcd5 (0x8021B5E8). The float decoders
// of this file are not linked on GC.

#include "types.h"

s32 adx_decode_output_mono_flag;

void ADX_SetDecodeSteAsMonoSw(s32 sw)
{
	adx_decode_output_mono_flag = sw;
}
