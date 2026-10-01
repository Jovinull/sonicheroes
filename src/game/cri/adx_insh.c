// adx_insh: builds an SFA header into an ADXT input stream via ADXSJE.
// .text 0x802136F4-0x8021389C (1 function), .bss 0x80411360-0x804117A0
// (adxt_dmybuf, adxt_hdbuf).
// Boundary: MKD adx_insh.o; both buffers are used only here.

#include "types.h"
#include "MSL_C/string.h"

typedef struct SjObj SjObj;
typedef struct SjChunk {
	s8* data;
	s32 len;
} SjChunk;
typedef struct SjIf {
	void* qi;
	void* addref;
	void* release;
	void (*Destroy)(SjObj* sj);
	void* getuuid;
	void (*Reset)(SjObj* sj);
	void (*GetChunk)(SjObj* sj, s32 id, s32 nbyte, SjChunk* ck);
	void (*UngetChunk)(SjObj* sj, s32 id, SjChunk* ck);
	void (*PutChunk)(SjObj* sj, s32 id, SjChunk* ck);
	s32 (*GetNumData)(SjObj* sj, s32 id);
} SjIf;
struct SjObj {
	SjIf* vtbl;
};

typedef struct AdxtObj {
	u8 pad0[0x14];
	SjObj* sji;
} AdxtObj;

typedef struct AdxsjeObj AdxsjeObj;

extern void ADXSJE_Init(void);
extern void ADXSJE_Finish(void);
extern AdxsjeObj* ADXSJE_Create(s32 nch, SjObj** sji, SjObj* sjo);
extern void ADXSJE_Destroy(AdxsjeObj* sje);
extern void ADXSJE_SetConfigSfa(AdxsjeObj* sje, s32 nch, s32 sfreq, s32 nsmpl);
extern void ADXSJE_Start(AdxsjeObj* sje);
extern void ADXSJE_Stop(AdxsjeObj* sje);
extern void ADXSJE_ExecServer(void);
extern SjObj* fn_80221300(void* buf, s32 bsize, s32 xsize); /* SJRBF_Create */
extern SjObj* fn_80220A04(void* buf, s32 bsize);            /* SJMEM_Create */

u8 adxt_hdbuf[0x400];
u8 adxt_dmybuf[0x40];

void ADXT_InsertHdrSfa(AdxtObj* adxt, s32 nch, s32 sfreq, s32 nsmpl)
{
	SjObj* sji[2];
	SjChunk ck;
	SjChunk ckd;
	SjObj* sjh;
	SjObj* sjd;
	AdxsjeObj* sje;

	ADXSJE_Init();
	sjh    = fn_80221300(adxt_hdbuf, sizeof(adxt_hdbuf), 0);
	sji[0] = fn_80220A04(adxt_dmybuf, 0x20);
	sji[1] = fn_80220A04(adxt_dmybuf + 0x20, 0x20);
	sjd    = adxt->sji;
	sje    = ADXSJE_Create(2, sji, sjh);
	ADXSJE_SetConfigSfa(sje, nch, sfreq, nsmpl);
	ADXSJE_Start(sje);
	ADXSJE_ExecServer();
	sjh->vtbl->GetChunk(sjh, 1, sizeof(adxt_hdbuf), &ck);
	if (ck.len == 0) {
		for (;;) {
		}
	}
	sjd->vtbl->GetChunk(sjd, 0, ck.len, &ckd);
	if (ckd.len < ck.len) {
		for (;;) {
		}
	}
	memcpy(ckd.data, ck.data, ck.len);
	sjh->vtbl->PutChunk(sjh, 0, &ck);
	sjd->vtbl->PutChunk(sjd, 1, &ckd);
	ADXSJE_Stop(sje);
	ADXSJE_Destroy(sje);
	sjh->vtbl->Destroy(sjh);
	sji[1]->vtbl->Destroy(sji[1]);
	sji[0]->vtbl->Destroy(sji[0]);
	ADXSJE_Finish();
}
