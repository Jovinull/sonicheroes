#include "types.h"

// CRI AXRNA for GameCube.
//
// The unit runs from fn_80223500 at 0x80223500 to the end of fn_80224C3C at
// 0x80224D14, and owns .rodata 0x80240400 to 0x802405F8, .data 0x8029BAB0 to
// 0x8029BB30 and .bss 0x80428A78 to 0x8042A9D0. The disc ships no map, so the
// bounds are argued rather than read:
//
//   The .rodata opens with the module's own banner, "\nAXRNA Ver.1.02
//   Build:May  9 2003 17:10:58\n", followed by a pointer to it. It ends at
//   0x802405F8, where the "RNARES handle" and "ADX buffer" messages start;
//   those belong to fn_80224D14 and fn_80224E1C, which sit above this run.
//
//   Every .bss and .data block between 0x80428A78 and 0x8042A9D0, and between
//   0x8029BAB0 and 0x8029BB30, is touched only by functions of this run.
//   0x8042A9D0 is the first block that is not: fn_80224E1C and fn_80224F88
//   share it, and both sit above the cut.
//
//   The lower bound is the neighbour. game/cri/adapter.c ends at 0x80223500
//   and its .bss ends at 0x80428A78, exactly where this one starts.
//
// Nothing is named yet: the banner carries no function names and the two error
// strings in range belong to the unit above, so every function keeps its dtk
// name.

typedef struct AxObj AxObj;

typedef struct AxVtbl {
	/* 0x00 */ u8 pad00[0xc];
	/* 0x0c */ void (*stop)(AxObj* obj);
	/* 0x10 */ u8 pad10[4];
	/* 0x14 */ void (*reset)(AxObj* obj);
	/* 0x18 */ void (*read)(AxObj* obj, s32 which, s32 size, void* out);
	/* 0x1c */ u8 pad1c[4];
	/* 0x20 */ void (*put)(AxObj* obj, s32 which, void* buf);
	/* 0x24 */ s32 (*get)(AxObj* obj, s32 arg);
} AxVtbl;

typedef struct AxCb {
	/* 0x00 */ s32 pad00;
	/* 0x04 */ s32 id;
} AxCb;

struct AxObj {
	/* 0x00 */ AxVtbl* vtbl;
};

typedef struct AxStream {
	/* 0x00 */ s32 flag[2];
	/* 0x08 */ s32 acc;
	/* 0x0C */ s32 total;
} AxStream;

typedef struct AxRna {
	/* 0x00 */ s8 stat;
	/* 0x01 */ u8 flags;
	/* 0x02 */ s8 nch;
	/* 0x03 */ s8 idx;
	/* 0x04 */ s32 loopReq;
	/* 0x08 */ AxObj* obj[2];
	/* 0x10 */ AxCb* cb[2];
	/* 0x18 */ s32 loopStart[2];
	/* 0x20 */ s32 loopLen;
	/* 0x24 */ s32 rate;
	/* 0x28 */ u8 pad28[8];
	/* 0x30 */ AxObj* strmA[2];
	/* 0x38 */ AxObj* strmB[2];
	/* 0x40 */ u8 bufA[2][8];
	/* 0x50 */ u8 bufB[2][8];
	/* 0x60 */ AxStream st[2];
	/* 0x80 */ s32 pad80;
	/* 0x84 */ s32 vol;
	/* 0x88 */ s32 pan[2];
	/* 0x90 */ u8 pad90[0x10];
	/* 0xa0 */ s16 rateMode;
	/* 0xa2 */ s16 rateFlag;
	/* 0xa4 */ s32 rateBias;
	/* 0xa8 */ u8 pad_a8[0x40];
} AxRna;

#define AX_RNA_MAX 16

extern void fn_8022347C(void* func, void* obj);
extern void fn_80223490(void);
extern void fn_802234B0(void);
extern void fn_801E89A4(AxObj* obj, s32 v);
extern void fn_801E89CC(AxObj* obj, s32 v);

extern s32 ax_PanTbl[31];

const char ax_ver[]                         = "\nAXRNA Ver.1.02 Build:May  9 2003 17:10:58\n";
static const char* const volatile ax_verptr = ax_ver;

void fn_80223500(AxRna* p, s32 ch, s32 v)
{
	s32 n;

	if (p == NULL) {
		return;
	}
	if (ch >= p->nch) {
		return;
	}
	n = v >= 15 ? 15 : v;
	n = n <= -15 ? -15 : n;
	if (n == p->pan[ch]) {
		return;
	}
	p->pan[ch] = n;
	fn_802234B0();
	if (p->obj[ch] != NULL) {
		fn_801E89CC(p->obj[ch], ax_PanTbl[n + 15]);
	}
	fn_80223490();
}

void fn_802235B4(AxRna* p, s32 v)
{
	s32 n;
	s32 i;

	if (p == NULL) {
		return;
	}
	n = v < 0 ? v : 0;
	n = n <= -999 ? -999 : n;
	if (n == p->vol) {
		return;
	}
	p->vol = n;
	for (i = 0; i < p->nch; i++) {
		fn_802234B0();
		if (p->obj[i] != NULL) {
			fn_801E89A4(p->obj[i], n);
		}
		fn_80223490();
	}
}

extern void fn_80223820(AxRna* p);

static s32 ax_RefCnt;
static void* ax_AlignedBuf;
static s32 ax_X[2];
static s32 ax_Y;
static s32 ax_Z[32];
static u8 ax_Buf[4160];
static AxRna ax_Tbl[AX_RNA_MAX];

void fn_802237B4(void* p, s8 v)
{
	if (p == NULL) {
		return;
	}
	*((s8*)p + 3) = v;
}

void fn_802237C4(void)
{
	AxRna* p;
	u32 i;

	p = ax_Tbl;
	for (i = 0; i < AX_RNA_MAX; i++) {
		if (p->stat == 1) {
			fn_80223820(p);
		}
		p++;
	}
}

s32 fn_80223E78(AxRna* p)
{
	if (p == NULL) {
		return -1;
	}
	return (s32)((u32)p->strmA[p->idx + 1]->vtbl->get(p->strmA[p->idx + 1], 0) >> 1);
}

s32 fn_80223ED0(AxRna* p)
{
	if (p == NULL) {
		return -1;
	}
	return 4096 - (s32)((u32)p->strmA[p->idx + 1]->vtbl->get(p->strmA[p->idx + 1], 0) >> 1);
}

void fn_80223B58(AxCb* cb)
{
	s32 x;
	AxRna* p;
	s32 ch;

	x  = cb->id & 0x7FFFFFFF;
	p  = &ax_Tbl[x / 2];
	ch = x % 2;
	if (p->st[1].flag[ch] == 1) {
		p->strmB[ch]->vtbl->put(p->strmB[ch], 1, &p->bufB[ch]);
		p->st[1].flag[ch] = 0;
		if (ch == p->idx - 1) {
			p->st[1].total += p->st[1].acc;
		}
	}
}

void fn_80223C24(AxCb* cb)
{
	s32 x;
	AxRna* p;
	s32 ch;

	x  = cb->id & 0x7FFFFFFF;
	p  = &ax_Tbl[x / 2];
	ch = x % 2;
	if (p->st[0].flag[ch] == 1) {
		p->strmA[ch]->vtbl->put(p->strmA[ch], 0, &p->bufA[ch]);
		p->strmB[ch]->vtbl->put(p->strmB[ch], 1, &p->bufB[ch]);
		p->st[0].flag[ch] = 0;
		if (ch == p->idx - 1) {
			p->st[0].total += p->st[0].acc;
		}
	}
}

void fn_80223D00(AxRna* p)
{
	s32 buf[2];
	s32 n;
	s32 req;
	s32 size;
	s32 i;
	s32 bytes;

	req = p->loopReq;
	if (p->obj[p->idx - 1] != NULL) {
		n            = *(s32*)((u8*)p->obj[p->idx - 1] + 0x1B2) - p->loopStart[p->idx];
		ax_Z[ax_Y++] = n;
		if (ax_Y == 32) {
			ax_Y = 0;
		}
		if (n < 0 || n > p->loopLen) {
			while (TRUE) {
			}
		}
		if (req == -1) {
			if (n == 0) {
				size = 0;
			} else {
				req        = 0;
				p->loopReq = 0;
			}
		}
		if (req != -1) {
			if (n > req) {
				size = n - req;
			} else {
				size = 4096 - (req - n);
			}
		}
		size = (size / 2048) * 2048;
		if (size > 0) {
			bytes = size * 2;
			for (i = 0; i < p->idx; i++) {
				p->strmB[i]->vtbl->read(p->strmB[i], 1, bytes, buf);
				p->strmB[i]->vtbl->put(p->strmB[i], 0, buf);
			}
			p->loopReq += size;
			if (p->loopReq >= 4096) {
				p->loopReq -= 4096;
			}
		}
	}
}

extern void fn_801E8984(AxObj* obj);
extern void fn_80224F88(void);
extern void* memset(void* p, int c, u32 n);

void fn_80224C3C(void)
{
	(void)ax_verptr;
	if (ax_RefCnt == 0) {
		fn_80224F88();
		memset(ax_Tbl, 0, sizeof(ax_Tbl));
		ax_AlignedBuf = (void*)(((u32)ax_Buf + 31) & ~31);
	}
	ax_RefCnt++;
}

void fn_80224A88(AxObj* obj)
{
	s32 i;
	s32 j;

	for (i = 0; i < AX_RNA_MAX; i++) {
		for (j = 0; j < 2; j++) {
			if (obj == ax_Tbl[i].obj[j]) {
				fn_801E8984(ax_Tbl[i].obj[j]);
				ax_Tbl[i].obj[j] = NULL;
				return;
			}
		}
	}
}

void fn_80224CB0(void* func, void* obj)
{
	fn_8022347C(func, obj);
}

s32 fn_80224CD0(void* p)
{
	if (p == NULL) {
		return 0;
	}
	return *(s32*)((s8*)p + 8);
}

s32 fn_80224CE8(void* p)
{
	if (p == NULL) {
		return 0;
	}
	return *(s32*)((s8*)p + 4);
}

extern void fn_80223F2C(AxRna* p, s32 v);
extern void fn_802240CC(AxRna* p, s32 v);
extern void fn_801E221C(AxObj* obj);
extern void fn_80224D00(void* p);

void fn_802242CC(AxRna* p)
{
	s8* nchp;
	s32 i;

	if (p == NULL) {
		return;
	}
	fn_80223F2C(p, 0);
	fn_802240CC(p, 0);
	for (i = 0, nchp = &p->nch; i < *nchp; i++) {
		if (p->strmB[i] != NULL) {
			p->strmB[i]->vtbl->stop(p->strmB[i]);
		}
		if (p->cb[i] != NULL) {
			fn_80224D00(p->cb[i]);
		}
		fn_802234B0();
		if (p->obj[i] != NULL) {
			fn_801E8984(p->obj[i]);
			fn_801E221C(p->obj[i]);
		}
		fn_80223490();
	}
	memset(p, 0, sizeof(AxRna));
}

extern void fn_80224D00(void* p);

extern void fn_801E4994(AxObj* obj, s32 v);
extern void fn_801E4C44(AxObj* obj, void* buf);
extern void fn_80223424(const char* msg);

void fn_80223F2C(AxRna* p, s32 sw)
{
	s32 cur;
	s32 i;

	if (p == NULL) {
		return;
	}
	if (p == NULL) {
		cur = -1;
	} else {
		cur = (p->flags >> 1) & 1;
	}
	if (sw == cur) {
		return;
	}
	fn_802234B0();
	if (sw == 1) {
		p->loopReq = -1;
		for (i = 0; i < p->idx; i++) {
			if (p->obj[i] != NULL) {
				s16 buf[8];
				s32 start = p->loopStart[i];
				s32 end   = start + p->loopLen - 1;
				buf[0]    = 1;
				buf[1]    = 10;
				buf[2]    = (s16)(start >> 16);
				buf[3]    = (s16)start;
				buf[4]    = (s16)(end >> 16);
				buf[5]    = (s16)end;
				buf[6]    = (s16)(start >> 16);
				buf[7]    = (s16)start;
				fn_801E4C44(p->obj[i], buf);
				fn_801E4994(p->obj[i], 1);
			}
		}
		p->flags |= 2;
	} else if (sw == 0) {
		for (i = 0; i < p->idx; i++) {
			if (p->obj[i] != NULL) {
				fn_801E4994(p->obj[i], 0);
			}
		}
		for (i = 0; i < p->nch; i++) {
			p->strmB[i]->vtbl->reset(p->strmB[i]);
		}
		p->flags &= 1;
	} else {
		fn_80223424("E1070309:Illigal parameter(sw).\n");
	}
	fn_80223490();
}

extern void fn_80224E1C(void);

void fn_80224B1C(void)
{
	AxRna* p;
	s32 i;

	if (--ax_RefCnt != 0) {
		return;
	}
	p = ax_Tbl;
	for (i = 0; i < AX_RNA_MAX; i++) {
		if (p->stat == 1) {
			fn_802242CC(p);
		}
		p++;
	}
	memset(ax_Tbl, 0, sizeof(ax_Tbl));
	fn_80224E1C();
}

void fn_80224D00(void* p)
{
	if (p == NULL) {
		return;
	}
	*(s32*)p = 0;
}

extern void fn_801E48D0(AxObj* obj, s32 rate);
extern void fn_801E4DF8(AxObj* obj, void* buf);

void fn_80223660(AxRna* p, s32 v)
{
	s32 adj;
	s32 whole;
	s32 frac;
	s32 i;

	if (p == NULL) {
		return;
	}
	p->rate = v;
	adj     = (v * 1124 + 1124) / 1125;
	whole   = v / 32000;
	frac    = (v << 8) / 125;
	for (i = 0; i < p->nch; i++) {
		fn_802234B0();
		if (p->obj[i] != NULL) {
			s16 buf[8];
			if (p->rateMode == 1) {
				if (v == 32000 && p->rateFlag == 0 && p != NULL) {
					p->rateBias = 0;
					p->rateFlag = 1;
				}
				buf[0] = (s16)((u32)adj / 32000);
				buf[1] = (s16)(((u32)adj << 8) / 125);
			} else {
				buf[0] = (s16)whole;
				buf[1] = (s16)frac;
			}
			buf[2] = 0;
			buf[3] = 0;
			buf[4] = 0;
			buf[5] = 0;
			buf[6] = 0;
			fn_801E48D0(p->obj[i], p->rateBias);
			fn_801E4DF8(p->obj[i], buf);
		}
		fn_80223490();
	}
}
