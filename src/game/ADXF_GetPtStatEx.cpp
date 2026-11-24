// Polls the background load of an AFS partition header (ADXF_LoadPartitionNw): checks the "AFS"
// magic and file count, then converts each little-endian file size into sectors in adxf_ptinfo.
// ADXF_GetStat and ADXF_ReadNw are inlined, as in retail.
// The messages sit in the adx_fs string pool at lbl_8023EA10. Retail keeps the pool base in one
// register, as mwcc does for its own pooled literals; a one-function unit can't own that pool, so
// the base is held in the local `pool` (HYPOTHESIS: the original wrote plain string literals).
// Field and helper names are inferred from use.

#include "types.h"

typedef struct ADXF_OBJ {
	s8 used;
	s8 stat;
	s8 sjflag;
	s8 stopnw_flg;
	u8 pad04[0x44 - 0x04];
} ADXF_OBJ;
typedef ADXF_OBJ* ADXF;

typedef struct ADXF_PT {
	u32 unk0;
	s32 size;
	s32 nfile;
	u16 nfile16;
	u8 unkE;
	s8 type;
} ADXF_PT;

extern "C" {
extern ADXF_PT* adxf_ptinfo[256];
extern s32 adxf_flno;
extern ADXF adxf_ldptnw_hn;
extern s32 adxf_ldptnw_ptid;
extern u8* lbl_8041D1A8;
extern s32 lbl_8041D1AC;
extern char lbl_8023EA10[]; /* adx_fs string pool */
void ADXERR_CallErrFunc1(const char* msg);
s32 memcmp(const void* a, const void* b, u32 n);
void adxf_CloseLdptnwHn(void);
s32 ADXF_ReadNw32(ADXF adxf, s32 nsct, void* buf);
}

static inline s32 GETLE32(u8* p)
{
	return (s32)(p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24));
}
static inline s32 GETLE32I(u8* b, s32 i)
{
	return GETLE32(b + i * 4);
}

static inline s32 ADXF_GetStat(char* pool, ADXF adxf)
{
	if (adxf == NULL) {
		ADXERR_CallErrFunc1(pool + 0x74);
		return -3;
	}
	return adxf->stat;
}

static inline s32 ADXF_ReadNw(char* pool, ADXF adxf, s32 nsct, void* buf)
{
	if ((u32)buf & 0x1F) {
		ADXERR_CallErrFunc1(pool + 0x238);
		return -3;
	}
	return ADXF_ReadNw32(adxf, nsct, buf);
}

extern "C" s32 ADXF_GetPtStatEx(s32 ptid)
{
	u16* hsize;
	u32* wsize;
	ADXF_PT* p;
	s32 stat;
	u16* hbase;
	u32* wbase;
	s32 i;
	s32 n;
	u32 v;
	s32 q;
	s32 nf;
	char* pool;

	pool  = lbl_8023EA10;
	hsize = NULL;
	hbase = NULL;
	wsize = NULL;
	wbase = NULL;

	if (ptid != adxf_ldptnw_ptid) {
		ADXERR_CallErrFunc1(pool + 0x3F8);
		return -3;
	}
	stat = ADXF_GetStat(pool, adxf_ldptnw_hn);
	if (stat != 3) {
		return stat;
	}
	p = adxf_ptinfo[ptid];
	if (p->type == 1) {
		wbase = (u32*)((u8*)p + 0x118);
		wsize = (u32*)((u8*)wbase + 4);
	} else {
		hbase = (u16*)((u8*)p + 0x118);
		hsize = (u16*)((u8*)hbase + 2);
	}
	if (p->nfile == 0) {
		if (memcmp(lbl_8041D1A8, pool + 0x42C, 3) != 0) {
			ADXERR_CallErrFunc1(pool + 0x430);
			adxf_CloseLdptnwHn();
			return 4;
		}
		nf = GETLE32(lbl_8041D1A8 + 4);
		if (nf > 0x10000) {
			ADXERR_CallErrFunc1(pool + 0x464);
			adxf_CloseLdptnwHn();
			return 4;
		}
		p->nfile16 = (u16)nf;
		p->nfile   = (u16)nf;
		if (p->type == 1) {
			p->size = (((p->nfile + 1) * 4) + 0x11c) & ~3u;
		} else {
			p->size = (((p->nfile + 1) * 2) + 0x11a) & ~3u;
		}
		if (p->type == 1) {
			v      = (u32)GETLE32(lbl_8041D1A8 + 8);
			*wbase = (s32)v / 2048;
		} else {
			v      = (u32)GETLE32(lbl_8041D1A8 + 8);
			*hbase = (u16)((s32)v / 2048);
		}
		i = 3;
	} else {
		i = 1;
	}
	n = (lbl_8041D1AC << 11) / 4;
	while (i < n) {
		if (p->type == 1) {
			v = (u32)GETLE32I(lbl_8041D1A8, i);
			q = (s32)v / 2048;
			if ((s32)v % 2048 > 0) {
				q++;
			}
			wsize[adxf_flno++] = q;
		} else {
			v = (u32)GETLE32I(lbl_8041D1A8, i);
			q = (s32)v / 2048;
			if ((s32)v % 2048 > 0) {
				q++;
			}
			if (q & 0xFFFF0000) {
				ADXERR_CallErrFunc1(pool + 0x498);
				adxf_CloseLdptnwHn();
				return 4;
			}
			hsize[adxf_flno++] = (u16)q;
		}
		if (adxf_flno >= p->nfile) {
			stat = 3;
			adxf_CloseLdptnwHn();
			break;
		}
		i += 2;
	}
	if (i >= n) {
		if (ADXF_ReadNw(pool, adxf_ldptnw_hn, lbl_8041D1AC, lbl_8041D1A8) < 0) {
			stat = 4;
			adxf_CloseLdptnwHn();
		} else {
			stat = adxf_ldptnw_hn->stat;
		}
	}
	return stat;
}
