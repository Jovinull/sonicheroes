#include "types.h"

#define SJ_MAX_OBJ 256
#define SJ_ERR_PRM (-3)

typedef struct SjChunk {
	s8* data;
	s32 length;
} SjChunk;

typedef struct SjObj SjObj;
typedef void (*SjErrorFunc)(void* object, s32 error);

typedef struct SjInterface {
	void* queryInterface;
	void* addRef;
	void* release;
	void (*destroy)(SjObj* sj);
	const void* (*getUuid)(SjObj* sj);
	void (*reset)(SjObj* sj);
	void (*getChunk)(SjObj* sj, s32 id, s32 size, SjChunk* chunk);
	void (*ungetChunk)(SjObj* sj, s32 id, SjChunk* chunk);
	void (*putChunk)(SjObj* sj, s32 id, SjChunk* chunk);
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

void* memset(void* destination, s32 value, u32 size);
void* memcpy(void* destination, const void* source, u32 size);
void fn_80220544(void);
void fn_80220590(void);
void fn_8022154C(void* object, s32 error);

s32 fn_80220C20(SjObj* sj, s32 id, s32 size, s32* readSize);
void fn_80220D2C(SjObj* sj, s32 id, SjChunk* chunk);
void fn_80220ED8(SjObj* sj, s32 id, SjChunk* chunk);
void fn_80221034(SjObj* sj, s32 id, s32 size, SjChunk* chunk);
s32 fn_802211E8(SjObj* sj, s32 id);
void fn_80221244(SjObj* sj);
void fn_8022129C(SjObj* sj, SjErrorFunc callback, void* object);
const void* fn_802212A8(SjObj* sj);
void fn_802212B0(SjObj* sj);

static const char lbl_8023FF70[]      = "\nSJ/GC Ver.6.14 Build:May  9 2003 17:10:13\n";
static const char* const lbl_8023FF9C = lbl_8023FF70;
static const SjUuid lbl_8023FFA0      = {
	{ 0x3B9A9E81, 0x0DBB11D2, 0xA6BF4445, 0x53540000 },
};

static SjInterface lbl_8029B858 = {
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

static s32 lbl_804230A0;
static SjObj lbl_804230A4[SJ_MAX_OBJ];
static u32 gap_09_804270A4_bss;

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
	return available == size;
}

void fn_80220D2C(SjObj* sj, s32 id, SjChunk* chunk)
{
	s32 expected;
	s32 actual;

	if (chunk->length <= 0 || chunk->data == NULL) {
		return;
	}
	fn_80220590();
	if (id == 0) {
		expected = (sj->offset0 + sj->bufferSize - chunk->length) % sj->bufferSize;
		actual   = (chunk->data - sj->buffer) % sj->bufferSize;
		if (expected == actual) {
			sj->offset0 = expected;
			sj->numData0 += chunk->length;
		} else if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
		sj->totals[0][0] -= chunk->length;
	} else if (id == 1) {
		expected = (sj->offset1 + sj->bufferSize - chunk->length) % sj->bufferSize;
		actual   = (chunk->data - sj->buffer) % sj->bufferSize;
		if (expected == actual) {
			sj->offset1 = expected;
			sj->numData1 += chunk->length;
		} else if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
		sj->totals[1][0] -= chunk->length;
	} else {
		chunk->length = 0;
		chunk->data   = NULL;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80220ED8(SjObj* sj, s32 id, SjChunk* chunk)
{
	s32 length;

	if (chunk->length <= 0 || chunk->data == NULL) {
		return;
	}
	fn_80220590();
	if (id == 1) {
		s32 offset;

		sj->numData1 += chunk->length;
		offset = chunk->data - sj->buffer;
		if (offset < sj->margin) {
			length = sj->margin - offset;
			if (chunk->length < length) {
				length = chunk->length;
			}
			memcpy(sj->bufferSize + (sj->buffer + offset), chunk->data, length);
		}
		if (chunk->data - sj->buffer + chunk->length > sj->bufferSize) {
			length = chunk->data - sj->buffer + chunk->length - sj->bufferSize;
			length = chunk->length < length ? chunk->length : length;
			memcpy(sj->buffer, sj->buffer + (chunk->data - sj->buffer + chunk->length - length),
			    length);
		}
		sj->totals[1][1] += chunk->length;
	} else if (id == 0) {
		sj->numData0 += chunk->length;
		sj->totals[0][1] += chunk->length;
	} else {
		chunk->length = 0;
		chunk->data   = NULL;
		if (sj->errorCallback != NULL) {
			sj->errorCallback(sj->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80221034(SjObj* sj, s32 id, s32 size, SjChunk* chunk)
{
	s32 available;

	fn_80220590();
	if (id == 0) {
		available     = sj->numData0 < sj->margin + (sj->bufferSize - sj->offset0)
		    ? sj->numData0
		    : sj->margin + (sj->bufferSize - sj->offset0);
		chunk->length = available;
		chunk->length = chunk->length < size ? chunk->length : size;
		chunk->data   = sj->buffer + sj->offset0;
		sj->offset0   = (sj->offset0 + chunk->length) % sj->bufferSize;
		sj->numData0 -= chunk->length;
		sj->totals[0][0] += chunk->length;
	} else if (id == 1) {
		available     = sj->numData1 < sj->margin + (sj->bufferSize - sj->offset1)
		    ? sj->numData1
		    : sj->margin + (sj->bufferSize - sj->offset1);
		chunk->length = available;
		chunk->length = chunk->length < size ? chunk->length : size;
		chunk->data   = sj->buffer + sj->offset1;
		sj->offset1   = (sj->offset1 + chunk->length) % sj->bufferSize;
		sj->numData1 -= chunk->length;
		sj->totals[1][0] += chunk->length;
	} else {
		chunk->length = 0;
		chunk->data   = NULL;
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

SjObj* fn_80221300(s8* buffer, s32 bufferSize, s32 margin)
{
	SjObj* sj;
	s32 i;

	fn_80220590();
	for (i = 0; i < SJ_MAX_OBJ; i++) {
		if (lbl_804230A4[i].used == 0) {
			break;
		}
	}
	if (i == SJ_MAX_OBJ) {
		sj = NULL;
	} else {
		sj                = &lbl_804230A4[i];
		sj->used          = 1;
		sj->interface     = &lbl_8029B858;
		sj->buffer        = buffer;
		sj->bufferSize    = bufferSize;
		sj->margin        = margin;
		sj->uuid          = &lbl_8023FFA0;
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
	return sj;
}

void fn_80221498(void)
{
	fn_80220590();
	lbl_804230A0--;
	if (lbl_804230A0 == 0) {
		memset(lbl_804230A4, 0, sizeof(lbl_804230A4));
	}
	fn_80220544();
}

void fn_802214E8(void)
{
	(void)*(const char* volatile*)&lbl_8023FF9C;
	fn_80220590();
	if (lbl_804230A0 == 0) {
		memset(lbl_804230A4, 0, sizeof(lbl_804230A4));
	}
	lbl_804230A0++;
	fn_80220544();
}
