#include "game/object.h"

// The bird of paradise's constructor (gokurakuchoCtor here), called by the
// module's factory. It builds the object's bases and makes its two models: its
// own, added to one world slot, and the stage's, added to another, whose
// atomics the module walks (gokurakuchoAtomicCallback, still assembly) with the object's
// atomic slot. The first atomic of the stage's model takes the bounding sphere
// of the reference atomic (both brought up to date first, as
// RpAtomicGetBoundingSphere does), and the second model's frame is hung under
// the first's.
//
// It clears its motion state, keeps a turn rate from the placement's second
// parameter and its size from the third, scales the model by that size and
// turns it: by the bob angle (whose sine and cosine take the angle formula
// twice, as a macro would), half a turn about Y when the rate is negative, by
// its own turn and the placement's angles, then moves it to the placement. It
// keeps where the frame ends up (position and angles) and gives its atomic a
// block of pointers to its state, then defaults the size and the first
// parameter when they are left at zero.

typedef struct GokurakuchoParams {
	f32 range; // 0x00
	f32 rate;  // 0x04
	f32 size;  // 0x08
} GokurakuchoParams;

typedef struct GokurakuchoFrame {
	RwV3d pos;                 // 0x00
	s32 angX;                  // 0x0C
	s32 angY;                  // 0x10
	s32 angZ;                  // 0x14
	u8 unk18[0x14];            // 0x18
	GokurakuchoParams* params; // 0x2C
} GokurakuchoFrame;

typedef struct GokurakuchoTask {
	const char* className; // 0x00
	u8 unk04[0x14];        // 0x04
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} GokurakuchoTask;         // 0x28

typedef struct GokurakuchoMotion {
	GokurakuchoFrame* frame; // 0x00
	void** vtable;           // 0x04
} GokurakuchoMotion;

typedef struct Gokurakucho {
	GokurakuchoTask base;     // 0x00
	GokurakuchoMotion motion; // 0x28
	RpClump* model;           // 0x30
	RpClump* stageModel;      // 0x34
	RpAtomic* atomic;         // 0x38
	void** state;             // 0x3C
	f32 unk40;                // 0x40
	s32 turn;                 // 0x44
	s32 rate;                 // 0x48
	u8 unk4C[0xC];            // 0x4C
	RwV3d offset;             // 0x58
	s32 unk64;                // 0x64
	s32 unk68;                // 0x68
	s32 unk6C;                // 0x6C
	s32 unk70;                // 0x70
	s32 unk74;                // 0x74
	s32 bob;                  // 0x78
	RwV3d where;              // 0x7C
	s32 angX;                 // 0x88
	s32 angY;                 // 0x8C
	s32 angZ;                 // 0x90
	RwV3d scale;              // 0x94
} Gokurakucho;                // 0xA0

extern "C" u8* lbl_8042C1D0;
extern "C" void* gokurakuchoVtable[];
extern "C" const char* gokurakuchoClassName;
extern "C" void* gokurakuchoModelFile;
extern "C" RpAtomic* gokurakuchoReference;
extern "C" const RwV3d gokurakuchoUnitScale;
extern "C" const f32 gokurakuchoOne[1];
extern "C" const f32 gokurakuchoBobScale[1];
extern "C" const f32 gokurakuchoZero[1];
extern "C" const f32 gokurakuchoRateScale[1];
extern "C" const f32 gokurakuchoRangeDefault[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

extern "C" void __ct__7TObjectFP7TObject(GokurakuchoTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(GokurakuchoMotion* motion);
extern "C" void* __nw__FUl(u32 size);
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014F854(RpAtomic* atomic);
extern "C" void fn_8019E92C(void* parent, void* child);
extern "C" void fn_8019EC30(void* frame, RwV3d* scale, s32 combine);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" RwMatrix* fn_8019E8EC(void* frame);
extern "C" RpAtomic* gokurakuchoAtomicCallback(RpAtomic* atomic, void* data);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
extern "C" void GetRotYXZ__FP11RwMatrixTagPiPiPi(RwMatrix* matrix, s32* x, s32* y, s32* z);

#pragma opt_common_subs off
extern "C" Gokurakucho* gokurakuchoCtor(Gokurakucho* object, void* owner)
{
	RpAtomic* atomic;

	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	object->base.vtable       = gokurakuchoVtable;
	object->motion.vtable     = gokurakuchoVtable + 0xB;
	GokurakuchoParams* params = object->motion.frame->params;
	object->base.className    = gokurakuchoClassName;
	object->base.objectSize   = 0xA0;

	object->model = fn_80150588(gokurakuchoModelFile);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7260), object->model);
	object->stageModel = fn_80150588(*(void**)(lbl_8042C1D0 + 0xB08));
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), object->stageModel);

	atomic = objRpClumpGetAtomic(object->stageModel, NULL);
	fn_8014FFBC(object->stageModel, gokurakuchoAtomicCallback, &object->atomic);
	if (gokurakuchoReference->interpolator.flags & 2) {
		fn_8014F854(gokurakuchoReference);
	}
	RwSphere* source = &gokurakuchoReference->boundingSphere;
	if (atomic->interpolator.flags & 2) {
		fn_8014F854(atomic);
	}
	RwSphere* sphere = &atomic->boundingSphere;
	*sphere          = *source;
	fn_8019E92C(((RwObject*)object->model)->parent, ((RwObject*)object->stageModel)->parent);

	object->offset.x = object->offset.y = object->offset.z = gokurakuchoZero[0];
	object->unk64 = object->unk68 = object->unk6C = 0;
	object->unk70 = object->unk74 = object->bob = 0;
	object->turn                                = 0;
	object->rate                                = gokurakuchoRateScale[0] * params->rate;
	object->scale.x = object->scale.y = object->scale.z = params->size;

	GokurakuchoParams* sized = object->motion.frame->params;
	void* frame              = ((RwObject*)object->model)->parent;
	RwV3d scale              = gokurakuchoUnitScale;
	scale.x                  = sized->size;
	scale.y                  = sized->size;
	scale.z                  = sized->size;
	fn_8019EC30(frame, &scale, 0);

	f32 sin = fn_800D7B00(gokurakuchoBobScale[0] * (gokurakuchoOne[0] + fn_800D7B00(object->bob)));
	fn_80195790((u8*)frame + 0x10, &AxisZ,
	    gokurakuchoOne[0]
	        - fn_800D7AE4(gokurakuchoBobScale[0] * (gokurakuchoOne[0] + fn_800D7B00(object->bob))),
	    sin, 2);
	fn_8019E880(frame);
	if (object->rate < 0) {
		sin = fn_800D7B00(0x8000);
		fn_80195790((u8*)frame + 0x10, &AxisY, gokurakuchoOne[0] - fn_800D7AE4(0x8000), sin, 2);
		fn_8019E880(frame);
	}
	fn_8019EB94(frame, &object->offset, 2);
	sin = fn_800D7B00(object->turn);
	fn_80195790((u8*)frame + 0x10, &AxisY, gokurakuchoOne[0] - fn_800D7AE4(object->turn), sin, 2);
	fn_8019E880(frame);
	sin = fn_800D7B00(object->motion.frame->angY);
	fn_80195790((u8*)frame + 0x10, &AxisY,
	    gokurakuchoOne[0] - fn_800D7AE4(object->motion.frame->angY), sin, 2);
	fn_8019E880(frame);
	sin = fn_800D7B00(object->motion.frame->angX);
	fn_80195790((u8*)frame + 0x10, &AxisX,
	    gokurakuchoOne[0] - fn_800D7AE4(object->motion.frame->angX), sin, 2);
	fn_8019E880(frame);
	sin = fn_800D7B00(object->motion.frame->angZ);
	fn_80195790((u8*)frame + 0x10, &AxisZ,
	    gokurakuchoOne[0] - fn_800D7AE4(object->motion.frame->angZ), sin, 2);
	fn_8019E880(frame);
	fn_8019EB94(frame, &object->motion.frame->pos, 2);

	RwMatrix* matrix = fn_8019E8EC(frame);
	object->where.x  = matrix->pos.x;
	object->where.y  = matrix->pos.y;
	object->where.z  = matrix->pos.z;
	GetRotYXZ__FP11RwMatrixTagPiPiPi(matrix, &object->angX, &object->angY, &object->angZ);

	object->unk40 = gokurakuchoZero[0];
	object->state = (void**)__nw__FUl(0x10);
	if (object->state != NULL) {
		object->state[0] = &object->unk40;
		object->state[1] = &object->where;
		object->state[2] = &object->angX;
		object->state[3] = &object->scale;
		RpAtomicMCCSetUsrData(object->atomic, (s32*)&object->state, 4);
	}

	if (gokurakuchoZero[0] == params->size) {
		params->size = gokurakuchoOne[0];
	}
	if (gokurakuchoZero[0] == params->range) {
		params->range = gokurakuchoRangeDefault[0];
	}
	return object;
}
#pragma opt_common_subs reset
