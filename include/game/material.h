#ifndef GAME_MATERIAL_H
#define GAME_MATERIAL_H
#include "game/plugin/materialcolorchange.h"
struct RpClump;
struct RwTexture;
class DealMaterial
{
public:
	RpClump* clump;
	RpAtomic* atomic;
	s32 num_materials;
	RwRGBA* colors;
	RwTexture** texture_ptrs;
	void EnableMatFX();
	void DisableMatFX();
	void DefaultColor();
	void MulColor(f32* color);
	void SetColor(RwRGBA* color);
	void DefaultTexture();
	void NoTexture();
	~DealMaterial();
	DealMaterial(RpAtomic* atomic);
	DealMaterial(RpClump* clump);
};
#endif
