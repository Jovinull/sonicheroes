// CRI ADXGC_SetAdjsfreqFlg (adx_gc): .text 0x8021B358..0x8021B37C, no data.
// Boundary: MKD adx_gc.o holds exactly this function between adx_sugc.o and
// adx_rnaa.o.

#include "types.h"

typedef struct ADXT_OBJ {
	s8 pad0[0xC];
	void* rna;
} ADXT_OBJ;

extern void ADXRNA_SetAdjsfreqFlg(void* rna, s32 flag);

void ADXGC_SetAdjsfreqFlg(ADXT_OBJ* adxt, s32 flag)
{
	ADXRNA_SetAdjsfreqFlg(adxt->rna, flag);
}
