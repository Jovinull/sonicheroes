#include "types.h"

// TObjFan's DestroyClump and CloneClump (the PS2 build's names;
// fanDestroyClump and fanCloneClump here): DestroyClump takes the model out of
// the scene and releases it; CloneClump (DestroyClump first, inlined) makes
// the spinning fan's model, adds it to the scene and gives it the placement's
// lights.

typedef struct RpClump RpClump;

typedef struct FanFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} FanFrame;

typedef struct Fan {
	u8 unk00[0x28];  // 0x00
	FanFrame* frame; // 0x28, the set object's
	u8 unk2C[0xC8];  // 0x2C
	s32 spinning;    // 0xF4
	RpClump* model;  // 0xF8
} Fan;

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

extern "C" World* lbl_8042C1D0;
extern "C" RpClump* fanModel;

extern "C" void fn_8015BBF8(void* scene, RpClump* model);
extern "C" void fn_8015BB08(void* scene, RpClump* model);
extern "C" void fn_80150958(RpClump* model);
extern "C" RpClump* fn_80150588(RpClump* model);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 lights);

extern "C" void fanDestroyClump(Fan* object)
{
	if (object->model != NULL) {
		fn_8015BBF8(lbl_8042C1D0->scene, object->model);
		fn_80150958(object->model);
		object->model = NULL;
	}
}

extern "C" void fanCloneClump(Fan* object)
{
	fanDestroyClump(object);
	if (object->spinning != 0) {
		object->model = fn_80150588(fanModel);
		fn_8015BB08(lbl_8042C1D0->scene, object->model);
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    object->model, ((object->frame->flags & 0x1C0000) >> 18) + 4);
	}
}
