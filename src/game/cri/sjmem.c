#include "cri/sjmem.h"
#include "cri/sjcrs.h"
#include "MSL_C/string.h"

// CRI SJMEM: the thirteen-function memory-backed stream implementation,
// 0x802205DC..0x80220BF0, with its UUID, vtable, 32-object pool and counter.
// This source boundary is inferred from GC references and correlated PS2
// symbolic metadata. C++ mode preserves declaration-order private BSS.
// All functions, owned sections, symbols and relocations match natively.

#define SJMEM_MAX_OBJ 32
#define SJ_ERR_PRM    (-3)

typedef struct SjInterface {
	void* queryInterface;
	void* addRef;
	void* release;
	void (*destroy)(SjmemObj* sjmem);
	const void* (*getUuid)(SjmemObj* sjmem);
	void (*reset)(SjmemObj* sjmem);
	void (*getChunk)(SjmemObj* sjmem, s32 id, s32 size, CriChunk* chunk);
	void (*ungetChunk)(SjmemObj* sjmem, s32 id, CriChunk* chunk);
	void (*putChunk)(SjmemObj* sjmem, s32 id, CriChunk* chunk);
	s32 (*getNumData)(SjmemObj* sjmem, s32 id);
	s32 (*isGetChunk)(SjmemObj* sjmem, s32 id, s32 size, s32* readSize);
	void (*entryErrFunc)(SjmemObj* sjmem, SjErrorFunc callback, void* object);
} SjInterface;

struct SjmemObj {
	const SjInterface* interface;
	s32 used;
	const void* uuid;
	s32 available;
	s32 offset;
	s8* buffer;
	s32 bufferSize;
	SjErrorFunc errorCallback;
	void* errorObject;
};

typedef struct SjUuid {
	u32 data1;
	u16 data2;
	u16 data3;
	u8 data4[8];
} SjUuid;

static const SjUuid sjmem_uuid
    = { 0xDD9EEE41, 0x1679, 0x11D2, { 0x93, 0x6C, 0x00, 0x60, 0x08, 0x94, 0x48, 0xBC } };
static const char lbl_8023FF60[] = "SJMEM Error";

static SjInterface sjmem_vtbl = {
	NULL,
	NULL,
	NULL,
	fn_802209C4,
	fn_802209BC,
	fn_8022099C,
	fn_80220858,
	fn_80220694,
	fn_802207C4,
	fn_80220940,
	fn_802205DC,
	fn_802209B0,
};

static s32 sjmem_init_cnt;
static SjmemObj sjmem_obj[SJMEM_MAX_OBJ];

s32 fn_802205DC(SjmemObj* sjmem, s32 id, s32 size, s32* readSize)
{
	s32 available;

	fn_80220590();
	if (id == 0) {
		available = 0;
	} else if (id == 1) {
		available = sjmem->available < size ? sjmem->available : size;
	} else {
		available = 0;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	*readSize = available;
	fn_80220544();
	if (available == size) {
		return 1;
	}
	return 0;
}

void fn_80220694(SjmemObj* sjmem, s32 id, CriChunk* chunk)
{
	s32 offset;
	s32 available;

	if (chunk->size <= 0 || chunk->addr == NULL) {
		return;
	}
	fn_80220590();
	if (id == 0) {
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	} else if (id == 1) {
		s32 length   = chunk->size;
		s32 position = sjmem->offset;
		offset       = position;
		offset -= length;
		offset        = position - length > 0 ? offset : 0;
		sjmem->offset = offset;
		available     = sjmem->available + chunk->size;
		if (sjmem->bufferSize < available) {
			available = sjmem->bufferSize;
		}
		sjmem->available = available;
		if (offset != chunk->addr - sjmem->buffer && sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	} else {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_802207C4(SjmemObj* sjmem, s32 id, CriChunk* chunk)
{
	if (chunk->size <= 0 || chunk->addr == NULL) {
		return;
	}
	fn_80220590();
	if ((u32)id > 1) {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80220858(SjmemObj* sjmem, s32 id, s32 size, CriChunk* chunk)
{
	fn_80220590();
	if (id == 0) {
		chunk->size = 0;
		chunk->addr = NULL;
	} else if (id == 1) {
		chunk->size = sjmem->available < size ? sjmem->available : size;
		chunk->addr = sjmem->buffer + sjmem->offset;
		sjmem->offset += chunk->size;
		sjmem->available -= chunk->size;
	} else {
		chunk->size = 0;
		chunk->addr = NULL;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

s32 fn_80220940(SjmemObj* sjmem, s32 id)
{
	if (id == 1) {
		return sjmem->available;
	}
	if (id == 0) {
		return 0;
	}
	if (sjmem->errorCallback != NULL) {
		sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
	}
	return 0;
}

void fn_8022099C(SjmemObj* sjmem)
{
	sjmem->available = sjmem->bufferSize;
	sjmem->offset    = 0;
}

void fn_802209B0(SjmemObj* sjmem, SjErrorFunc callback, void* object)
{
	sjmem->errorCallback = callback;
	sjmem->errorObject   = object;
}

const void* fn_802209BC(SjmemObj* sjmem)
{
	return sjmem->uuid;
}

void fn_802209C4(SjmemObj* sjmem)
{
	if (sjmem != NULL) {
		memset(sjmem, 0, sizeof(*sjmem));
		sjmem->used = 0;
	}
}

CriStream* fn_80220A04(void* buffer, s32 size)
{
	SjmemObj* sjmem;
	s32 i;

	for (i = 0; i < SJMEM_MAX_OBJ; i++) {
		if (sjmem_obj[i].used == 0) {
			break;
		}
	}
	if (i == SJMEM_MAX_OBJ) {
		return NULL;
	}
	sjmem                = &sjmem_obj[i];
	sjmem->used          = 1;
	sjmem->interface     = &sjmem_vtbl;
	sjmem->buffer        = (s8*)buffer;
	sjmem->bufferSize    = size;
	sjmem->uuid          = &sjmem_uuid;
	sjmem->errorCallback = fn_80220BC8;
	sjmem->errorObject   = sjmem;
	fn_8022099C(sjmem);
	return (CriStream*)sjmem;
}

void fn_80220B2C(void)
{
	sjmem_init_cnt--;
	if (sjmem_init_cnt == 0) {
		memset(sjmem_obj, 0, sizeof(sjmem_obj));
	}
}

void fn_80220B74(void)
{
	if (sjmem_init_cnt == 0) {
		memset(sjmem_obj, 0, sizeof(sjmem_obj));
	}
	sjmem_init_cnt++;
}

void fn_80220BC8(void* object, s32 error)
{
	fn_80221888(lbl_8023FF60);
}
