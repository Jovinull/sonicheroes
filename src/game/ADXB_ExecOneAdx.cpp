#include "types.h"

typedef struct ADXB_OBJ ADXB_OBJ;

struct ADXB_OBJ {
	u8 pad00[4];
	s32 stat;  /* 0x04 */
	void* xpd; /* 0x08 */
	u8 pad0C[0x34];
	s32 f40;      /* 0x40 */
	s32 f44;      /* 0x44 */
	s8* ibuf;     /* 0x48 */
	s32 ibufsize; /* 0x4C */
	s32 nch;      /* 0x50 */
	s32 f54;      /* 0x54 */
	s32 f58;      /* 0x58 */
	s16* obuf;    /* 0x5C */
	s32 f60;      /* 0x60 */
	s32 f64;      /* 0x64 */
	s32 pu0;      /* 0x68 */
	s32 pu1;      /* 0x6C */
	s32 pu2;      /* 0x70 */
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
s32 ADXPD_GetNumBlk(void* xpd);
s32 ADXPD_EntryMono(void* xpd, s8* ibuf, s32 nblk, s16* obuf);
s32 ADXPD_EntrySte(void* xpd, s8* ibuf, s32 nblk, s16* obufl, s16* obufr);
void ADXPD_Start(void* xpd);
void ADXPD_ExecHndl(void* xpd);
void ADXPD_Reset(void* xpd);

static inline s32 adxb_GetNumChan(void* obj)
{
	return ((ADXB_OBJ*)obj)->nch;
}

static inline s16* adxb_GetWrPtr(void* obj)
{
	ADXB_OBJ* a = (ADXB_OBJ*)obj;
	s16* p;

	p = a->obuf;
	p += a->pu0;
	return p;
}

void ADXB_ExecOneAdx(ADXB_OBJ* o)
{
	s16* out;
	s32 p0;
	s16* in;
	s32 i;
	s32 n;
	s32 pos;
	s32 b;
	s32 mx;
	s32 ofs;
	s32 w;
	s32 x;
	s32 ofs2;
	s32 f54;
	s32 f58;
	s32 lim;

	if (o->stat == 1 && ADXPD_GetStat(o->xpd) == 0) {
		o->getinfo(o->getinfo_arg, &o->pu0, &o->pu1, &o->pu2);
		p0  = o->pu0;
		lim = o->f60;
		w   = o->pu2;
		n   = o->ibufsize / o->nch;
		pos = o->pu1;
		x   = w + o->f58 - 1;
		mx  = x / o->f58;
		ofs = (o->f58 - 1) - x % o->f58;
		b   = lim - p0 - 1;
		b   = (o->f58 + b) / o->f58;
		i   = b * o->f58;
		if (mx < b && p0 + i - ofs < lim) {
			b++;
		}
		if (w < pos) {
			pos += ofs;
		}
		if (n > pos / o->f58) {
			n = pos / o->f58;
		}
		if (n > mx) {
			n = mx;
		}
		if (n > b) {
			n = b;
		}
		if (adxb_GetNumChan(o) == 2) {
			void* xpd = o->xpd;
			out       = adxb_GetWrPtr(o);
			ADXPD_EntrySte(xpd, o->ibuf, n * 2, out, out + o->f64);
			ADXPD_Start(xpd);
		} else {
			void* xpd = o->xpd;
			ADXPD_EntryMono(xpd, o->ibuf, n, adxb_GetWrPtr(o));
			ADXPD_Start(xpd);
		}
		o->stat = 2;
	}
	if (o->stat == 2) {
		ADXPD_ExecHndl(o->xpd);
		if (ADXPD_GetStat(o->xpd) == 3) {
			s32 f44;
			s32 f40;
			s32 pos2;
			s16* obuf;
			s32 b2;
			s32 numblk;

			f58    = o->f58;
			b2     = o->pu2 + f58 - 1;
			f54    = o->f54;
			pos2   = o->pu0;
			obuf   = o->obuf;
			f40    = o->f40;
			f44    = o->f44;
			ofs2   = (f58 - 1) - b2 % f58;
			numblk = ADXPD_GetNumBlk(o->xpd);
			n      = numblk * f58 / o->nch;
			i      = b2 / f58;
			if (i * o->nch <= numblk) {
				n -= ofs2;
			}
			o->numsmpl = n;
			pos2 += n;
			o->dtsize = numblk * f54;
			if (pos2 >= f40) {
				pos2 -= f40;
				if (adxb_GetNumChan(o) == 2) {
					out = obuf;
					in  = obuf + f40;
					for (i = pos2; i > 0; i--) {
						*out++ = *in++;
					}
					in  = obuf + (f44 + f40);
					out = obuf + f44;
					for (i = pos2; i > 0; i--) {
						*out++ = *in++;
					}
				} else {
					in = obuf + f40;
					for (i = pos2; i > 0; i--) {
						*obuf++ = *in++;
					}
				}
			}
			ADXPD_Reset(o->xpd);
			o->outcb(o->outcb_arg, o->dtsize, o->numsmpl);
			o->stat = 3;
		}
	}
}
}
