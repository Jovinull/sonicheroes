#include "types.h"

// CRI SJMEM: a fixed memory-backed SJ implementation. The complete unit is
// the twelve-function run at 0x802205DC..0x80220BF0 and its exclusive UUID,
// vtable, 32-object pool, and initialization count.

#define SJMEM_MAX_OBJ 32
#define SJ_ERR_PRM    (-3)

typedef struct SjChunk {
	s8* data;
	s32 length;
} SjChunk;

typedef struct SjmemObj SjmemObj;
typedef void (*SjErrorFunc)(void* object, s32 error);

typedef struct SjInterface {
	void* queryInterface;
	void* addRef;
	void* release;
	void (*destroy)(SjmemObj* sjmem);
	const void* (*getUuid)(SjmemObj* sjmem);
	void (*reset)(SjmemObj* sjmem);
	void (*getChunk)(SjmemObj* sjmem, s32 id, s32 size, SjChunk* chunk);
	void (*ungetChunk)(SjmemObj* sjmem, s32 id, SjChunk* chunk);
	void (*putChunk)(SjmemObj* sjmem, s32 id, SjChunk* chunk);
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

void* memset(void* destination, s32 value, u32 size);
void fn_80220544(void);
void fn_80220590(void);
void fn_80221888(const char* message);

s32 fn_802205DC(SjmemObj* sjmem, s32 id, s32 size, s32* readSize);
void fn_80220694(SjmemObj* sjmem, s32 id, SjChunk* chunk);
void fn_802207C4(SjmemObj* sjmem, s32 id, SjChunk* chunk);
void fn_80220858(SjmemObj* sjmem, s32 id, s32 size, SjChunk* chunk);
s32 fn_80220940(SjmemObj* sjmem, s32 id);
void fn_8022099C(SjmemObj* sjmem);
void fn_802209B0(SjmemObj* sjmem, SjErrorFunc callback, void* object);
const void* fn_802209BC(SjmemObj* sjmem);
void fn_802209C4(SjmemObj* sjmem);
void fn_80220BC8(void* object, s32 error);

static const SjUuid lbl_8023FF50
    = { 0xDD9EEE41, 0x1679, 0x11D2, { 0x93, 0x6C, 0x00, 0x60, 0x08, 0x94, 0x48, 0xBC } };
static const char lbl_8023FF60[] = "SJMEM Error";
const u32 gap_06_8023FF6C_rodata = 0;

static SjInterface lbl_8029B828 = {
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

static s32 lbl_80422C18;
static SjmemObj lbl_80422C1C[SJMEM_MAX_OBJ];
static u32 gap_09_8042309C_bss;

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
	return available == size;
}

void fn_80220694(SjmemObj* sjmem, s32 id, SjChunk* chunk)
{
	s32 offset;
	s32 available;

	if (chunk->length <= 0 || chunk->data == NULL) {
		return;
	}
	fn_80220590();
	if (id == 0) {
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	} else if (id == 1) {
		offset        = -chunk->length + sjmem->offset;
		offset        = offset > 0 ? offset : 0;
		sjmem->offset = offset;
		available     = sjmem->available + chunk->length;
		if (sjmem->bufferSize < available) {
			available = sjmem->bufferSize;
		}
		sjmem->available = available;
		if (offset != chunk->data - sjmem->buffer && sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	} else {
		chunk->length = 0;
		chunk->data   = NULL;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_802207C4(SjmemObj* sjmem, s32 id, SjChunk* chunk)
{
	if (chunk->length <= 0 || chunk->data == NULL) {
		return;
	}
	fn_80220590();
	if ((u32)id > 1) {
		chunk->length = 0;
		chunk->data   = NULL;
		if (sjmem->errorCallback != NULL) {
			sjmem->errorCallback(sjmem->errorObject, SJ_ERR_PRM);
		}
	}
	fn_80220544();
}

void fn_80220858(SjmemObj* sjmem, s32 id, s32 size, SjChunk* chunk)
{
	fn_80220590();
	if (id == 0) {
		chunk->length = 0;
		chunk->data   = NULL;
	} else if (id == 1) {
		chunk->length = sjmem->available < size ? sjmem->available : size;
		chunk->data   = sjmem->buffer + sjmem->offset;
		sjmem->offset += chunk->length;
		sjmem->available -= chunk->length;
	} else {
		chunk->length = 0;
		chunk->data   = NULL;
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

SjmemObj* fn_80220A04(s8* buffer, s32 size)
{
	SjmemObj* sjmem;
	s32 i;

	for (i = 0; i < SJMEM_MAX_OBJ; i++) {
		if (lbl_80422C1C[i].used == 0) {
			break;
		}
	}
	if (i == SJMEM_MAX_OBJ) {
		return NULL;
	}
	sjmem                = &lbl_80422C1C[i];
	sjmem->used          = 1;
	sjmem->interface     = &lbl_8029B828;
	sjmem->buffer        = buffer;
	sjmem->bufferSize    = size;
	sjmem->uuid          = &lbl_8023FF50;
	sjmem->errorCallback = fn_80220BC8;
	sjmem->errorObject   = sjmem;
	fn_8022099C(sjmem);
	return sjmem;
}

void fn_80220B2C(void)
{
	lbl_80422C18--;
	if (lbl_80422C18 == 0) {
		memset(lbl_80422C1C, 0, sizeof(lbl_80422C1C));
	}
}

void fn_80220B74(void)
{
	if (lbl_80422C18 == 0) {
		memset(lbl_80422C1C, 0, sizeof(lbl_80422C1C));
	}
	lbl_80422C18++;
}

void fn_80220BC8(void* object, s32 error)
{
	fn_80221888(lbl_8023FF60);
}
