// Draws a mesh display list with its effect data (HYPOTHESIS: the GameCube material-effect render
// callback): fetches the effect record (fn_80146BC8 with 6), saves the source and destination
// blend states, loads its textures (fn_801B1D0C) and runs the pre-render callback; with an effect
// material it sets the effect up (fn_801455B0), draws, and resets the manual texture coordinate
// scales, the indirect stages and the direct TEV stages the effect used; otherwise it just draws.
// Then the post-render callback runs and the blend states are restored. Names are inferred from
// this function only.
// NonMatching: instruction stream matches; in each loop retail gives the strength-reduced pointer
// and the counter the opposite saved registers (r26/r27, r25/r26), 22 words. Declaration
// permutations do not reproduce it.
extern "C" {
#include "dolphin/gx.h"
}
#include "types.h"

#define RW_STATE_SRC_BLEND  10
#define RW_STATE_DEST_BLEND 11

typedef void (*RenderCallBack80145CBC)(void* object, void* a, void* b, void* data);

struct CallBacks80145CBC {
	RenderCallBack80145CBC pre;  // 0x0
	RenderCallBack80145CBC post; // 0x4
	void* data;                  // 0x8
};

struct Effect80145CBC {
	u8 pad0[0x4];
	u32 numTextures;              // 0x4
	void* textures[8];            // 0x8
	u8 block28[0x8];              // 0x28
	void* material;               // 0x30
	CallBacks80145CBC* callbacks; // 0x34
};

struct TexCoordGen80145CBC {
	u32 flags; // 0x0: bit 2 uses a manual scale
	u8 pad4[0x18 - 0x4];
};

struct TevStage80145CBC {
	u8 pad0[0x60];
	void* indirect; // 0x60
};

struct MaterialState80145CBC {
	u8 pad0[0x9];
	u8 numTexGens;   // 0x9
	u8 numTevStages; // 0xA
	u8 padB;
	u8 numIndStages; // 0xC
	u8 padD[0x44 - 0xD];
	TexCoordGen80145CBC* texGens; // 0x44
	u8 pad48[0x50 - 0x48];
	TevStage80145CBC* tevStages; // 0x50
};

struct DisplayList80145CBC {
	void* list; // 0x0
	u32 size;   // 0x4
};

extern "C" {
Effect80145CBC* fn_80146BC8(void* object, s32 type);
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);
void fn_801B1D0C(void* texture, u32 slot);
void fn_801455B0(void* material, u32 numTextures, void* block, void* arg);
MaterialState80145CBC* fn_801439D8(void* material);

void fn_80145CBC(DisplayList80145CBC* displayList, void* object, void* a, void* b, void* arg)
{
	Effect80145CBC* effect;
	CallBacks80145CBC* callbacks;
	void* srcBlend;
	void* destBlend;
	u32 i;
	s32 stage;
	MaterialState80145CBC* state;

	effect    = fn_80146BC8(object, 6);
	callbacks = effect->callbacks;

	fn_80194294(RW_STATE_SRC_BLEND, &srcBlend);
	fn_80194294(RW_STATE_DEST_BLEND, &destBlend);
	for (i = 0; i < effect->numTextures; i++) {
		fn_801B1D0C(effect->textures[i], i);
	}
	if (callbacks->pre != 0) {
		callbacks->pre(object, a, b, callbacks->data);
	}
	if (effect->material != 0) {
		fn_801455B0(effect->material, effect->numTextures, effect->block28, arg);
		GXCallDisplayList(displayList->list, displayList->size);
		state = fn_801439D8(effect->material);
		for (stage = 0; stage < state->numTexGens; stage++) {
			if (state->texGens[stage].flags & 0x4) {
				GXSetTexCoordScaleManually((GXTexCoordID)stage, 0, 0, 0);
			}
		}
		if (state->numIndStages != 0) {
			GXSetNumIndStages(0);
			for (stage = 0; stage < state->numIndStages; stage++) {
				GXSetIndTexCoordScale((GXIndTexStageID)stage, GX_ITS_1, GX_ITS_1);
			}
			for (stage = 0; stage < state->numTevStages; stage++) {
				if (state->tevStages[stage].indirect != 0) {
					GXSetTevDirect((GXTevStageID)stage);
				}
			}
		}
	} else {
		GXCallDisplayList(displayList->list, displayList->size);
	}
	if (callbacks->post != 0) {
		callbacks->post(object, a, b, callbacks->data);
	}
	fn_80194234(RW_STATE_SRC_BLEND, srcBlend);
	fn_80194234(RW_STATE_DEST_BLEND, destBlend);
}
}
