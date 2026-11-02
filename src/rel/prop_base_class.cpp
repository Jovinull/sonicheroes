#include "types.h"

// The common stage object base's Exec (empty), destructor and constructor
// (propBase here; the class has no PS2 name), the same in the six stage
// modules that carry it. The constructor clears the place, angles, flags and
// hit timers, sets a 20-frame hit time, 100 life, a 100-frame timer and flags
// 0x100 and 0x200, and no score, owner or sounds.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct C_COLLI {
	u8 unk00[0x6];
	s16 timer; // 0x06
	u8 unk08[0x80];
} C_COLLI; // 0x88

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject; // 0x28

typedef struct PropBase {
	TObject base;  // 0x000
	C_COLLI colli; // 0x028
	u32 flags;     // 0x0B0
	RwV3d pos;     // 0x0B4
	sAngle ang;    // 0x0C0
	s16 hitTime;   // 0x0CC
	s16 timers[8]; // 0x0CE
	u8 pad0DE[0x2];
	s32 score;     // 0x0E0
	s32 owner;     // 0x0E4
	s16 sounds[4]; // 0x0E8
	u8 unk0F0[0x4];
	f32 life; // 0x0F4
} PropBase;

extern "C" void* propBaseVtable[];
extern "C" const f32 propBaseZero;
extern "C" const f32 propBaseLife;
extern "C" void* lbl_8042C148;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7C_COLLIFv(C_COLLI* colli);
extern "C" void __dt__7C_COLLIFv(C_COLLI* colli, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" void propBaseExec(PropBase* object) { }

extern "C" PropBase* propBaseDtor(PropBase* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = propBaseVtable;
		__dt__7C_COLLIFv(&object->colli, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}

extern "C" PropBase* propBaseCtor(PropBase* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(&object->base, parent);
	__ct__7C_COLLIFv(&object->colli);
	object->base.vtable = propBaseVtable;
	object->flags       = 0;
	object->pos.x = object->pos.y = object->pos.z = propBaseZero;
	object->ang.x = object->ang.y = object->ang.z = 0;
	object->flags                                 = 0;
	object->timers[0]                             = 0;
	object->timers[1]                             = 0;
	object->timers[2]                             = 0;
	object->timers[3]                             = 0;
	object->timers[4]                             = 0;
	object->timers[5]                             = 0;
	object->timers[6]                             = 0;
	object->timers[7]                             = 0;
	object->hitTime                               = 0x14;
	object->life                                  = propBaseLife;
	object->colli.timer                           = 0x64;
	object->flags |= 0x100;
	object->flags |= 0x200;
	object->score     = 0;
	object->owner     = -1;
	object->sounds[0] = object->sounds[1] = object->sounds[2] = object->sounds[3] = 0;
	return object;
}
