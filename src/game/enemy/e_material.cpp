// Complete enemy/e_material.cpp. The destructor and End intentionally have
// distinct roles: End owns release of the material-pointer array.
#include "game/enemy/e_material.h"

struct OBJ_SearchMaterials {
	RpMaterial* (*callback)(RpMaterial*, void*);
	char* pTextureName;
	void* pData;
};
struct sMatTextureSearch {
	RpMaterial** pMaterial;
	s32 nbNum;
};
static RpMaterial* callbackMaterial(RpMaterial*, void*);
extern "C" {
RpMaterial* fn_8015498C(RpMaterial*, RwTexture*);
RpMaterial* fn_801498EC(RpMaterial*, RwTexture*);
RpMaterial* fn_801494A0(RpMaterial*, RwTexture*);
RpMaterial* fn_80149B8C(RpMaterial*, RwTexture*);
RwTexture* fn_801A4BBC(RwTexDictionary*, const char*);
void fn_8005E664(RpClump*, OBJ_SearchMaterials*);
}

void TEnemyMatTexture::PreDisp(s32 num)
{
	// Preserve the native strict-greater-than test; callers supply valid indices.
	if (num > mNum)
		return;
	RwTexture* pTexTmp = mpEnTexture[num].pTexture;
	eEnTexture flagTmp = mpEnTexture[num].flag;
	if (pTexTmp == NULL)
		return;
	for (s32 i = 0; i < mMaterialNum; i++) {
		if (mpMaterial[i] != NULL) {
			switch (flagTmp) {
				case EN_TEXTURE_MATFX_NULL:
					fn_8015498C(mpMaterial[i], pTexTmp);
					break;
				case EN_TEXTURE_MATFX_ENV:
					fn_801498EC(mpMaterial[i], pTexTmp);
					break;
				case EN_TEXTURE_MATFX_BUMP:
					fn_801494A0(mpMaterial[i], pTexTmp);
					break;
				case EN_TEXTURE_MATFX_DUAL:
					fn_80149B8C(mpMaterial[i], pTexTmp);
					break;
			}
		}
	}
}

void TEnemyMatTexture::End()
{
	if (mpMaterial != NULL) {
		delete[] mpMaterial;
		mpMaterial = NULL;
	}
}

void TEnemyMatTexture::Init(
    RwTexDictionary* pTexDict, RpClump* pClump, sEnTexture* pEnTexture, s32 num)
{
	Clear();
	mNum        = num;
	mpEnTexture = pEnTexture;
	for (s32 i = 0; i < mNum; i++) {
		char* string = pEnTexture[i].filename;
		if (string != NULL)
			pEnTexture[i].pTexture = fn_801A4BBC(pTexDict, string);
	}
	sMatTextureSearch MatTextureSearch;
	MatTextureSearch.pMaterial = NULL;
	MatTextureSearch.nbNum     = 0;
	OBJ_SearchMaterials OBJ_SM;
	OBJ_SM.callback = callbackMaterial;
	OBJ_SM.pData    = &MatTextureSearch;
	for (s32 i = 0; i < mNum; i++) {
		char* string = pEnTexture[i].filename;
		if (string != NULL) {
			OBJ_SM.pTextureName = string;
			fn_8005E664(pClump, &OBJ_SM);
		}
		if (MatTextureSearch.nbNum > 0)
			break;
	}
	if (MatTextureSearch.nbNum != 0) {
		mpMaterial                 = new RpMaterial*[MatTextureSearch.nbNum];
		MatTextureSearch.pMaterial = mpMaterial;
		MatTextureSearch.nbNum     = 0;
		OBJ_SM.callback            = callbackMaterial;
		OBJ_SM.pData               = &MatTextureSearch;
		for (s32 i = 0; i < mNum; i++) {
			char* string = pEnTexture[i].filename;
			if (string != NULL) {
				OBJ_SM.pTextureName = string;
				fn_8005E664(pClump, &OBJ_SM);
			}
			if (MatTextureSearch.nbNum > 0)
				break;
		}
		mMaterialNum = MatTextureSearch.nbNum;
	}
}

TEnemyMatTexture::~TEnemyMatTexture() { }
TEnemyMatTexture::TEnemyMatTexture()
{
	Clear();
}

static RpMaterial* callbackMaterial(RpMaterial* material, void* data)
{
	sMatTextureSearch* pMatTextureSearch = (sMatTextureSearch*)((OBJ_SearchMaterials*)data)->pData;
	if (pMatTextureSearch->pMaterial != NULL)
		pMatTextureSearch->pMaterial[pMatTextureSearch->nbNum] = material;
	pMatTextureSearch->nbNum++;
	return material;
}
