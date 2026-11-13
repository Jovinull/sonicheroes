#include "types.h"

extern "C" {

typedef struct SjObj SjObj;
typedef struct ADXSJD_OBJ ADXSJD_OBJ;

struct ADXSJD_OBJ {
	s8 used;      /* 0x00 */
	s8 state;     /* 0x01 */
	s8 numch;     /* 0x02 */
	s8 f3;        /* 0x03 */
	u32 handle;   /* 0x04 */
	s32 sj;       /* 0x08 */
	s32 tbl[18];  /* 0x0C */
	u8 pad[0x44]; /* 0x54 */
	s32 f98;      /* 0x98 */
};

s8* fn_80220C18(SjObj*);
s32 fn_80220C10(SjObj*);
s32 fn_80220C08(SjObj*);
u32 ADXB_Create(s32, s8*, s32, s32);
void ADXB_EntryGetWrFunc(u32, int (*)(SjObj*, s32*, s32*, s32*), ADXSJD_OBJ*);
extern unsigned char adxsjd_obj[];
int adxsjd_get_wr(SjObj*, s32*, s32*, s32*);

ADXSJD_OBJ* ADXSJD_Create(s32 arg0, s32 arg1, s32* arg2)
{
	s8* buf;
	SjObj* sj;
	ADXSJD_OBJ* o;
	s32 half;
	s32 i;

	sj = (SjObj*)arg2[0];
	for (i = 0; i < 16; i++) {
		if (((ADXSJD_OBJ*)adxsjd_obj)[i].used == 0) {
			break;
		}
	}
	if (i == 16) {
		return 0;
	}
	o = (ADXSJD_OBJ*)adxsjd_obj + i;

	buf       = fn_80220C18(sj);
	half      = fn_80220C10(sj) / 2;
	o->handle = ADXB_Create(arg1, buf, half, half + fn_80220C08(sj) / 2);
	if (o->handle == 0) {
		return 0;
	}
	ADXB_EntryGetWrFunc(o->handle, adxsjd_get_wr, o);

	o->sj    = arg0;
	o->numch = arg1;
	for (i = 0; i < arg1; i++) {
		o->tbl[i] = arg2[i];
	}

	o->state               = 0;
	o->f98                 = 0;
	o->tbl[8]              = 0;          /* +0x2C */
	o->tbl[9]              = 0;          /* +0x30 */
	o->tbl[10]             = 0;          /* +0x34 */
	o->tbl[11]             = 0x7FFFFFFF; /* +0x38 */
	o->tbl[12]             = -1;         /* +0x3C */
	o->tbl[13]             = 0;          /* +0x40 */
	o->tbl[14]             = 0;          /* +0x44 */
	o->f3                  = 0;
	o->tbl[15]             = 0; /* +0x48 */
	o->tbl[16]             = 0; /* +0x4C */
	o->tbl[17]             = 0; /* +0x50 */
	*(s32*)((u8*)o + 0x54) = 0;
	o->used                = 1;
	return o;
}
}
