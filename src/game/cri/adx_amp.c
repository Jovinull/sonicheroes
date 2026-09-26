// adx_amp: ADXAMP (amplitude extraction) handle functions kept by the linker.
// .text 0x802125A0-0x802127B0 (4 functions); no data.
// Boundary: MKD adx_amp.o holds exactly these four in this order, between the
// ADXB parsers and adx_crs.

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
	void* destroy;
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

typedef struct AdxampObj {
	s8 used;
	s8 stat;
	s8 maxnch;
	s8 rsv;
	SjObj* sji[2];
	SjObj* sjo[2];
	s32 total_exsmpl[2];
	s32 nch;
	s32 sfreq;
	f32 frm_len;
	f32 frm_prd;
	s32 frm_no;
} AdxampObj;

extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);

void ADXAMP_Destroy(AdxampObj* amp)
{
	if (amp != NULL) {
		ADXCRS_Lock();
		memset(amp, 0, sizeof(AdxampObj));
		ADXCRS_Unlock();
	}
}

void ADXAMP_Start(AdxampObj* amp)
{
	SjChunk ck;
	SjObj* sj;
	s32 ch;

	for (ch = 0; ch < amp->maxnch; ch++) {
		amp->total_exsmpl[ch] = 0;
	}
	amp->frm_no = 0;
	for (ch = 0; ch < amp->maxnch; ch++) {
		sj = amp->sji[ch];
		sj->vtbl->Reset(sj);
		sj->vtbl->GetChunk(sj, 0, sj->vtbl->GetNumData(sj, 0), &ck);
		memset(ck.data, 0, ck.len);
		sj->vtbl->UngetChunk(sj, 0, &ck);
	}
	for (ch = 0; ch < amp->maxnch; ch++) {
		sj = amp->sjo[ch];
		sj->vtbl->Reset(sj);
		sj->vtbl->GetChunk(sj, 0, sj->vtbl->GetNumData(sj, 0), &ck);
		memset(ck.data, 0, ck.len);
		sj->vtbl->UngetChunk(sj, 0, &ck);
	}
	amp->stat = 2;
}

void ADXAMP_Stop(AdxampObj* amp)
{
	amp->stat = 0;
}

void ADXAMP_SetSfreq(AdxampObj* amp, s32 sfreq)
{
	amp->sfreq = sfreq;
}
