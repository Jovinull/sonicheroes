// Complete materialcolorchange.c unit. PS2 symbolic metadata records C++
// compilation, C linkage for its public API, and C++ local stream callbacks.
#include "game/plugin/materialcolorchange.h"

struct MCCLocal {
	RwRGBA color;
	RpMaterial* pMaterial;
	s32 active;
	s32 userData[3];
	OBJ_CUSTOMRENDER cr;
};
static s32 LocalOffset = -1;
#define MCC(object) ((MCCLocal*)((u8*)(object) + LocalOffset))

static s32 MCCDataGetStreamSize(const void*, s32, s32);
static RwStream* MCCDataWriteStream(RwStream*, s32, const void*, s32, s32);
static RwStream* MCCDataReadStream(RwStream*, s32, void*, s32, s32);
static void* MCCDataCopier(void*, const void*, s32, s32);
static void* MCCDataDestructor(void*, s32, s32);
static void* MCCDataConstructor(void*, s32, s32);
extern "C" {
s32 fn_801520D0(s32, u32, void* (*)(void*, s32, s32), void* (*)(void*, s32, s32),
    void* (*)(void*, const void*, s32, s32));
s32 fn_80152150(u32, RwStream* (*)(RwStream*, s32, void*, s32, s32),
    RwStream* (*)(RwStream*, s32, const void*, s32, s32), s32 (*)(const void*, s32, s32));
void* fn_80193174(void*, u32);
void* fn_80193270(void*, u32);
u32 fn_801979AC(RwStream*, void*, u32);
RwStream* fn_80197B48(RwStream*, const void*, u32);
}

OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* pAtomic)
{
	if (LocalOffset > 0)
		return &MCC(pAtomic)->cr;
	return NULL;
}
s32 RpAtomicMCCSetCustomRenderCallBack(RpAtomic* pAtomic, OBJ_CUSTOMRENDER* pOBJ)
{
	if (LocalOffset > 0) {
		MCC(pAtomic)->cr = *pOBJ;
		return TRUE;
	}
	return FALSE;
}
s32* RpAtomicMCCGetUsrData(RpAtomic* pAtomic)
{
	if (LocalOffset > 0)
		return MCC(pAtomic)->userData;
	return NULL;
}
s32 RpAtomicMCCSetUsrData(RpAtomic* pAtomic, s32* pUserData, s32 size)
{
	if (LocalOffset > 0) {
		s32 _tmp;
		s32 _maxEle = size / 4;
		for (_tmp = 0; _tmp < _maxEle; ++_tmp)
			MCC(pAtomic)->userData[_tmp] = pUserData[_tmp];
		return TRUE;
	}
	return FALSE;
}
s32 RpAtomicMCCSetActive(RpAtomic* pAtomic, s32 active)
{
	if (LocalOffset > 0) {
		MCC(pAtomic)->active = active;
		return TRUE;
	}
	return FALSE;
}
s32 RpAtomicMCCSetMaterialPointer(RpAtomic* pAtomic, RpMaterial* pMaterial)
{
	if (LocalOffset > 0) {
		MCC(pAtomic)->pMaterial = pMaterial;
		return TRUE;
	}
	return FALSE;
}
s32 RpAtomicMCCSetColor(RpAtomic* pAtomic, RwRGBA* pColor)
{
	if (LocalOffset > 0) {
		MCC(pAtomic)->color = *pColor;
		return TRUE;
	}
	return FALSE;
}
RpMaterial* RpAtomicMCCGetMaterialPointer(RpAtomic* pAtomic)
{
	return LocalOffset > 0 ? MCC(pAtomic)->pMaterial : NULL;
}
RwRGBA* RpAtomicMCCGetColor(RpAtomic* pAtomic)
{
	return LocalOffset > 0 ? &MCC(pAtomic)->color : NULL;
}
s32 RpAtomicMCCPluginAttach()
{
	LocalOffset = fn_801520D0(
	    sizeof(MCCLocal), 0x1ff, MCCDataConstructor, MCCDataDestructor, MCCDataCopier);
	if (LocalOffset < 0)
		return FALSE;
	s32 offset = fn_80152150(0x1ff, MCCDataReadStream, MCCDataWriteStream, MCCDataGetStreamSize);
	return offset == LocalOffset;
}
static s32 MCCDataGetStreamSize(const void*, s32, s32)
{
	return sizeof(MCCLocal);
}
static RwStream* MCCDataWriteStream(RwStream* stream, s32, const void* pAtomic, s32, s32)
{
	MCCLocal binaryData;
	binaryData.color     = MCC(pAtomic)->color;
	binaryData.pMaterial = MCC(pAtomic)->pMaterial;
	binaryData.active    = MCC(pAtomic)->active;
	for (s32 _tmp = 0; _tmp < 3; ++_tmp)
		binaryData.userData[_tmp] = MCC(pAtomic)->userData[_tmp];
	fn_80193174(&binaryData, sizeof(binaryData));
	if (fn_80197B48(stream, &binaryData, sizeof(binaryData)))
		return stream;
	return NULL;
}
static RwStream* MCCDataReadStream(RwStream* stream, s32, void* pAtomic, s32, s32)
{
	MCCLocal binaryData;
	if (fn_801979AC(stream, &binaryData, sizeof(binaryData)) != sizeof(binaryData))
		return NULL;
	fn_80193270(&binaryData, sizeof(binaryData));
	RpAtomicMCCSetColor((RpAtomic*)pAtomic, &binaryData.color);
	RpAtomicMCCSetMaterialPointer((RpAtomic*)pAtomic, binaryData.pMaterial);
	RpAtomicMCCSetActive((RpAtomic*)pAtomic, binaryData.active);
	return stream;
}
static void* MCCDataCopier(void* dstAtomic, const void* srcAtomic, s32, s32)
{
	MCC(dstAtomic)->color     = MCC(srcAtomic)->color;
	MCC(dstAtomic)->pMaterial = MCC(srcAtomic)->pMaterial;
	MCC(dstAtomic)->active    = MCC(srcAtomic)->active;
	for (s32 _tmp = 0; _tmp < 3; ++_tmp)
		MCC(dstAtomic)->userData[_tmp] = MCC(srcAtomic)->userData[_tmp];
	return dstAtomic;
}
static void* MCCDataDestructor(void* pAtomic, s32, s32)
{
	return pAtomic;
}
static void* MCCDataConstructor(void* pAtomic, s32, s32)
{
	if (LocalOffset > 0) {
		RwRGBA def_color        = { 0, 0, 0, 0 };
		MCC(pAtomic)->color     = def_color;
		MCC(pAtomic)->pMaterial = NULL;
		MCC(pAtomic)->active    = FALSE;
		for (s32 _tmp = 0; _tmp < 3; ++_tmp)
			MCC(pAtomic)->userData[_tmp] = 0;
	}
	return pAtomic;
}
