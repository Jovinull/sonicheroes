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
	/* 0x1c */ void (*unget)(AxObj* obj, s32 which, void* buf);
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

typedef struct AxRange {
	/* 0x00 */ void* addr;
	/* 0x04 */ s32 size;
} AxRange;

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
	/* 0x90 */ s32 voiceParam[4];
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
extern void fn_80223B58(AxCb* cb);
extern void fn_80223C24(AxCb* cb);
extern void fn_80223D00(AxRna* p);
extern void fn_80221824(AxRange* src, s32 size, AxRange* consumed, AxRange* remaining);
extern void DCFlushRange(void* addr, u32 size);
extern void ARQPostRequest(void* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest,
    u32 length, void (*callback)(AxCb*));

static s32 ax_RateBias   = 1;
static s32 ax_PanTbl[31] = {
	0,
	4,
	8,
	12,
	16,
	20,
	24,
	28,
	33,
	37,
	41,
	45,
	49,
	53,
	57,
	64,
	68,
	72,
	76,
	81,
	85,
	89,
	93,
	98,
	102,
	106,
	110,
	115,
	119,
	123,
	127,
};

const char lbl_80240400[]                   = "\nAXRNA Ver.1.02 Build:May  9 2003 17:10:58\n";
static const char* const volatile ax_verptr = lbl_80240400;
const char ax_off[]                         = "OFF";
const char ax_on[]                          = "ON ";
const char* const ax_rodata_pad             = ax_off;
const char* const ax_rodata_pad2            = ax_on;
const struct {
	char badSwitch[36];
	char dmaData[56];
	char dmaFlash[56];
	char illegalSwitch[36];
	char badChannelCount[40];
	char nullStreams[40];
	char nullStream[40];
	char noHandles[36];
	char noResource[32];
	char noStream[28];
	char noVoice[36];
} lbl_80240440 = {
	"E1070309:Illigal parameter(sw).\n",
	"E2071701:DMA transfer(data) to A-RAM did not finish.\n",
	"E2071701:DMA transfer(flash) to A-RAM did not finish.\n",
	"E1070308:Illigal parameter(sw).\n",
	"E1070301:Illigal parameter(maxnch<=0).\n",
	"E1070302:Illigal parameter(sj=null).\n",
	"E1070303:Illigal parameter(sj[]=null).\n",
	"E1070304:Not enough RNA handle.\n",
	"E1070305:Can't create RNARES.\n",
	"E1070306:Can't create SJ.\n",
	"E1070307:Can't acquire voice(AX).\n",
};

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

extern void fn_801E48D0(AxObj* obj, s32 rate);
extern void fn_801E4DF8(AxObj* obj, void* buf);

#pragma opt_loop_invariants off
void fn_80223660(AxRna* p, s32 v)
{
	s32 adj;
	s32 whole;
	u16 frac;
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
				u16 adjustedWhole;
				u16 adjustedFrac;
				if (v == 32000 && p->rateFlag == 0 && p != NULL) {
					p->rateBias = 0;
					p->rateFlag = 1;
				}
				adjustedWhole = (u32)adj / 32000;
				adjustedFrac  = ((u32)adj << 8) / 125;
				buf[0]        = adjustedWhole;
				buf[1]        = adjustedFrac;
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
#pragma opt_loop_invariants reset

extern void fn_80223820(AxRna* p);

static u32 ax_RefCnt;
static void* ax_AlignedBuf;
static s32 ax_X[2];
static s32 ax_Y;
static struct {
	s32 z[32];
	u8 buf[4160];
} ax_Work;
static struct {
	AxRna tbl[AX_RNA_MAX];
	s32 pad;
} ax_Table;

#define ax_Z   ax_Work.z
#define ax_Buf ax_Work.buf
#define ax_Tbl ax_Table.tbl

// Never called, and it is here for its side effect on layout, not its value.
// MWCC lays .bss out in the reverse of the order the first function to touch
// these reads them, so a dead static above the first user is what decides where
// they land -- not declaration order, not alignment. Reading them backwards
// here puts all seven at the addresses the target's base register uses. The
// original must have had a real function above this doing the same; what it was
// is unknown, so this stands in for it and is a hypothesis, not a reading.
static s32 ax_Touch(void)
{
	return ax_Z[0] + ax_Buf[0] + ax_Y + ax_X[0] + (ax_AlignedBuf != NULL) + ax_RefCnt;
}

void fn_802237B4(void* p, s8 v)
{
	if (p == NULL) {
		return;
	}
	*((s8*)p + 3) = v;
}

void fn_802237C4(void)
{
	u32 i;

	for (i = 0; i < AX_RNA_MAX; i++) {
		if (ax_Tbl[i].stat == 1) {
			fn_80223820(&ax_Tbl[i]);
		}
	}
}

void fn_80223820(AxRna* p)
{
	AxRange secondRemaining;
	AxRange second;
	AxRange firstRemaining;
	AxRange first;
	AxRange loopRemaining;
	AxRange loopRange;
	s32 bytes;
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
	if (cur == 1) {
		fn_80223D00(p);
	}
	if (p == NULL) {
		cur = -1;
	} else {
		cur = p->flags & 1;
	}
	if (cur == 1) {
		u8* objp = (u8*)p;
		u8* bufp = (u8*)p;
		u8* reqp = (u8*)p;

		for (i = 0; i < p->idx; objp += 4, bufp += 8, reqp += 0x20, i++) {
			if (*(AxObj**)(objp + 8) != NULL && *(s32*)(objp + 0x60) == 0) {
				(*(AxObj**)(objp + 0x38))->vtbl->read(*(AxObj**)(objp + 0x38), 0, 0x2000, &second);
				(*(AxObj**)(objp + 0x30))
				    ->vtbl->read(*(AxObj**)(objp + 0x30), 1, second.size, &first);
				bytes = first.size < second.size ? first.size : second.size;
				bytes = bytes / 32 * 32;
				fn_80221824(&second, bytes, &second, &secondRemaining);
				(*(AxObj**)(objp + 0x38))
				    ->vtbl->unget(*(AxObj**)(objp + 0x38), 0, &secondRemaining);
				fn_80221824(&first, bytes, &first, &firstRemaining);
				(*(AxObj**)(objp + 0x30))->vtbl->unget(*(AxObj**)(objp + 0x30), 1, &firstRemaining);
				if (bytes == 0) {
					return;
				}
				if (first.size != second.size) {
					for (;;) {
					}
				}
				*(AxRange*)(bufp + 0x40) = first;
				*(AxRange*)(bufp + 0x50) = second;
				p->st[0].acc             = (u32)bytes >> 1;
				DCFlushRange(((AxRange*)(bufp + 0x40))->addr, ((AxRange*)(bufp + 0x40))->size);
				*(s32*)(objp + 0x60) = 1;
				ARQPostRequest(reqp + 0xA8, *(u32*)(objp + 0x28), 0, 1, (u32)first.addr,
				    (u32)second.addr, bytes, fn_80223C24);
			}
		}
	} else {
		if (p == NULL) {
			cur = -1;
		} else {
			cur = (p->flags >> 1) & 1;
		}
		if (cur != 1) {
			return;
		}
		if (p->st[1].total >= p->loopLen) {
			return;
		}
		{
			u8* objp = (u8*)p;
			u8* bufp = (u8*)p;
			u8* reqp = (u8*)p;
			s32 loopIndex;
			s32 loopBytes;

			for (loopIndex = 0; loopIndex < p->idx;
			    objp += 4, bufp += 8, reqp += 0x20, loopIndex++) {
				if (*(s32*)(objp + 0x70) == 0) {
					(*(AxObj**)(objp + 0x38))
					    ->vtbl->read(*(AxObj**)(objp + 0x38), 0, 0x2000, &loopRange);
					loopBytes = loopRange.size / 32 * 32;
					fn_80221824(&loopRange, loopBytes, &loopRange, &loopRemaining);
					(*(AxObj**)(objp + 0x38))
					    ->vtbl->unget(*(AxObj**)(objp + 0x38), 0, &loopRemaining);
					if (loopBytes == 0) {
						return;
					}
					*(AxRange*)(bufp + 0x50) = loopRange;
					p->st[1].acc             = (u32)loopBytes >> 1;
					DCFlushRange(ax_AlignedBuf, 0x1000);
					*(s32*)(objp + 0x70) = 1;
					ARQPostRequest(reqp + 0xA8, *(u32*)(objp + 0x28), 0, 1, (u32)ax_AlignedBuf,
					    (u32)loopRange.addr, loopBytes, fn_80223B58);
				}
			}
		}
	}
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
		n            = *(s32*)((u8*)p->obj[p->idx - 1] + 0x1B2) - p->loopStart[p->idx - 1];
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

extern void fn_801E8984(AxObj* obj);
extern void fn_80224F88(void);
extern void* memset(void* p, int c, u32 n);

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
				s32 start       = p->loopStart[i];
				s32 repeatStart = p->loopStart[i];
				s32 end         = start + p->loopLen - 1;
				buf[0]          = 1;
				buf[1]          = 10;
				buf[2]          = (s16)(start >> 16);
				buf[3]          = (s16)start;
				buf[4]          = (s16)(end >> 16);
				buf[5]          = (s16)end;
				buf[6]          = (s16)(repeatStart >> 16);
				buf[7]          = (s16)repeatStart;
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
		fn_80223424(lbl_80240440.badSwitch);
	}
	fn_80223490();
}

void fn_802240CC(AxRna* root, s32 sw)
{
	const char* rodata = lbl_80240400;
	s32 cur;
	s32 zero;
	s32* p;
	s32 i;
	s32 j;
	s32 k;
	s32 delay;

	if (root == NULL) {
		return;
	}
	if (root == NULL) {
		cur = -1;
	} else {
		cur = root->flags & 1;
	}
	if (sw == cur) {
		return;
	}
	if (sw == 1) {
		fn_802234B0();
		for (i = 0; i < root->idx; i++) {
			root->strmB[i]->vtbl->reset(root->strmB[i]);
			memset(root->bufA[i], 0, sizeof(root->bufA[i]));
			memset(root->bufB[i], 0, sizeof(root->bufB[i]));
			memset(root->pad_a8 + i * 0x20, 0, 0x20);
			root->st[0].flag[i] = 0;
		}
		root->st[0].acc   = 0;
		root->st[0].total = 0;
		root->st[1].acc   = 0;
		root->st[1].total = 0;
		root->loopReq     = -1;
		root->flags |= 1;
		fn_80223490();
	} else if (sw == 0) {
		p = (s32*)root;
		for (i = 0; i < root->idx; i++) {
			k = sw;
			for (j = 0; j < 200; j++) {
				zero = 0;
				if (*(volatile s32*)((u8*)p + 0x60) == 0) {
					break;
				}
				if (k < 100000) {
					for (delay = zero; delay < 100000; delay++) {
					}
				}
			}
			if (j == 200) {
				fn_80223424(rodata + 0x64);
				return;
			}
			j = zero;
			k = j;
			for (; j < 200; j++) {
				if (*(volatile s32*)((u8*)p + 0x70) == 0) {
					break;
				}
				if (k < 100000) {
					for (delay = 0; delay < 100000; delay++) {
					}
				}
			}
			if (j == 200) {
				fn_80223424(rodata + 0x9C);
				return;
			}
			p++;
		}
		root->flags &= 2;
	} else {
		fn_80223424(rodata + 0xD4);
	}
}

extern void fn_801E221C(AxObj* obj);
extern void fn_80224D00(void* p);

void fn_802242CC(AxRna* p)
{
	s32 i;

	if (p == NULL) {
		return;
	}
	fn_80223F2C(p, 0);
	fn_802240CC(p, 0);
	for (i = 0; i < p->nch; i++) {
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

extern void fn_80224E1C(void);
extern void fn_80224A88(AxObj* obj);
extern AxCb* fn_80224D14(void);
extern AxObj* fn_80221300(s32 start, s32 length, s32 zero);
extern AxObj* fn_801E229C(s32 priority, void (*callback)(AxObj*), s32 zero);
extern void fn_801E7B08(AxObj* obj, s32 type, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

static inline void ax_SetRateMode(AxRna* p)
{
	if (p == NULL) {
		return;
	}
	p->rateMode = (s16)ax_X[0];
}

static inline void ax_SetRateBias(AxRna* p)
{
	if (p == NULL) {
		return;
	}
	p->rateBias = ax_RateBias;
	p->rateFlag = 1;
}

static inline void ax_SetBufferCount(AxRna* p)
{
	if (p == NULL) {
		return;
	}
	p->pad80 = 16;
}

AxRna* fn_8022439C(AxObj** sj, s32 maxnch)
{
	const char* rodata = lbl_80240400;
	AxRna* p;
	s16 rate[7];
	u32 i;
	u32 id;

	if (maxnch <= 0) {
		fn_80223424(rodata + 0xF8);
		return NULL;
	}
	if (sj == NULL) {
		fn_80223424(rodata + 0x120);
		return NULL;
	}
	for (i = 0; i < maxnch; i++) {
		if (sj[i] == NULL) {
			fn_80223424(rodata + 0x148);
			return NULL;
		}
	}
	for (i = 0; i < AX_RNA_MAX; i++) {
		if (ax_Tbl[i].stat == 0) {
			break;
		}
	}
	if (i == AX_RNA_MAX) {
		fn_80223424(rodata + 0x170);
		return NULL;
	}
	p      = &ax_Tbl[i];
	p->idx = (s8)maxnch;
	p->nch = (s8)maxnch;
	for (i = 0; i < p->nch; i++) {
		p->strmA[i] = sj[i];
	}
	p->vol           = 0;
	p->voiceParam[0] = 127;
	p->voiceParam[1] = -999;
	p->voiceParam[2] = -999;
	p->voiceParam[3] = 0;
	id               = i * 2;
	{
		u8* chp = (u8*)p;

		for (i = 0; i < p->nch; i++, id++, chp += 4) {
			*(s32*)(chp + 0x28)   = 0x80000000 | id;
			*(AxCb**)(chp + 0x10) = fn_80224D14();
			if (*(AxCb**)(chp + 0x10) == NULL) {
				fn_80223424(rodata + 0x194);
				fn_802242CC(p);
				return NULL;
			}
			*(s32*)(chp + 0x18)    = fn_80224CE8(*(AxCb**)(chp + 0x10));
			p->loopLen             = fn_80224CD0(*(AxCb**)(chp + 0x10));
			*(AxObj**)(chp + 0x38) = fn_80221300(*(s32*)(chp + 0x18) * 2, p->loopLen * 2, 0);
			if (*(AxObj**)(chp + 0x38) == NULL) {
				fn_80223424(rodata + 0x1B4);
				fn_802242CC(p);
				return NULL;
			}
			*(AxObj**)(chp + 8) = fn_801E229C(31, fn_80224A88, 0);
			if (*(AxObj**)(chp + 8) == NULL) {
				fn_80223424(rodata + 0x1D0);
				fn_802242CC(p);
				return NULL;
			}
			fn_802234B0();
			fn_801E7B08(*(AxObj**)(chp + 8), 3, p->vol, p->voiceParam[1], p->voiceParam[2],
			    p->voiceParam[0], p->voiceParam[3], 0x40);
			fn_80223490();
		}
	}
	ax_SetRateMode(p);
	ax_SetRateBias(p);
	p->rateFlag = 0;
	if (p != NULL) {
		p->rate = 32000;
		for (i = 0; i < p->nch; i++) {
			fn_802234B0();
			if (p->obj[i] != NULL) {
				if (p->rateMode == 1) {
					rate[0] = 1;
					rate[1] = 0x7FA9;
				} else {
					rate[0] = 1;
					rate[1] = (s16)0x8000;
				}
				rate[2] = 0;
				rate[3] = 0;
				rate[4] = 0;
				rate[5] = 0;
				rate[6] = 0;
				fn_801E48D0(p->obj[i], p->rateBias);
				fn_801E4DF8(p->obj[i], rate);
			}
			fn_80223490();
		}
	}
	ax_SetBufferCount(p);
	if (p->nch == 2) {
		fn_80223500(p, 0, -15);
		fn_80223500(p, 1, 15);
	} else {
		fn_80223500(p, 0, 0);
	}
	p->flags = 0;
	p->stat  = 1;
	return p;
}

const s32 ax_rodata_pad3 = 0;

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

void fn_80224B1C(void)
{
	s32 i;

	if (--ax_RefCnt != 0) {
		return;
	}
	for (i = 0; i < AX_RNA_MAX; i++) {
		if (ax_Tbl[i].stat == 1) {
			fn_802242CC(&ax_Tbl[i]);
		}
	}
	memset(ax_Tbl, 0, sizeof(ax_Tbl));
	fn_80224E1C();
}

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

void fn_80224D00(void* p)
{
	if (p == NULL) {
		return;
	}
	*(s32*)p = 0;
}
