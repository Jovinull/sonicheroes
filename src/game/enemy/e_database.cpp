// Complete C++ enemy/e_database.cpp; resource cleanup remains separate
// from destruction of the database record container.
#include "game/enemy/e_database.h"
struct RtAnimInterpolatorInfo {
	s32 typeID;
}; // accessed prefix only
struct RtAnimAnimation {
	RtAnimInterpolatorInfo* interpInfo;
	s32 numFrames, flags;
	f32 duration;
	void* pFrames;
	void* customData;
};
extern "C" {
extern u8 lbl_8029C310[];
s32 fn_800194A8(void*);                         // ACTION stage getter
void* fn_80012994(s32);                         // temporary allocation
void fn_800126C8(void*);                        // temporary release
RwTexDictionary* fn_801A4C84(RwTexDictionary*); // set current dictionary
RtAnimAnimation* fn_8022CF5C(RtAnimAnimation*); // animation compression
RtAnimAnimation* fn_8020C2D8(RtAnimAnimation*); // animation destroy
s32 fn_80150958(RpClump*);
s32 fn_8011B7CC(RpUVAnimAnimation*);
s32 fn_8014D8A4(RpSpline*);
void fn_80132750(NJS_MOTION*);
s32 fn_801A46D0(RwTexDictionary*);
s32 strcmp(const char*, const char*);
s32 strncmp(const char*, const char*, u32);
char* strchr(const char*, s32);
}
namespace nFileName
{
// Positive e_utility_filename.h metadata: signed-int CheckFileExt(PCc,PCc).
inline s32 CheckFileExt(const char* filename, const char* extension)
{
	char* p = strchr(filename, '.');
	if (p && strncmp(p, extension, 4) == 0)
		return 1;
	return 0;
}
}

TEnemyDataBase* TEnemyDataBase::mpDataBase;

s32 TEnemyDataBase::GetAnimationNum(eEnemyDataBase id)
{
	s32 num             = 0;
	sEnemyDataBase* pDB = &EnemyDataBase[id];
	sEnemyData* pData   = pDB->addr;
	for (s32 i = 0; i < pDB->filenum; i++) {
		if (pData[i].kind == DB_KIND_ANIMATION)
			num++;
	}
	return num;
}

s32 TEnemyDataBase::GetFileNum(eEnemyDataBase id)
{
	return EnemyDataBase[id].filenum;
}

NJS_MOTION* TEnemyDataBase::SearchCameraMotion(eEnemyDataBase id, u32 num)
{
	sEnemyData* pData = EnemyDataBase[id].addr;
	if (pData == NULL)
		return NULL;
	if (num < (u32)EnemyDataBase[id].filenum) {
		if (pData[num].kind == DB_KIND_CAMERAMOTION)
			return (NJS_MOTION*)pData[num].addr;
		return NULL;
	}
	return NULL;
}

RpUVAnimAnimation* TEnemyDataBase::SearchUVAnim(eEnemyDataBase id, u32 num)
{
	sEnemyData* pData = EnemyDataBase[id].addr;
	if (pData == NULL)
		return NULL;
	if (num < (u32)EnemyDataBase[id].filenum) {
		if (pData[num].kind == DB_KIND_UVANIMATION)
			return (RpUVAnimAnimation*)pData[num].addr;
		return NULL;
	}
	return NULL;
}

RtAnimAnimation* TEnemyDataBase::SearchHAnim(eEnemyDataBase id, u32 num)
{
	sEnemyData* pData = EnemyDataBase[id].addr;
	if (pData == NULL)
		return NULL;
	if (num < (u32)EnemyDataBase[id].filenum) {
		if (pData[num].kind == DB_KIND_ANIMATION)
			return (RtAnimAnimation*)pData[num].addr;
		return NULL;
	}
	return NULL;
}

RwTexDictionary* TEnemyDataBase::SearchTexDictonary(eEnemyDataBase id, u32 num)
{
	sEnemyData* pData = EnemyDataBase[id].addr;
	if (pData == NULL)
		return NULL;
	if (num < (u32)EnemyDataBase[id].filenum) {
		if (pData[num].kind == DB_KIND_TEX)
			return (RwTexDictionary*)pData[num].addr;
		return NULL;
	}
	return NULL;
}

RpClump* TEnemyDataBase::SearchClump(eEnemyDataBase id, u32 num)
{
	sEnemyData* pData = EnemyDataBase[id].addr;
	if (pData == NULL)
		return NULL;
	if (num < (u32)EnemyDataBase[id].filenum) {
		if (pData[num].kind == DB_KIND_CLUMP)
			return (RpClump*)pData[num].addr;
		return NULL;
	}
	return NULL;
}

s32 TEnemyDataBase::SetUpFiles(ONEFILE* pfp, eEnemyDataBase id)
{
	s32 num = 0;
	for (s32 i = 0; i < 256; ++i) {
		char* filename = pfp->CheckFileName(i);
		if (filename && strcmp(filename, "") != 0)
			++num;
	}
	if (num == 0)
		return 0;
	sEnemyDataBase* pDB = &EnemyDataBase[id];
	sEnemyData* pData   = new sEnemyData[num + 2];
	pDB->addr           = pData;
	pDB->filenum        = num + 2;
	s32 stageNo         = fn_800194A8(lbl_8029C310);
	s32 sizeBuffer_Temp;
	if (stageNo == 27 || stageNo == 28)
		sizeBuffer_Temp = 0x190000;
	else
		sizeBuffer_Temp = 0xaf000;
	void* tmpBuffer = fn_80012994(sizeBuffer_Temp);
	for (s32 i = 0; i < pDB->filenum; ++i) {
		char* filename = pfp->CheckFileName(i);
		if (!filename) {
			pData[i].kind = DB_KIND_UNKNOWN;
			pData[i].addr = 0;
		} else if (nFileName::CheckFileExt(filename, ".TXD")) {
			RwTexDictionary* tex = pfp->OneFileLoadTextureDictionay(i, tmpBuffer);
			if (tex) {
				fn_801A4C84(tex);
				pData[i].kind = DB_KIND_TEX;
				pData[i].addr = tex;
				break;
			}
			pData[i].kind = DB_KIND_UNKNOWN;
			pData[i].addr = 0;
		}
	}
	for (s32 i = 0; i < pDB->filenum; ++i) {
		char* filename = pfp->CheckFileName(i);
		if (!filename) {
			pData[i].kind = DB_KIND_UNKNOWN;
			pData[i].addr = 0;
		} else if (nFileName::CheckFileExt(filename, ".DFF")) {
			pData[i].kind = DB_KIND_CLUMP;
			pData[i].addr = pfp->OneFileLoadClump(i, tmpBuffer);
		} else if (nFileName::CheckFileExt(filename, ".ANM")) {
			pData[i].kind         = DB_KIND_ANIMATION;
			RtAnimAnimation* anim = pfp->OneFileLoadHAnimation(i, tmpBuffer);
			if (anim->interpInfo->typeID == 1) {
				RtAnimAnimation* compressed_anim = fn_8022CF5C(anim);
				fn_8020C2D8(anim);
				anim = compressed_anim;
			}
			pData[i].addr = anim;
		} else if (nFileName::CheckFileExt(filename, ".TXD")) {
			// Preserve entry produced by the earlier dictionary pass.
		} else if (nFileName::CheckFileExt(filename, ".UVB")) {
			pData[i].kind = DB_KIND_UVANIMATION;
			pData[i].addr = pfp->OneFileLoadUVAnim(i, tmpBuffer);
		} else if (nFileName::CheckFileExt(filename, ".SPL")) {
			pData[i].kind = DB_KIND_SPLINE;
			pData[i].addr = pfp->OneFileLoadSpline(i, tmpBuffer);
		} else if (nFileName::CheckFileExt(filename, ".TMB")) {
			pData[i].kind = DB_KIND_CAMERAMOTION;
			pData[i].addr = pfp->OneFileLoadCameraTmb(i, tmpBuffer);
		} else {
			pData[i].kind = DB_KIND_UNKNOWN;
			pData[i].addr = 0;
		}
	}
	fn_800126C8(tmpBuffer);
	return 1;
}

s32 TEnemyDataBase::Delete(eEnemyDataBase id)
{
	sEnemyDataBase* pDB = &EnemyDataBase[id];
	if (!pDB->filenum)
		return 0;
	sEnemyData* pData = pDB->addr;
	for (s32 i = pDB->filenum - 1; i >= 0; --i) {
		switch (pData[i].kind) {
			case DB_KIND_UNKNOWN:
				break;
			case DB_KIND_CLUMP:
				fn_80150958((RpClump*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
			case DB_KIND_ANIMATION:
				fn_8020C2D8((RtAnimAnimation*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
			case DB_KIND_UVANIMATION:
				fn_8011B7CC((RpUVAnimAnimation*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
			case DB_KIND_SPLINE:
				fn_8014D8A4((RpSpline*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
			case DB_KIND_CAMERAMOTION:
				fn_80132750((NJS_MOTION*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
		}
	}
	for (s32 i = pDB->filenum - 1; i >= 0; --i) {
		switch (pData[i].kind) {
			case DB_KIND_TEX:
				fn_801A46D0((RwTexDictionary*)pData[i].addr);
				pData[i].kind = DB_KIND_UNKNOWN;
				pData[i].addr = 0;
				break;
		}
	}
	delete[] pData;
	// Retail leaves pDB->addr and pDB->filenum unchanged.
	return 1;
}

s32 TEnemyDataBase::Add(eEnemyDataBase id, char* onefilename)
{
	s32 ret      = 0;
	ONEFILE* pfp = new ONEFILE(onefilename, 0);
	if (pfp)
		ret = SetUpFiles(pfp, id);
	delete pfp;
	return ret;
}

TEnemyDataBase::~TEnemyDataBase()
{
	for (s32 i = 0; i < ENEMY_DB_NUM; i++) {
		EnemyDataBase[i].addr    = NULL;
		EnemyDataBase[i].filenum = 0;
	}
}

TEnemyDataBase::TEnemyDataBase()
{
	for (s32 i = 0; i < ENEMY_DB_NUM; i++) {
		EnemyDataBase[i].addr    = NULL;
		EnemyDataBase[i].filenum = 0;
	}
	mpDataBase = this;
}
