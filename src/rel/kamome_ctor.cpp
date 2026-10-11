#include "types.h"

// The seagull flock's constructor (kamomeCtor here), called by the factory in
// rel/kamome_create.cpp. It builds the object's bases and takes the
// placement's parameters, giving the two speeds their defaults when they are
// left at zero. It makes a frame turned by the placement's angles (Y, then X
// and Z) and moved to its position, keeps the flock size (at least one) and
// makes that many 0x70-byte seagulls (kamomeBirdCtor, still assembly), each
// with its index and the two speeds.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct TObject {
	const char* className; // 0x00
	u8 unk04[0x14];        // 0x04
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} TObject;                 // 0x28

typedef struct KamomeParams {
	s8 count; // 0x00
	u8 pad01[3];
	f32 speedA; // 0x04
	f32 speedB; // 0x08
} KamomeParams;

typedef struct KamomeFrame {
	RwV3d pos;            // 0x00
	s32 angX;             // 0x0C
	s32 angY;             // 0x10
	s32 angZ;             // 0x14
	u8 unk18[0x14];       // 0x18
	KamomeParams* params; // 0x2C
} KamomeFrame;

typedef struct KamomeMotion {
	KamomeFrame* frame; // 0x00
	void** vtable;      // 0x04
} KamomeMotion;

typedef struct Kamome {
	TObject base;        // 0x00
	KamomeMotion motion; // 0x28
	s16 count;           // 0x30
	u8 pad32[0xA];       // 0x32
	void* frame;         // 0x3C
	s32 unk40;           // 0x40
} Kamome;                // 0x44

extern "C" void* lbl_8042C148;
extern "C" void* kamomeVtable[];
extern "C" const char* kamomeClassName;
extern "C" const f32 kamomeZero[1];
extern "C" const f32 kamomeSpeedADefault[1];
extern "C" const f32 kamomeSpeedBDefault[1];
extern "C" const f32 kamomeOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(KamomeMotion* motion);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* fn_8019E344(void);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void kamomeBirdCtor(void* bird, Kamome* flock, f32 speedB, f32 speedA, s16 index);

extern "C" Kamome* kamomeCtor(Kamome* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	object->base.vtable     = kamomeVtable;
	object->motion.vtable   = kamomeVtable + 0xB;
	KamomeParams* params    = object->motion.frame->params;
	object->base.className  = kamomeClassName;
	object->base.objectSize = 0x44;

	if (kamomeZero[0] == params->speedA) {
		params->speedA = kamomeSpeedADefault[0];
	}
	object->frame = fn_8019E344();
	if (kamomeZero[0] == params->speedB) {
		params->speedB = kamomeSpeedBDefault[0];
	}

	f32 sin = fn_800D7B00(object->motion.frame->angY);
	fn_80195790((u8*)object->frame + 0x10, &AxisY,
	    kamomeOne[0] - fn_800D7AE4(object->motion.frame->angY), sin, 0);
	fn_8019E880(object->frame);
	sin = fn_800D7B00(object->motion.frame->angX);
	fn_80195790((u8*)object->frame + 0x10, &AxisX,
	    kamomeOne[0] - fn_800D7AE4(object->motion.frame->angX), sin, 2);
	fn_8019E880(object->frame);
	sin = fn_800D7B00(object->motion.frame->angZ);
	fn_80195790((u8*)object->frame + 0x10, &AxisZ,
	    kamomeOne[0] - fn_800D7AE4(object->motion.frame->angZ), sin, 2);
	fn_8019E880(object->frame);
	fn_8019EB94(object->frame, &object->motion.frame->pos, 2);

	if (params->count == 0) {
		params->count = 1;
	}
	object->count = params->count;
	object->unk40 = 0;
	for (s16 i = 0; i < object->count; i++) {
		void* bird = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x70);
		if (bird != NULL) {
			kamomeBirdCtor(bird, object, params->speedB, params->speedA, i);
		}
	}
	return object;
}
