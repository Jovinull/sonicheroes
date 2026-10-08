// Complete enemy/e_mtnpath.cpp; GameCube layout and behavior are authoritative.
#include "game/enemy/e_mtnpath.h"

extern "C" {
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RwFrame* fn_8011B5A8(RwFrame*, s32);
}

char* CL_TEnemyMtnPath = "TEnemyMtnPath";

RwMatrixTag* TEnemyMtnPath::GetMtnPathMatrix()
{
	if (mpFrame != NULL)
		return &mpFrame->modelling;
	return NULL;
}

void TEnemyMtnPath::SetPath(s32 path)
{
	if (path < 0 || mPathNum <= path)
		return;
	mPathNo   = path;
	reqmotion = mPathNo;
	nframe    = 0.0f;
	UpdateMotion();
}

void TEnemyMtnPath::ChangePath(s32 path)
{
	if (mPathNo != path && path >= 0 && mPathNum > path) {
		mPathNo   = path;
		reqmotion = mPathNo;
		nframe    = 0.0f;
		UpdateMotion();
	}
}

void TEnemyMtnPath::Disp() { }
void TEnemyMtnPath::Exec()
{
	UpdateMotion();
}

TEnemyMtnPath::~TEnemyMtnPath()
{
	if (mpPathPos != NULL) {
		delete[] mpPathPos;
		mpPathPos = NULL;
	}
	mPathPosIdx = 0;
	mPathNo     = 0;
	mPathRate   = 0.0f;
	if (mpClump != NULL) {
		fn_80150958(mpClump);
		pClump  = NULL;
		mpClump = NULL;
	}
	mpFrame = NULL;
}

TEnemyMtnPath::TEnemyMtnPath(TObject* ptp, TEnemyMtnPathData* pathdata)
    : TObject(ptp)
{
	ClassName       = CL_TEnemyMtnPath;
	DispTime        = sizeof(TEnemyMtnPath);
	mpClump         = NULL;
	mpFrame         = NULL;
	mpPathPos       = NULL;
	mPathPosIdx     = 0;
	mPathNo         = 0;
	mPathRate       = 0.0f;
	mPathNum        = pathdata->GetAnimNum();
	mMatrix.right.x = mMatrix.up.y = mMatrix.at.z = 1.0f;
	mMatrix.right.y = mMatrix.right.z = mMatrix.up.x = 0.0f;
	mMatrix.up.z = mMatrix.at.x = mMatrix.at.y = 0.0f;
	mMatrix.pos.x = mMatrix.pos.y = mMatrix.pos.z = 0.0f;
	mMatrix.flags |= 0x20003;
	RpClump* pClump_Temp = pathdata->GetModelPtr();
	if (pClump_Temp != NULL) {
		mpClump         = fn_80150588(pClump_Temp);
		RwFrame* pFrame = (RwFrame*)mpClump->object.parent;
		if (pFrame != NULL)
			mpFrame = fn_8011B5A8(pFrame, 0x37);
	}
	ENEMY_MOTION* pMtnTblPtr = pathdata->GetMotionPtr();
	if (pMtnTblPtr != NULL && mpClump != NULL) {
		mPathNo   = 0;
		pClump    = mpClump;
		pEM       = pMtnTblPtr;
		reqmotion = mPathNo;
	}
}

// Metadata-backed external database view; append to common declarations.
struct sEnemyData;
struct sEnemyDataBase {
	sEnemyData* addr;
	s32 filenum;
};
class TEnemyDataBase
{
public:
	TEnemyDataBase();
	s32 GetFileNum(eEnemyDataBase);
	s32 GetAnimationNum(eEnemyDataBase);
	RtAnimAnimation* SearchHAnim(eEnemyDataBase, u32);
	RpClump* SearchClump(eEnemyDataBase, u32);
	static TEnemyDataBase* GetInstance()
	{
		if (!mpDataBase) {
			new TEnemyDataBase;
		}
		return mpDataBase;
	}
	sEnemyDataBase EnemyDataBase[ENEMY_DB_NUM];
	static TEnemyDataBase* mpDataBase;
};

s32 TEnemyMtnPathData::SetUpMotionTable(eEnemyDataBase database)
{
	TEnemyDataBase* pDB = TEnemyDataBase::GetInstance();
	s32 filenum         = pDB->GetFileNum(database);
	if (!filenum) {
		return 0;
	}
	mAnimNum = pDB->GetAnimationNum(database);
	if (!mAnimNum) {
		return 0;
	}
	mpEnemyMotionTblPtr = new ENEMY_MOTION[mAnimNum + 1];
	RtAnimAnimation* p_anim;
	s32 idx = 0;
	for (s32 i = 0; i < filenum; i++) {
		p_anim = pDB->SearchHAnim(database, i);
		if (p_anim) {
			mpEnemyMotionTblPtr[idx].pHAA    = p_anim;
			mpEnemyMotionTblPtr[idx].mtnmode = ENEMYMTNMD_SPEED;
			mpEnemyMotionTblPtr[idx].next    = 0;
			mpEnemyMotionTblPtr[idx].start   = 0.0f;
			mpEnemyMotionTblPtr[idx].end     = -1.0f;
			mpEnemyMotionTblPtr[idx].frame   = 1.0f;
			mpEnemyMotionTblPtr[idx].racio   = 1.0f;
			mpEnemyMotionTblPtr[idx].pName   = 0;
			mpEnemyMotionTblPtr[idx].uid     = 0;
			idx++;
		}
	}
	mpEnemyMotionTblPtr[idx].pHAA    = 0;
	mpEnemyMotionTblPtr[idx].mtnmode = ENEMYMTNMD_END;
	mpEnemyMotionTblPtr[idx].next    = 0;
	mpEnemyMotionTblPtr[idx].start   = 0.0f;
	mpEnemyMotionTblPtr[idx].end     = 0.0f;
	mpEnemyMotionTblPtr[idx].frame   = 0.0f;
	mpEnemyMotionTblPtr[idx].racio   = 0.0f;
	mpEnemyMotionTblPtr[idx].pName   = 0;
	mpEnemyMotionTblPtr[idx].uid     = 0;
	RpClump* pClump;
	for (s32 i = 0; i < filenum; i++) {
		pClump = pDB->SearchClump(database, i);
		if (pClump) {
			mpClump = pClump;
			break;
		}
	}
	return 1;
}

TEnemyMtnPathData::~TEnemyMtnPathData()
{
	mpClump  = 0;
	mAnimNum = 0;
	if (mpEnemyMotionTblPtr) {
		delete[] mpEnemyMotionTblPtr;
		mpEnemyMotionTblPtr = 0;
	}
}

TEnemyMtnPathData::TEnemyMtnPathData(eEnemyDataBase database)
{
	mpEnemyMotionTblPtr = 0;
	mpClump             = 0;
	mAnimNum            = 0;
	SetUpMotionTable(database);
}
