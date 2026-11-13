#include "types.h"
#include "MSL_C/string.h"

typedef struct ADXF_PT {
	u8 pad0[8];
	s32 fsize; /* 0x08 */
	u8 padC[2];
	u8 unkE;          /* 0x0E */
	s8 unkF;          /* 0x0F */
	char name[0x100]; /* 0x10 */
	s32 dir;          /* 0x110 */
	s32 ofst;         /* 0x114 */
	union {
		struct {
			u32 base;    /* 0x118 */
			u32 size[1]; /* 0x11C */
		} w;
		struct {
			u16 base;    /* 0x118 */
			u16 size[1]; /* 0x11A */
		} h;
	} u;
} ADXF_PT;

extern "C" {
extern ADXF_PT* adxf_ptinfo[256];
extern char lbl_8023EA3C[];
extern char lbl_8023EA60[];

extern void ADXERR_CallErrFunc1(const char* msg);

s32 ADXF_GetFnameRangeEx(s32 ptid, s32 flid, char* fname, void** dir, s32* ofst, s32* nsct)
{
	s32 err;
	ADXF_PT* p;
	ADXF_PT* pt;
	u32* sizes;
	u16* hsize;
	s32 i;
	u32 sum;

	if (ptid < 0 || ptid >= 0x100) {
		ADXERR_CallErrFunc1(lbl_8023EA3C);
		err = -3;
	} else if ((p = adxf_ptinfo[ptid]) == NULL) {
		ADXERR_CallErrFunc1(lbl_8023EA3C);
		err = -3;
	} else if (flid < 0 || flid >= p->fsize) {
		ADXERR_CallErrFunc1(lbl_8023EA60);
		err = -3;
	} else {
		err = 0;
	}
	if (err < 0) {
		*dir  = NULL;
		*ofst = -1;
		*nsct = -1;
		return err;
	}
	pt = adxf_ptinfo[ptid];
	if (pt->unkF == 1) {
		sizes = (u32*)((u8*)pt + 0x11c);
		sum   = pt->u.w.base;
		for (i = 0; i < flid; i++) {
			sum += sizes[i];
		}
		*nsct = sizes[flid];
	} else {
		hsize = (u16*)((u8*)pt + 0x11a);
		sum   = pt->u.h.base;
		for (i = 0; i < flid; i++) {
			sum += hsize[i];
		}
		*nsct = hsize[flid];
	}
	strncpy(fname, pt->name, 0x100);
	*dir  = (void*)pt->dir;
	*ofst = pt->ofst + sum;
	return err;
}
}
