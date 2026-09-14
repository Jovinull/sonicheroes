#include "cri/sjrbf.h"
#include "cri/sjcrs.h"
#include "MSL_C/string.h"

// CRI ring-buffer stream implementation. Correlated API/data names identify
// this seventeen-function run; its source boundary is inferred from the GC
// callback, vtable and private storage relationships, not a source marker.
// The vendor C boundary uses C++ mode for declaration-order private BSS.

#define SJ_MAX_OBJ 256
#define SJ_ERR_PRM (-3)

typedef struct SjInterface {
	void* queryInterface;
	void* addRef;
	void* release;
	void (*destroy)(SjObj* sj);
	const void* (*getUuid)(SjObj* sj);
	void (*reset)(SjObj* sj);
	void (*getChunk)(SjObj* sj, s32 id, s32 size, CriChunk* chunk);
	void (*ungetChunk)(SjObj* sj, s32 id, CriChunk* chunk);
	void (*putChunk)(SjObj* sj, s32 id, CriChunk* chunk);
	s32 (*getNumData)(SjObj* sj, s32 id);
	s32 (*isGetChunk)(SjObj* sj, s32 id, s32 size, s32* readSize);
	void (*entryErrFunc)(SjObj* sj, SjErrorFunc callback, void* object);
} SjInterface;

struct SjObj {
	const SjInterface* interface;
	s32 used;
	const void* uuid;
	s32 numData1;
	s32 numData0;
	s32 offset0;
	s32 offset1;
	s8* buffer;
	s32 bufferSize;
	s32 margin;
	s32 totals[2][2];
	SjErrorFunc errorCallback;
	void* errorObject;
};

typedef struct SjUuid {
	u32 data[4];
} SjUuid;

static const char lbl_8023FF70[]  = "\nSJ/GC Ver.6.14 Build:May  9 2003 17:10:13\n";
static const char* const sj_build = lbl_8023FF70;
static const SjUuid sjrbf_uuid    = {
	{ 0x3B9A9E81, 0x0DBB11D2, 0xA6BF4445, 0x53540000 },
};

static const char lbl_8023FFB0[] = "SJRBF Error";

static SjInterface sjrbf_vtbl = {
	NULL,
	NULL,
	NULL,
	fn_802212B0,
	fn_802212A8,
	fn_80221244,
	fn_80221034,
	fn_80220D2C,
	fn_80220ED8,
	fn_802211E8,
	fn_80220C20,
	fn_8022129C,
};

static s32 sjrbf_init_cnt;
static SjObj sjrbf_obj[SJ_MAX_OBJ];

s32 fn_80220BF0(SjObj* sj, s32 id, s32 index)
{
	return sj->totals[id][index];
}

s32 fn_80220C08(SjObj* sj)
{
	return sj->margin;
}

s32 fn_80220C10(SjObj* sj)
{
	return sj->bufferSize;
}

s8* fn_80220C18(SjObj* sj)
{
	return sj->buffer;
}

s32 fn_80220C20(SjObj* sj, s32 id, s32 size, s32* readSize)
{
	s32 available;

	fn_80220590();
	if (id == 0) {
		available = sj->numData0 < sj->margin + (sj->bufferSize - sj->offset0)
		    ? sj->numData0
		    : sj->margin + (sj->bufferSize - sj->offset0);
		available = available < size ? available : size;
	} else if (id == 1) {
		available = sj->numData1 < sj->margin + (sj->bufferSize - sj->offset1)
		    ? sj->numData1
		    : sj->margin + (sj->bufferSize - sj->offset1);
		available = available < size ? available : size;
	} else {
		available = 0;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	*readSize = available;
	fn_80220544();
	if (available == size)
		return 1;
	return 0;
}

void fn_80220D2C(SjObj* sj, s32 id, CriChunk* chunk)
{
	s32 expected;
	s32 actual;

	if (chunk->size <= 0 || chunk->addr == NULL) {
		return;
	}
	fn_80220590();
	if (id == 0) {
		expected = (sj->offset0 + sj->bufferSize - chunk->size) % sj->bufferSize;
		actual   = ((s8*)chunk->addr - sj->buffer) % sj->bufferSize;
		if (expected == actual) {
			sj->offset0 = expected;
			sj->numData0 += chunk->size;
		} else if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
		sj->totals[0][0] -= chunk->size;
	} else if (id == 1) {
		expected = (sj->offset1 + sj->bufferSize - chunk->size) % sj->bufferSize;
		actual   = ((s8*)chunk->addr - sj->buffer) % sj->bufferSize;
		if (expected == actual) {
			sj->offset1 = expected;
			sj->numData1 += chunk->size;
		} else if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
		sj->totals[1][0] -= chunk->size;
	} else {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80220ED8(SjObj* sj, s32 id, CriChunk* chunk)
{
	s32 length;

	if (chunk->size <= 0 || chunk->addr == NULL) {
		return;
	}
	fn_80220590();
	if (id == 1) {
		s32 offset;

		sj->numData1 += chunk->size;
		offset = (s8*)chunk->addr - sj->buffer;
		if (offset < sj->margin) {
			length = sj->margin - offset;
			if (chunk->size < length) {
				length = chunk->size;
			}
			memcpy(sj->buffer + (sj->bufferSize + offset), chunk->addr, length);
		}
		if ((s8*)chunk->addr - sj->buffer + chunk->size > sj->bufferSize) {
			length = (s8*)chunk->addr - sj->buffer + chunk->size - sj->bufferSize;
			length = chunk->size < length ? chunk->size : length;
			memcpy(sj->buffer, sj->buffer + ((s8*)chunk->addr - sj->buffer + chunk->size - length),
			    length);
		}
		sj->totals[1][1] += chunk->size;
	} else if (id == 0) {
		sj->numData0 += chunk->size;
		sj->totals[0][1] += chunk->size;
	} else {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80221034(SjObj* sj, s32 id, s32 size, CriChunk* chunk)
{
	s32 available;

	fn_80220590();
	if (id == 0) {
		available   = sj->numData0 < sj->margin + (sj->bufferSize - sj->offset0)
		    ? sj->numData0
		    : sj->margin + (sj->bufferSize - sj->offset0);
		chunk->size = available;
		chunk->size = chunk->size < size ? chunk->size : size;
		chunk->addr = sj->buffer + sj->offset0;
		sj->offset0 = (sj->offset0 + chunk->size) % sj->bufferSize;
		sj->numData0 -= chunk->size;
		sj->totals[0][0] += chunk->size;
	} else if (id == 1) {
		available   = sj->numData1 < sj->margin + (sj->bufferSize - sj->offset1)
		    ? sj->numData1
		    : sj->margin + (sj->bufferSize - sj->offset1);
		chunk->size = available;
		chunk->size = chunk->size < size ? chunk->size : size;
		chunk->addr = sj->buffer + sj->offset1;
		sj->offset1 = (sj->offset1 + chunk->size) % sj->bufferSize;
		sj->numData1 -= chunk->size;
		sj->totals[1][0] += chunk->size;
	} else {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

s32 fn_802211E8(SjObj* sj, s32 id)
{
	if (id == 1) {
		return sj->numData1;
	}
	if (id == 0) {
		return sj->numData0;
	}
	if (sj->errorCallback != NULL) {
		sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
	}
	return 0;
}

void fn_80221244(SjObj* sj)
{
	fn_80220590();
	sj->numData1     = 0;
	sj->numData0     = sj->bufferSize;
	sj->offset0      = 0;
	sj->offset1      = 0;
	sj->totals[0][0] = 0;
	sj->totals[0][1] = 0;
	sj->totals[1][0] = 0;
	sj->totals[1][1] = 0;
	fn_80220544();
}

void fn_8022129C(SjObj* sj, SjErrorFunc callback, void* object)
{
	sj->errorCallback = callback;
	sj->errorObject   = object;
}

const void* fn_802212A8(SjObj* sj)
{
	return sj->uuid;
}

void fn_802212B0(SjObj* sj)
{
	fn_80220590();
	if (sj != NULL) {
		memset(sj, 0, sizeof(*sj));
		sj->used = 0;
	}
	fn_80220544();
}

CriStream* fn_80221300(void* buffer, s32 bufferSize, s32 margin)
{
	SjObj* sj;
	s32 i;

	fn_80220590();
	for (i = 0; i < SJ_MAX_OBJ; i++) {
		if (sjrbf_obj[i].used == 0) {
			break;
		}
	}
	if (i == SJ_MAX_OBJ) {
		sj = NULL;
	} else {
		sj                = &sjrbf_obj[i];
		sj->used          = 1;
		sj->interface     = &sjrbf_vtbl;
		sj->buffer        = (s8*)buffer;
		sj->bufferSize    = bufferSize;
		sj->margin        = margin;
		sj->uuid          = &sjrbf_uuid;
		sj->errorCallback = fn_8022154C;
		sj->errorObject   = sj;
		fn_80220590();
		sj->numData1     = 0;
		sj->numData0     = sj->bufferSize;
		sj->offset0      = 0;
		sj->offset1      = 0;
		sj->totals[0][0] = 0;
		sj->totals[0][1] = 0;
		sj->totals[1][0] = 0;
		sj->totals[1][1] = 0;
		fn_80220544();
	}
	fn_80220544();
	return (CriStream*)sj;
}

void fn_80221498(void)
{
	fn_80220590();
	sjrbf_init_cnt--;
	if (sjrbf_init_cnt == 0) {
		memset(sjrbf_obj, 0, sizeof(sjrbf_obj));
	}
	fn_80220544();
}

void fn_802214E8(void)
{
	(void)*(const char* volatile*)&sj_build;
	fn_80220590();
	if (sjrbf_init_cnt == 0) {
		memset(sjrbf_obj, 0, sizeof(sjrbf_obj));
	}
	sjrbf_init_cnt++;
	fn_80220544();
}

void fn_8022154C(void* object, s32 error)
{
	fn_80221888(lbl_8023FFB0);
}
