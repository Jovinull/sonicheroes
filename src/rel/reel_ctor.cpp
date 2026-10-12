#include "game/object.h"

// The reel's constructor (reelCtor here), called by the factory in
// rel/reel_assets.cpp.
//
// It takes the placement's position, angle and parameters: the kind (0 hangs at
// height 0, 1 at the height parameter), the speed in degrees turned into the
// game's angle units, and a third value. Then it makes the reel's clump,
// registers it with the world, turns and moves its frame, stretches the rope
// frame to the height (a tenth of it, or 0.01 when the height is 0) and moves
// the reel frame under it down by the height, giving that frame the inverse
// stretch. Last come the collision, the light set and the custom render mode of
// the first atomic using one of the reel's textures.

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RpAtomic RpAtomic;

typedef struct ReelAngle {
	s32 x, y, z;
} ReelAngle;

typedef struct ReelParams {
	f32 height; // 0x00
	f32 speed;  // 0x04
	f32 unk08;  // 0x08
	s16 kind;   // 0x0C
} ReelParams;

typedef struct ReelFrame {
	RwV3d pos;          // 0x00
	ReelAngle ang;      // 0x0C
	u32 condition;      // 0x18
	u8 unk1C[0x10];     // 0x1C
	ReelParams* params; // 0x2C
} ReelFrame;

typedef struct ReelTask {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} ReelTask;                // 0x28

typedef struct ReelMotion {
	ReelFrame* frame; // 0x00
	void** vtable;    // 0x04
} ReelMotion;         // 0x08

typedef struct Reel {
	ReelTask base;     // 0x00
	ReelMotion motion; // 0x28
	u8 colli[0x88];    // 0x30
	s32 unkB8;         // 0xB8
	s8 kind;           // 0xBC
	s8 unkBD;          // 0xBD
	s16 unkBE;         // 0xBE
	f32 unkC0;         // 0xC0
	f32 height;        // 0xC4
	f32 heightParam;   // 0xC8
	f32 unkCC;         // 0xCC
	s32 speed;         // 0xD0
	f32 unkD4;         // 0xD4
	s8 unkD8;          // 0xD8
	u8 padD9[3];       // 0xD9
	RwV3d pos;         // 0xDC
	ReelAngle ang;     // 0xE8
	RpClump* clump;    // 0xF4
} Reel;                // 0xF8

extern "C" u8* lbl_8042C1D0;
extern "C" void* reelVtable[];
extern "C" const char* reelClassName;
extern "C" RpClump* reelClump;
extern "C" char* reelTextureNames[];
extern "C" u8 reelCclInfo[];
extern "C" const f32 reelZero[1];
extern "C" const f32 reelOne[1];
extern "C" const f32 reelAngleScale[1];
extern "C" const f32 reelHeightScale[1];
extern "C" const f32 reelMinHeight[1];
extern "C" RwV3d AxisY;

extern "C" void __ct__7TObjectFP7TObject(ReelTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(ReelMotion* motion);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, void* info, s32 count, u8 kind);
extern "C" RpClump* fn_80150588(RpClump* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(RwMatrix* matrix, RwV3d* axis, f32 cosine, f32 sine, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* child);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);

extern "C" Reel* reelCtor(Reel* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	__ct__7C_COLLIFv(object->colli);
	object->base.vtable     = reelVtable;
	object->motion.vtable   = reelVtable + 0xB;
	object->base.className  = reelClassName;
	object->base.objectSize = 0xF8;
	object->pos             = object->motion.frame->pos;
	object->ang             = object->motion.frame->ang;

	RwV3d down;
	RwV3d scale;
	ReelParams* params  = object->motion.frame->params;
	object->heightParam = params->height;
	object->kind        = params->kind;
	switch (object->kind) {
		case 0:
			object->unkC0 = reelZero[0];
			break;
		case 1:
			object->unkC0 = object->heightParam;
			break;
	}
	object->height = object->unkC0;
	object->speed  = reelAngleScale[0] * params->speed;
	object->unkD4  = params->unk08;
	object->unkBE  = 0;
	object->unkD8  = 0;
	object->unkBD  = -1;
	object->unkCC  = reelZero[0];
	object->unkB8  = 1;

	object->clump = fn_80150588(reelClump);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), object->clump);
	RwFrame* frame = (RwFrame*)((RwObject*)object->clump)->parent;
	fn_80195790(&frame->modelling, &AxisY, reelOne[0] - fn_800D7AE4(object->ang.y),
	    fn_800D7B00(object->ang.y), 0);
	fn_8019EB94(frame, &object->pos, 2);

	frame   = objRwFrameGetChildFrame(objRwFrameGetChildFrame(frame, NULL), NULL);
	scale.x = scale.z = reelOne[0];
	if (reelZero[0] != object->height) {
		scale.y = reelHeightScale[0] * object->height;
	} else {
		scale.y = reelMinHeight[0];
	}
	fn_8019EC30(frame, &scale, 0);

	frame  = objRwFrameGetChildFrame(frame, NULL);
	down.x = down.z = reelZero[0];
	down.y          = -object->height;
	fn_8019EB94(frame, &down, 0);
	scale.y = reelOne[0] / scale.y;
	fn_8019EC30(frame, &scale, 2);

	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, reelCclInfo, 1, 4);
	u32 flag = *(volatile u32*)&object->motion.frame->condition;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
	    object->clump, ((flag & 0x1C0000) >> 18) + 4);

	RpAtomic* atomic = NULL;
	for (s32 i = 0; atomic == NULL; i++) {
		atomic = objRpClumpGetAtomicWithTexture(object->clump, NULL, reelTextureNames[i]);
	}
	OBJ_CUSTOMRENDER* render = RpAtomicMCCGetCustomRenderCallBack(atomic);
	render->pData            = (void*)0x10;
	return object;
}
