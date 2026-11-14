#include "types.h"

typedef struct ADXB_OBJ ADXB_OBJ;

struct ADXB_OBJ {
	u8 pad00[4];
	s32 stat;  /* 0x04 */
	void* xpd; /* 0x08 */
	u8 pad0C[2];
	s8 nch; /* 0x0E */
	u8 pad0F[0x39];
	u16* ibuf;    /* 0x48 */
	s32 ibufsize; /* 0x4C */
	u8 pad50[0x0C];
	u16* obuf; /* 0x5C */
	s32 f60;   /* 0x60 */
	s32 f64;   /* 0x64 */
	s32 pu0;   /* 0x68 */
	s32 pu1;   /* 0x6C */
	s32 pu2;   /* 0x70 */
	u8 pad74[4];
	void (*getinfo)(void*, s32*, s32*, s32*); /* 0x78 */
	void* getinfo_arg;                        /* 0x7C */
	void (*outcb)(void*, s32, s32);           /* 0x80 */
	void* outcb_arg;                          /* 0x84 */
	u8 pad88[8];
	s32 numsmpl; /* 0x90 */
	s32 dtsize;  /* 0x94 */
};

extern "C" {
s32 ADXPD_GetStat(void* xpd);
void ADXB_ExecOneAu16(ADXB_OBJ* o);
}

void ADXB_ExecOneAu16(ADXB_OBJ* o)
{
	u16* ibuf = o->ibuf;
	u16* dst;
	u16* dst2;
	s32 i;
	s32 n;

	if (o->stat == 1) {
		if (ADXPD_GetStat(o->xpd) == 0) {
			o->getinfo(o->getinfo_arg, &o->pu0, &o->pu1, &o->pu2);
			n = o->f60 - o->pu0;
			if (n > o->pu1) {
				n = o->pu1;
			}
			if (n > o->ibufsize) {
				n = o->ibufsize;
			}
			dst = o->obuf + o->pu0;
			if (o->nch == 2) {
				dst2 = o->obuf + (o->f64 + o->pu0);
				u16 v;
				for (i = 0; i < n; i++) {
					v       = ibuf[i * 2];
					dst[i]  = (u16)((v << 8) | (v >> 8));
					v       = ibuf[i * 2 + 1];
					dst2[i] = (u16)((v << 8) | (v >> 8));
				}
			} else {
				for (i = 0; i < n; i++) {
					dst[i] = (u16)((ibuf[i] >> 8) | (ibuf[i] << 8));
				}
			}
			o->numsmpl = n;
			o->dtsize  = o->nch * (n * 2);
			o->stat    = 2;
		}
	}
	if (o->stat == 2) {
		o->outcb(o->outcb_arg, o->dtsize, o->numsmpl);
		o->stat = 3;
	}
}
