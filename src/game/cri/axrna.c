#include "types.h"
#include "cri/rnares.h"
#include "cri/axrna.h"
#include "cri/adapter.h"
#include "MSL_C/string.h"
#include "cri/sj.h"
#include "dolphin/ax.h"
#include "dolphin/arq.h"
#include "dolphin/os/OSCache.h"

#ifdef __cplusplus
extern "C" {
#endif

// CRI AXRNA for GameCube.
//
// Nineteen functions occupy 0x80223500..0x80224CD0, ending with the error
// callback setter fn_80224CB0. The following size/address accessors and destroy
// routine belong with RNARES's allocator, shutdown and initialization routines.
// This boundary is inferred from their GameCube data/call relationships, not
// claimed as an original source marker.
//
// Owned ranges are .rodata 0x80240400..0x802405F4, .data
// 0x8029BAB0..0x8029BB30 and .bss 0x80428A78..0x8042A9CC. The four bytes before
// the next .rodata and .bss units are linker alignment, not extra source data.
// The banner identifies AXRNA Ver.1.02, built May 9 2003. Adapter ends at the
// lower code/BSS boundaries; the adjacent RNARES strings and state identify
// the upper boundaries. Function names remain address labels.
//
// This is a reviewed vendor C boundary. C++ compiler mode provides the native
// declaration-order BSS pool; it does not establish historical C++ source.

typedef struct AxStream {
	/* 0x00 */ s32 flag[2];
	/* 0x08 */ s32 acc;
	/* 0x0C */ s32 total;
} AxStream;

struct AxRna {
	/* 0x00 */ s8 stat;
	/* 0x01 */ u8 flags;
	/* 0x02 */ s8 nch;
	/* 0x03 */ s8 idx;
	/* 0x04 */ s32 loopReq;
	/* 0x08 */ AxVoice* obj[2];
	/* 0x10 */ RnaResHandle* cb[2];
	/* 0x18 */ s32 loopStart[2];
	/* 0x20 */ s32 loopLen;
	/* 0x24 */ s32 rate;
	/* 0x28 */ u32 callbackId[2];
	/* 0x30 */ CriStream* strmA[2];
	/* 0x38 */ CriStream* strmB[2];
	/* 0x40 */ CriChunk bufA[2];
	/* 0x50 */ CriChunk bufB[2];
	/* 0x60 */ AxStream st[2];
	/* 0x80 */ s32 pad80;
	/* 0x84 */ s32 vol;
	/* 0x88 */ s32 pan[2];
	/* 0x90 */ s32 voiceParam[4];
	/* 0xa0 */ s16 rateMode;
	/* 0xa2 */ s16 rateFlag;
	/* 0xa4 */ s32 rateBias;
	/* 0xa8 */ ARQRequest requests[2];
};

#define AX_RNA_MAX 16

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

const char lbl_80240400[] = "\nAXRNA Ver.1.02 Build:May  9 2003 17:10:58\n";
#pragma force_active on
/* Initialization deliberately reads this version anchor; the historical qualifier is unknown. */
__declspec(export) const char* const volatile lbl_8024042C = lbl_80240400;
__declspec(export) const char lbl_80240430[]               = "OFF";
const struct {
	char on[4];
	const char* off;
	const char* onPtr;
} __declspec(export) lbl_80240434 = { "ON ", lbl_80240430, lbl_80240434.on };
#pragma force_active reset
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
	long limited;
	s32 n;

	if (p == NULL) {
		return;
	}
	if (ch >= p->nch) {
		return;
	}
	limited = v >= 15 ? 15 : v;
	n       = limited > -15 ? limited : -15;
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
	long channelVolume;
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
		channelVolume = n;
		if (p->obj[i] != NULL) {
			fn_801E89A4(p->obj[i], channelVolume);
		}
		fn_80223490();
	}
}

static inline void ax_ApplyVoiceRate(AxRna* p, s32 channel, AxVoiceRate* buf)
{
	buf->fraction   = 0;
	buf->samples[0] = 0;
	buf->samples[1] = 0;
	buf->samples[2] = 0;
	buf->samples[3] = 0;
	fn_801E48D0(p->obj[channel], p->rateBias);
	fn_801E4DF8(p->obj[channel], buf);
}

static inline void ax_FillAdjustedRate(AxVoiceRate* buf, s32 rate)
{
	u32 unsignedRate = (u32)rate;
	buf->ratioHigh   = unsignedRate / 32000;
	buf->ratioLow    = (unsignedRate << 8) / 125;
}
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
	adj     = (v * 1124L + 1124L) / 1125;
	whole   = v / 32000L;
	frac    = (v << 8) / 125;
	for (i = 0; i < p->nch; i++) {
		fn_802234B0();
		if (p->obj[i] != NULL) {
			AxVoiceRate buf;
			if (p->rateMode == 1) {
				if (v == 32000 && p->rateFlag == 0 && p != NULL) {
					p->rateBias = 0;
					p->rateFlag = 1;
				}
				ax_FillAdjustedRate(&buf, adj);
			} else {
				buf.ratioHigh = whole;
				buf.ratioLow  = frac;
			}
			ax_ApplyVoiceRate(p, i, &buf);
		}
		fn_80223490();
	}
}

static u32 ax_RefCnt;
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
	u32 i;

	for (i = 0; i < AX_RNA_MAX; i++) {
		if (ax_Tbl[i].stat == 1) {
			fn_80223820(&ax_Tbl[i]);
		}
	}
}

static inline void ax_CopyRange(CriChunk* dst, const CriChunk* src)
{
	__memcpy(dst, src, sizeof(CriChunk));
}

void fn_80223820(AxRna* p)
{
	CriChunk secondRemaining;
	CriChunk second;
	CriChunk firstRemaining;
	CriChunk first;
	CriChunk loopRemaining;
	CriChunk loopRange;
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
			if (*(AxVoice**)(objp + 8) != NULL && *(s32*)(objp + 0x60) == 0) {
				(*(CriStream**)(objp + 0x38))
				    ->vtbl->read(*(CriStream**)(objp + 0x38), 0, 0x2000, &second);
				(*(CriStream**)(objp + 0x30))
				    ->vtbl->read(*(CriStream**)(objp + 0x30), 1, second.size, &first);
				bytes = first.size < second.size ? first.size : second.size;
				bytes = bytes / 32 * 32;
				fn_80221824(&second, bytes, &second, &secondRemaining);
				(*(CriStream**)(objp + 0x38))
				    ->vtbl->unget(*(CriStream**)(objp + 0x38), 0, &secondRemaining);
				fn_80221824(&first, bytes, &first, &firstRemaining);
				(*(CriStream**)(objp + 0x30))
				    ->vtbl->unget(*(CriStream**)(objp + 0x30), 1, &firstRemaining);
				if (bytes == 0) {
					return;
				}
				if (first.size != second.size) {
					for (;;) {
					}
				}
				ax_CopyRange((CriChunk*)(bufp + 0x40), &first);
				ax_CopyRange((CriChunk*)(bufp + 0x50), &second);
				p->st[0].acc = (u32)bytes >> 1;
				DCFlushRange(((CriChunk*)(bufp + 0x40))->addr, ((CriChunk*)(bufp + 0x40))->size);
				*(s32*)(objp + 0x60) = 1;
				ARQPostRequest((ARQRequest*)(reqp + 0xA8), *(u32*)(objp + 0x28), 0, 1,
				    (u32)first.addr, (u32)second.addr, bytes, fn_80223C24);
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
					(*(CriStream**)(objp + 0x38))
					    ->vtbl->read(*(CriStream**)(objp + 0x38), 0, 0x2000, &loopRange);
					loopBytes = loopRange.size / 32 * 32;
					fn_80221824(&loopRange, loopBytes, &loopRange, &loopRemaining);
					(*(CriStream**)(objp + 0x38))
					    ->vtbl->unget(*(CriStream**)(objp + 0x38), 0, &loopRemaining);
					if (loopBytes == 0) {
						return;
					}
					ax_CopyRange((CriChunk*)(bufp + 0x50), &loopRange);
					p->st[1].acc = (u32)loopBytes >> 1;
					DCFlushRange(ax_AlignedBuf, 0x1000);
					*(s32*)(objp + 0x70) = 1;
					ARQPostRequest((ARQRequest*)(reqp + 0xA8), *(u32*)(objp + 0x28), 0, 1,
					    (u32)ax_AlignedBuf, (u32)loopRange.addr, loopBytes, fn_80223B58);
				}
			}
		}
	}
}

void fn_80223B58(u32 request)
{
	ARQRequest* cb = (ARQRequest*)request;
	s32 x;
	AxRna* p;
	s32 ch;

	x  = cb->owner & 0x7FFFFFFF;
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

void fn_80223C24(u32 request)
{
	ARQRequest* cb = (ARQRequest*)request;
	s32 x;
	AxRna* p;
	s32 ch;

	x  = cb->owner & 0x7FFFFFFF;
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
	CriChunk buf;
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
				p->strmB[i]->vtbl->read(p->strmB[i], 1, bytes, &buf);
				p->strmB[i]->vtbl->put(p->strmB[i], 0, &buf);
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
	return (s32)((u32)p->strmB[p->idx - 1]->vtbl->get(p->strmB[p->idx - 1], 0) >> 1);
}

s32 fn_80223ED0(AxRna* p)
{
	if (p == NULL) {
		return -1;
	}
	return 4096 - (s32)((u32)p->strmA[p->idx + 1]->vtbl->get(p->strmA[p->idx + 1], 0) >> 1);
}

void fn_80223F2C(AxRna* p, s32 sw)
{
	s32 cur;
	s32 i;
	u16 endLo;

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
				s32 start   = p->loopStart[i];
				s32 current = p->loopStart[i];
				s32 end     = start + p->loopLen - 1;
				buf[0]      = 1;
				buf[1]      = 10;
				buf[2]      = (s16)(start >> 16);
				buf[3]      = (s16)start;
				endLo       = (s16)end;
				buf[4]      = (s16)(end >> 16);
				buf[5]      = endLo;
				buf[6]      = (s16)(current >> 16);
				buf[7]      = (s16)current;
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
	s32 i;
	s32 j;
	long delay;

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
			memset(&root->bufA[i], 0, sizeof(root->bufA[i]));
			memset(&root->bufB[i], 0, sizeof(root->bufB[i]));
			memset(&root->requests[i], 0, sizeof(ARQRequest));
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
		for (i = 0; i < root->idx; i++) {
			for (j = 0; j < 200; j++) {
				if (*(volatile s32*)&root->st[0].flag[i] == 0) {
					break;
				}
				for (delay = 0; delay < 100000; delay++) {
				}
			}
			if (j == 200) {
				fn_80223424(rodata + 0x64);
				return;
			}
			for (j = 0; j < 200; j++) {
				if (*(volatile s32*)&root->st[1].flag[i] == 0) {
					break;
				}
				for (delay = 0; delay < 100000; delay++) {
				}
			}
			if (j == 200) {
				fn_80223424(rodata + 0x9C);
				return;
			}
		}
		root->flags &= 2;
	} else {
		fn_80223424(rodata + 0xD4);
	}
}

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

static inline void ax_SetRateMode(AxRna* p)
{
	s32 mode = ax_X[0];
	if (p == NULL) {
		return;
	}
	p->rateMode = mode;
}

static inline void ax_SetRateBias(AxRna* p)
{
	s32 bias = ax_RateBias;
	if (p == NULL) {
		return;
	}
	p->rateBias = bias;
	p->rateFlag = 1;
}

static inline void ax_SetBufferCount(AxRna* p)
{
	if (p == NULL) {
		return;
	}
	p->pad80 = 16;
}

AxRna* fn_8022439C(CriStream** sj, s32 maxnch)
{
	const char* rodata = lbl_80240400;
	AxRna* p;
	u32 i;
	u32 slot;

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
	for (slot = 0; slot < AX_RNA_MAX; slot++) {
		if (ax_Tbl[slot].stat == 0) {
			break;
		}
	}
	if (slot == AX_RNA_MAX) {
		fn_80223424(rodata + 0x170);
		return NULL;
	}
	p      = &ax_Tbl[slot];
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
	{

		for (i = 0; i < p->nch; i++) {
			p->callbackId[i] = 0x80000000 | (slot * 2 + i);
			if ((p->cb[i] = fn_80224D14()) == NULL) {
				fn_80223424(rodata + 0x194);
				fn_802242CC(p);
				return NULL;
			}
			p->loopStart[i] = fn_80224CE8(p->cb[i]);
			p->loopLen      = fn_80224CD0(p->cb[i]);
			p->strmB[i]     = fn_80221300((void*)(p->loopStart[i] * 2), p->loopLen * 2, 0);
			if (p->strmB[i] == NULL) {
				fn_80223424(rodata + 0x1B4);
				fn_802242CC(p);
				return NULL;
			}
			if ((p->obj[i] = fn_801E229C(31, fn_80224A88, 0)) == NULL) {
				fn_80223424(rodata + 0x1D0);
				fn_802242CC(p);
				return NULL;
			}
			fn_802234B0();
			if (p->obj[i] != NULL) {
				fn_801E7B08(p->obj[i], 3, p->vol, p->voiceParam[1], p->voiceParam[2], 0x40,
				    p->voiceParam[0], p->voiceParam[3]);
			}
			fn_80223490();
		}
	}
	ax_SetRateMode(p);
	ax_SetRateBias(p);
	p->rateFlag = 0;
	fn_80223660(p, 48000);
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

void fn_80224A88(AxVoice* obj)
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
	(void)lbl_8024042C;
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

#ifdef __cplusplus
}
#endif
