#include "types.h"

// The unload and load hooks rel/jump_panel_register.cpp puts in the jump
// panel's editor record. The load reads the panel's model (keeping the
// material of its arrow texture when there is a model) and its UV animation;
// when both the animation and the material are there, the animation heads the
// panel's custom FX block, which goes to the atomic that uses the arrow
// texture. The unload forgets the model (the stage resource manager owns it).

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

struct JumpPanelFX {
	RpClump* uv; // 0x00
	u8 pad04[0x40];
};

extern "C" char jumpPanelModelName[];
extern "C" char jumpPanelTexture[];
extern "C" char jumpPanelUVName[];
extern "C" RpClump* jumpPanelModel;
extern "C" RpMaterial* jumpPanelMaterial;
extern "C" RpClump* jumpPanelUV;
extern "C" JumpPanelFX jumpPanelFX;

RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* fx);

extern "C" void jumpPanelUnload(void)
{
	jumpPanelModel = NULL;
}

extern "C" void jumpPanelLoad(void)
{
	jumpPanelModel = objPointerReadFromClumpAnim(jumpPanelModelName);
	if (jumpPanelModel != NULL) {
		jumpPanelMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(jumpPanelModel, NULL, jumpPanelTexture);
	}
	jumpPanelUV = objPointerReadFromClumpAnim(jumpPanelUVName);
	if (jumpPanelUV != NULL && jumpPanelMaterial != NULL) {
		jumpPanelFX.uv = jumpPanelUV;
		AtomicSetCustomFXTexture(
		    objRpClumpGetAtomicWithTexture(jumpPanelModel, NULL, jumpPanelTexture), &jumpPanelFX);
	}
}
