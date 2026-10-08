#ifndef GAME_E_MTNPATH_H
#define GAME_E_MTNPATH_H
#include "types.h"
#include "game/pathctrl.h"

// Accessed GameCube contracts. No PS2-specific 16-byte alignment.
struct RwMatrixTag {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
typedef RwMatrixTag RwMatrix;
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RwLLLink {
	RwLLLink* next;
	RwLLLink* prev;
};
struct RwLinkList {
	RwLLLink link;
};
// Only the modelling prefix is accessed. Tail extent is intentionally opaque.
struct RwFrame {
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrix modelling;
};
struct RpClump {
	RwObject object;
	RwLinkList atomicList, lightList, cameraList;
	RwLLLink inWorldLink;
	RpClump* (*callback)(RpClump*, void*);
};
struct RpHAnimHierarchy;
struct RtAnimAnimation;
struct sBitFlag {
	u32 Flag;
};
class TObject;
struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};
struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;
class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	// Natural two-byte tail padding to 0x28; no named filler needed.
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p) { lbl_8042C148->Free(p); }
};
enum ENEMYMTNMD {
	ENEMYMTNMD_INIT      = 0,
	ENEMYMTNMD_SET       = 1,
	ENEMYMTNMD_CHANGE    = 2,
	ENEMYMTNMD_LOOP      = 3,
	ENEMYMTNMD_NEXT      = 4,
	ENEMYMTNMD_STOP      = 5,
	ENEMYMTNMD_TXEN      = 6,
	ENEMYMTNMD_POTS      = 7,
	ENEMYMTNMD_SPEED     = 8,
	ENEMYMTNMD_SPEEDNEXT = 9,
	ENEMYMTNMD_TURN      = 10,
	ENEMYMTNMD_MANUAL    = 11,
	ENEMYMTNMD_NEXT2     = 12,
	ENEMYMTNMD_LOOP2     = 13,
	ENEMYMTNMD_END       = 14
};
enum eEnemyDataBase {
	ENEMY_DB_COMMON     = 0,
	ENEMY_DB_ICON       = 1,
	ENEMY_DB_SEARCHER   = 2,
	ENEMY_DB_RINOLINER  = 3,
	ENEMY_DB_TURTLE     = 4,
	ENEMY_DB_FLYER      = 5,
	ENEMY_DB_PAWN       = 6,
	ENEMY_DB_CAPTURE    = 7,
	ENEMY_DB_WALL       = 8,
	ENEMY_DB_E2000      = 9,
	ENEMY_DB_MAGICIAN   = 10,
	ENEMY_DB_EGGMOBILE  = 11,
	ENEMY_DB_MTNPATH    = 12,
	ENEMY_DB_METALSONIC = 13,
	ENEMY_DB_NUM        = 14
};

struct ENEMY_MOTION {
	RtAnimAnimation* pHAA;
	ENEMYMTNMD mtnmode;
	s32 next;
	f32 start, end, frame, racio;
	char* pName;
	u32 uid;
};
class ENEMYMTNMAN
{
public:
	ENEMYMTNMAN();
	~ENEMYMTNMAN();
	void UpdateMotion();
	f32 nframe, pframe, start_frame, framespeed;
	sBitFlag mtnflag;
	s32 mtntimer, motion, reqmotion, lastmotion, nextmotion;
	ENEMYMTNMD mtnmode;
	ENEMY_MOTION* pEM;
	RpClump* pClump;
	RpHAnimHierarchy* pNHAH;
	RpHAnimHierarchy* pTHAH;
	RpHAnimHierarchy* pIHAH;
	s32 subFrameID;
	RpHAnimHierarchy* pPHAH;
	s32 reqmotion2;
};
class TEnemyMtnPathData
{
public:
	TEnemyMtnPathData(eEnemyDataBase);
	~TEnemyMtnPathData();
	s32 SetUpMotionTable(eEnemyDataBase);
	ENEMY_MOTION* GetMotionPtr() { return mpEnemyMotionTblPtr; }
	RpClump* GetModelPtr() { return mpClump; }
	s32 GetAnimNum() { return mAnimNum; }
	ENEMY_MOTION* mpEnemyMotionTblPtr;
	RpClump* mpClump;
	s32 mAnimNum;
};
class TEnemyMtnPath : public TObject, public ENEMYMTNMAN
{
public:
	TEnemyMtnPath(TObject*, TEnemyMtnPathData*);
	virtual ~TEnemyMtnPath();
	virtual void Exec();
	virtual void Disp();
	RwMatrix* GetMtnPathMatrix();
	void SetPath(s32);
	void ChangePath(s32);
	RpClump* mpClump;
	RwFrame* mpFrame;
	RwMatrix mMatrix;
	RwV3d* mpPathPos;
	s32 mPathPosIdx, mPathNo;
	f32 mPathRate;
	s32 mPathNum;
};
extern char* CL_TEnemyMtnPath;
#endif
