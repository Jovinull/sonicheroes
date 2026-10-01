/*
 * adx_tlk2.c -- ADXT_StartFname / ADXT_StartAfs.
 * .text   0x80219778-0x80219904 (2 functions)
 * .rodata 0x8023E7D0-0x8023E84C (+4 bytes alignment padding to 0x8023E850)
 *
 * TU evidence: PS2 symbol metadata names an adx_tlk2.c holding the Start*
 * entry points; here both call ADXT_Stop out of line, whereas every adx_tlk.c
 * caller has it inlined, and their strings follow adx_tlk's pool.
 * Build: GC/1.3.2, "-sdata 0 -sdata2 0 -str reuse,readonly -use_lmw_stmw on
 * -inline deferred". Functions are written in original (PS2) source order;
 * deferred mode emits them reversed, i.e. in DOL order.
 */
#include "types.h"
#include "MSL_C/string.h"

typedef struct SJ_OBJ SJ_OBJ;
typedef SJ_OBJ* SJ;

typedef struct SJCK {
	s8* data;
	s32 len;
} SJCK;

typedef struct SJ_IF {
	void* obj0;
	void* obj4;
	void* obj8;
	void (*Destroy)(SJ sj);
	void* GetUuid;
	void (*Reset)(SJ sj);
	void (*GetChunk)(SJ sj, s32 id, s32 nbyte, SJCK* ck);
	void (*UngetChunk)(SJ sj, s32 id, SJCK* ck);
	void (*PutChunk)(SJ sj, s32 id, SJCK* ck);
	s32 (*GetNumData)(SJ sj, s32 id);
} SJ_IF;

struct SJ_OBJ {
	SJ_IF* vtbl;
};

typedef struct ADXT_OBJ {
	s8 used;          /* 0x00 */
	s8 stat;          /* 0x01 */
	s8 pmode;         /* 0x02 */
	s8 maxnch;        /* 0x03 */
	void* sjd;        /* 0x04 */
	void* stm;        /* 0x08 */
	void* rna;        /* 0x0C */
	SJ sjf;           /* 0x10 */
	SJ sji;           /* 0x14 */
	SJ sjo[2];        /* 0x18 */
	s8* ibuf;         /* 0x20 */
	s32 ibufbsize;    /* 0x24 */
	s32 ibufxsize;    /* 0x28 */
	s8* obuf;         /* 0x2C */
	s32 obufbsize;    /* 0x30 */
	s32 obufdist;     /* 0x34 */
	s32 svrfreq;      /* 0x38 */
	s16 maxsct;       /* 0x3C */
	s16 minsct;       /* 0x3E */
	s16 outvol;       /* 0x40 */
	s16 outpan[2];    /* 0x42 */
	s16 outbalance;   /* 0x46 */
	s32 maxdecsmpl;   /* 0x48 */
	s32 lpcnt;        /* 0x4C */
	s32 lp_skiplen;   /* 0x50 */
	s32 trp;          /* 0x54 */
	s32 wpos;         /* 0x58 */
	s32 mofst;        /* 0x5C */
	s16 ecode;        /* 0x60 */
	s16 pad62;        /* 0x62 */
	s32 edecpos;      /* 0x64 */
	s16 edeccnt;      /* 0x68 */
	s16 eshrtcnt;     /* 0x6A */
	s8 lpflg;         /* 0x6C */
	s8 autorcvr;      /* 0x6D */
	s8 fltmode;       /* 0x6E */
	s8 execflag;      /* 0x6F */
	s8 pstwait_flag;  /* 0x70 */
	s8 pstready_flag; /* 0x71 */
	s8 pause_flag;    /* 0x72 */
	s8 pad73;         /* 0x73 */
	void* amp;        /* 0x74 */
	SJ ampsji[2];     /* 0x78 */
	SJ ampsjo[2];     /* 0x80 */
	s32 time_ofst;    /* 0x88 */
	s32 lesct;        /* 0x8C */
	s32 trpnsmpl;     /* 0x90 */
	void* lsc;        /* 0x94 */
	s8 lnkflg;        /* 0x98 */
	s8 pad99[3];      /* 0x99 */
	u32 tvofst;       /* 0x9C */
	s32 svcnt;        /* 0xA0 */
	s32 decofst;      /* 0xA4 */
	s8 stmstart;      /* 0xA8 */
	s8 padA9[3];      /* 0xA9 */
	char* fnbuf;      /* 0xAC */
	char* fname;      /* 0xB0 */
	void* dir;        /* 0xB4 */
	s32 ofst;         /* 0xB8 */
	s32 nsct;         /* 0xBC */
} ADXT_OBJ;

typedef ADXT_OBJ* ADXT;

extern void ADXERR_CallErrFunc1(const char* msg);
extern void ADXERR_CallErrFunc2(const char* msg1, const char* msg2);
extern void ADXERR_ItoA2(s32 no1, s32 no2, char* buf, s32 len);
extern s32 ADXF_GetFnameRangeEx(s32 ptid, s32 flid, char* fname, void** dir, s32* ofst, s32* nsct);
extern void ADXT_Stop(ADXT adxt);

void ADXT_StartFname(ADXT adxt, const char* fname);
void ADXT_StartAfs(ADXT adxt, s32 patid, s32 fid);

void ADXT_StartAfs(ADXT adxt, s32 patid, s32 fid)
{
	s32 ofst;
	s32 nsct;
	void* dir;
	char buf[20];

	if (adxt == NULL) {
		ADXERR_CallErrFunc1("E02080811 ADXT_StartAfs: parameter error");
		return;
	}
	ADXT_Stop(adxt);
	if (ADXF_GetFnameRangeEx(patid, fid, adxt->fnbuf, &dir, &ofst, &nsct) != 0) {
		return;
	}
	if (adxt->stm == NULL) {
		ADXERR_ItoA2(patid, fid, buf, 16);
		ADXERR_CallErrFunc2("E8101202 ADXT_StartAfs: can't open ", buf);
		adxt->ecode = -1;
		adxt->stat  = 6;
		return;
	}
	adxt->fname    = adxt->fnbuf;
	adxt->dir      = dir;
	adxt->ofst     = ofst;
	adxt->nsct     = nsct;
	adxt->stat     = 1;
	adxt->stmstart = 1;
	adxt->pmode    = 1;
	adxt->lnkflg   = 0;
}

void ADXT_StartFname(ADXT adxt, const char* fname)
{
	if (adxt == NULL || fname == NULL) {
		ADXERR_CallErrFunc1("E02080807 ADXT_StartFname: parameter error");
		return;
	}
	ADXT_Stop(adxt);
	strcpy(adxt->fnbuf, fname);
	adxt->fname    = adxt->fnbuf;
	adxt->dir      = NULL;
	adxt->ofst     = 0;
	adxt->nsct     = 0xFFFFF;
	adxt->stat     = 1;
	adxt->stmstart = 1;
	adxt->pmode    = 0;
	adxt->lnkflg   = 0;
}
