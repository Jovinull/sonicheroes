#include "types.h"

// TObjWeightExtSub's constructor (the PS2 build's TObjWeightExtSub::__ct;
// weightExtCtor here): the piece beside the breakable weight, a child of the
// weight it belongs to, with a collision of one shape and vitality 10 whose
// size and centre height follow the weight's scale.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct WeightExtInfo {
	u8 unk00[0x8]; // 0x00
	RwV3d center;  // 0x08
	f32 a;         // 0x14
	f32 b;         // 0x18
	f32 c;         // 0x1C
} WeightExtInfo;

typedef struct WeightExtOwner {
	u8 unk000[0x124]; // 0x000
	RwV3d scale;      // 0x124
} WeightExtOwner;

typedef struct WeightExt {
	u8 unk00[0x18];        // 0x00
	void** vtable;         // 0x18
	u8 unk1C[0xC];         // 0x1C
	u8 colli[0x6];         // 0x28 (C_COLLI)
	s16 vitality;          // 0x2E
	u8 unk30[0x8];         // 0x30
	WeightExtInfo* info;   // 0x38
	u8 unk3C[0x74];        // 0x3C
	WeightExtOwner* owner; // 0xB0
} WeightExt;

extern "C" void* weightExtVtable[];
extern "C" WeightExtInfo weightExtCclInfo[];

extern "C" void __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, WeightExtInfo* info, s32 count, u8 kind);
extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" WeightExt* weightExtCtor(WeightExt* object, WeightExtOwner* owner)
{
	__ct__7TObjectFP7TObject(object, owner);
	__ct__7C_COLLIFv(object->colli);
	object->vtable = weightExtVtable;
	object->owner  = owner;
	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, weightExtCclInfo, 1, 4);
	object->vitality       = 10;
	object->info->a        = object->owner->scale.x * weightExtCclInfo[0].a;
	object->info->b        = object->owner->scale.y * weightExtCclInfo[0].b;
	object->info->c        = object->owner->scale.z * weightExtCclInfo[0].c;
	object->info->center.y = object->owner->scale.y * weightExtCclInfo[0].center.y;
	CalcRange__7C_COLLIFv(object->colli);
	return object;
}
