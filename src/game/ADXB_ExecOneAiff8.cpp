#include "types.h"

typedef struct ADXB_OBJ ADXB_OBJ;

struct ADXB_OBJ {
	u8 pad00[4];
	s32 stat;
	void* xpd;
	u8 pad0C[2];
	s8 fmt;
	u8 pad0F[0x39];
	u8* ibuf;
	s32 unk4C;
	u8 pad50[0x0C];
	u8* obuf;
	s32 total;
	s32 unk64;
	s32 pos;
	s32 unk6C;
	s32 unk70;
	u8 pad74[4];
	void (*fn78)(s32, s32*, s32*, s32*);
	s32 arg7C;
	void (*fn80)(s32, s32, s32);
	s32 arg84;
	u8 pad88[8];
	s32 out90;
	s32 out94;
};

extern "C" {
s32 ADXPD_GetStat(void* xpd);

void ADXB_ExecOneAiff8(ADXB_OBJ* o)
{
	u8* ibuf = o->ibuf;
	s16* out;
	s16* out2;
	s32 i;
	s32 n;

	if (o->stat == 1 && ADXPD_GetStat(o->xpd) == 0) {
		o->fn78(o->arg7C, &o->pos, &o->unk6C, &o->unk70);
		n = o->total - o->pos;
		if (n > o->unk6C) {
			n = o->unk6C;
		}
		if (n > o->unk4C) {
			n = o->unk4C;
		}
		out = (s16*)(o->obuf + o->pos * 2);
		if (o->fmt == 2) {
			out2 = (s16*)(o->obuf + (o->unk64 + o->pos) * 2);
			for (i = 0; i < n; i++) {
				out[i]  = (ibuf[i * 2] << 8) & 0xFF00;
				out2[i] = (ibuf[i * 2 + 1] << 8) & 0xFF00;
			}
		} else {
			for (i = 0; i < n; i++) {
				out[i] = (ibuf[i] << 8) & 0xFF00;
			}
		}
		o->out90 = n;
		o->out94 = n * o->fmt;
		o->stat  = 2;
	}
	if (o->stat == 2) {
		o->fn80(o->arg84, o->out94, o->out90);
		o->stat = 3;
	}
}
}
