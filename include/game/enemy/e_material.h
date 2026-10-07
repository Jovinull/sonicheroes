#ifndef GAME_ENEMY_E_MATERIAL_H
#define GAME_ENEMY_E_MATERIAL_H
#include "types.h"
struct RpMaterial;
struct RpClump;
struct RwTexture;
struct RwTexDictionary;
enum eEnTexture {
	EN_TEXTURE_MATFX_NULL    = 0,
	EN_TEXTURE_MATFX_ENV     = 1,
	EN_TEXTURE_MATFX_BUMP    = 2,
	EN_TEXTURE_MATFX_BUMPENV = 3,
	EN_TEXTURE_MATFX_DUAL    = 4
};
struct sEnTexture {
	char* filename;
	RwTexture* pTexture;
	eEnTexture flag;
};
class TEnemyMatTexture
{
public:
	TEnemyMatTexture();
	virtual ~TEnemyMatTexture();
	void PreDisp(s32);
	void End();
	void Init(RwTexDictionary*, RpClump*, sEnTexture*, s32);
	void Clear()
	{
		mpEnTexture  = NULL;
		mNum         = 0;
		mMaterialNum = 0;
		mpMaterial   = NULL;
	}
	RpMaterial** mpMaterial;
	sEnTexture* mpEnTexture;
	s32 mNum, mMaterialNum;
};
#endif
