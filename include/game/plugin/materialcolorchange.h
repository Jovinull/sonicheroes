#ifndef GAME_PLUGIN_MATERIALCOLORCHANGE_H
#define GAME_PLUGIN_MATERIALCOLORCHANGE_H
#include "types.h"
struct RpAtomic;
struct RpMaterial;
struct RwStream;
struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct OBJ_CUSTOMRENDER {
	void* pData;
	RpAtomic* (*callback)(RpAtomic*);
};
extern "C" {
OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* pAtomic);
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* pAtomic, OBJ_CUSTOMRENDER* pOBJ);
s32* RpAtomicMCCGetUsrData(RpAtomic* pAtomic);
s32 RpAtomicMCCSetUsrData(RpAtomic* pAtomic, s32* pUserData, s32 size);
s32 RpAtomicMCCSetActive(RpAtomic* pAtomic, s32 active);
s32 RpAtomicMCCSetMaterialPointer(RpAtomic* pAtomic, RpMaterial* pMaterial);
s32 RpAtomicMCCSetColor(RpAtomic* pAtomic, RwRGBA* pColor);
RpMaterial* RpAtomicMCCGetMaterialPointer(RpAtomic* pAtomic);
RwRGBA* RpAtomicMCCGetColor(RpAtomic* pAtomic);
s32 RpAtomicMCCPluginAttach();
}
#endif
