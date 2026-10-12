#include "game/object.h"

// The target's constructor (targetCtor here), called by the factory in
// rel/target_assets.cpp.
//
// It takes the placement's position, angle and kind, and its first state: 8 for
// a target already hit (condition bit 0x10000, and nothing more is set up),
// otherwise from the placement's mode (1 and 2 give states 0 and 1) or, failing
// that, from the kind (0 and 1 give 4, 2 and 3 give 6). It then makes the
// target's clump and turns it by its angle, the Y turn adding the extra angle
// at 0xE0 (in degrees), gives its collision block its shape and keeps a word in
// the placement's work block, making the block when there is none.

typedef struct RpAtomic RpAtomic;

typedef struct TargetAngle {
	s32 x, y, z;
} TargetAngle;

typedef struct TargetParams {
	s8 kind; // 0x00
	s8 mode; // 0x01
} TargetParams;

typedef struct TargetWork {
	u8 unk00[0x10]; // 0x00
	s32 unk10;      // 0x10
} TargetWork;       // 0x14

typedef struct TargetFrame {
	RwV3d pos;            // 0x00
	TargetAngle ang;      // 0x0C
	u32 condition;        // 0x18
	u8 unk1C[0x10];       // 0x1C
	TargetParams* params; // 0x2C
	TargetWork* work;     // 0x30
} TargetFrame;

typedef struct TargetTask {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} TargetTask;              // 0x28

typedef struct TargetMotion {
	TargetFrame* frame; // 0x00
	void** vtable;      // 0x04
} TargetMotion;         // 0x08

typedef struct Target {
	TargetTask base;     // 0x00
	TargetMotion motion; // 0x28
	u8 colli[0x88];      // 0x30
	s32 state;           // 0xB8
	s8 kind;             // 0xBC
	s8 unkBD;            // 0xBD
	s16 unkBE;           // 0xBE
	s32 unkC0;           // 0xC0
	s32 unkC4;           // 0xC4
	RwV3d pos;           // 0xC8
	TargetAngle ang;     // 0xD4
	f32 extraAngle;      // 0xE0
	f32 unkE4;           // 0xE4
	f32 unkE8;           // 0xE8
	RpClump* clump;      // 0xEC
} Target;                // 0xF0

extern "C" void* targetVtable[];
extern "C" const char* targetClassName;
extern "C" RpClump* targetResource;
extern "C" u8 targetCclInfo[];
extern "C" const f32 targetZero[1];
extern "C" const f32 targetOne[1];
extern "C" const f32 targetAngleScale[1];
extern "C" RwV3d AxisX;
extern "C" RwV3d AxisY;
extern "C" RwV3d AxisZ;

extern "C" void __ct__7TObjectFP7TObject(TargetTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(TargetMotion* motion);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, void* info, s32 count, u8 kind);
extern "C" void* __nw__FUl(u32 size);
extern "C" RpClump* fn_80150588(RpClump* model);
extern "C" void fn_80150958(RpClump* clump);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(RwMatrix* matrix, RwV3d* axis, f32 cosine, f32 sine, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" Target* targetCtor(Target* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	__ct__7C_COLLIFv(object->colli);
	object->base.vtable     = targetVtable;
	object->motion.vtable   = targetVtable + 0xB;
	TargetParams* params    = object->motion.frame->params;
	object->base.className  = targetClassName;
	object->base.objectSize = 0xF0;
	TargetParams* kind      = object->motion.frame->params;
	object->pos             = object->motion.frame->pos;
	object->ang             = object->motion.frame->ang;
	object->kind            = kind->kind;
	object->unkBE           = 0;
	object->unkBD           = -1;
	object->unkC0           = 0;
	object->extraAngle = object->unkE4 = targetZero[0];
	object->clump                      = NULL;
	object->unkE8                      = targetOne[0];

	if (object->motion.frame->condition & 0x10000) {
		object->state = 8;
		return object;
	}
	if (params->mode == 1) {
		object->state = 0;
	} else if (params->mode == 2) {
		object->state = 1;
	} else {
		switch (object->kind) {
			case 2:
			case 3:
				object->state = 6;
				break;
			case 0:
			case 1:
				object->state = 4;
				break;
		}
	}

	if (object->clump != NULL) {
		fn_80150958(object->clump);
		object->clump = NULL;
	}
	object->clump = fn_80150588(targetResource);
	if (object->clump != NULL) {
		RwFrame* frame = (RwFrame*)((RwObject*)object->clump)->parent;
		s32 extra      = (s32)(targetAngleScale[0] * object->extraAngle);
		s32 angle      = extra + object->ang.y;
		fn_80195790(
		    &frame->modelling, &AxisY, targetOne[0] - fn_800D7AE4(angle), fn_800D7B00(angle), 0);
		fn_80195790(&frame->modelling, &AxisX, targetOne[0] - fn_800D7AE4(object->ang.x),
		    fn_800D7B00(object->ang.x), 2);
		fn_80195790(&frame->modelling, &AxisZ, targetOne[0] - fn_800D7AE4(object->ang.z),
		    fn_800D7B00(object->ang.z), 2);
		fn_8019EB94(frame, &object->pos, 2);
	}

	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, targetCclInfo, 1, 4);
	if (object->motion.frame->work != NULL) {
		object->unkC4 = object->motion.frame->work->unk10;
	} else {
		TargetWork* work           = (TargetWork*)__nw__FUl(0x14);
		object->motion.frame->work = work;
		object->unkC4              = 0;
		work->unk10                = 0;
	}
	return object;
}
