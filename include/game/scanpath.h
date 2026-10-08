#ifndef GAME_SCANPATH_H
#define GAME_SCANPATH_H
#include "game/pathctrl.h"
struct TObjectBase {
	u8 kind[4];
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct THeapCtrl {
	u8 data[12];

	THeapCtrl(u32 size, u32 alignment);
	void Free(void* object);
	void* Malloc(u32 size);
	static void* operator new(unsigned long size);
	static void operator delete(void* object);
};

extern "C" THeapCtrl* lbl_8042C148;

struct TObject : public TObjectBase {
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
	u16 field1C;
	u16 field1E;
	u16 field20;
	u16 pad22;
	u16 field24;
	u16 pad26;

	int CheckAlive();
	int GetChildCount();
	void ImmAftSetRasterChild();
	void TDispChild();
	void PDispChild();
	void DispChild();
	void ExecChild();
	void DeleteChild();
	void KillChild();
	void Kill();
	static void operator delete(void* object);
	static void* operator new(unsigned long size);
};

struct PATHTBL_R {
	RwV3d n;
	f32 length;
	RwV3d pos;
};
struct PATHTBL_C {
	RwV3d pos;
};
struct PATHINFO {
	s32 slangx, slangz, slangax, slangaz;
	f32 onpathpos;
	RwV3d pos, normal, normala, front;
};
struct PATHPOINTCHECK {
	f32 S_length, length, min_dist, onpos_Refer, range_Search;
	RwV3d *p0, *p1, *pt;
	f32* min_onpos;
	RwV3d* onpnt3;
};
enum PATH_ROT_STATUS { PATH_ROT_YXZ = 0, PATH_ROT_ZXY = 1 };
class TObjPathManage : public TObject
{
public:
	PATHTAG** tagTblTopPtr;
	CLASS_PATH* pPath;
	NJS_LINE l_pl_Temp[8];
	RwV3d pos_pl_Last[8], diff_pl_Temp[8], dir_pl_Temp[8];
	f32 dist_pl_Temp[8];
	TObjPathManage(PATHTAG**);
	virtual ~TObjPathManage();
	virtual void Exec();
	virtual void Disp();
	void SetPath(PATHTAG**);
	void ReleasePath(CLASS_PATH*);
	static void reEntryLen(f32*, RwV3d*, RwV3d*);
	static void reEntryVec(RwV3d*, sAngle*, PATH_ROT_STATUS);
	static void reEntryAng(s16*, s16*, sAngle*, PATH_ROT_STATUS);
	static void reEntryPos(RwV3d*, RwV3d*, sAngle*, RwV3d*, PATH_ROT_STATUS);
	CLASS_PATH* EntryPath(PATHTAG*, RwV3d*, sAngle*, RwV3d*, PATH_ROT_STATUS);
	PATHTAG* scanpathGetTheConnectedPath(PATHTAG*, RwV3d*, f32*);
};
PATHTAG** MargePathTag(PATHTAG**, PATHTAG**);
f32 SCPathPntNearToOnpos(PATHTAG*, RwV3d*, RwV3d*, f32*, f32);
s32 SCPathOnposToPntnmb(PATHTAG*, f32, u32*);
s32 GetStatusOnPath(PATHTAG*, PATHINFO*);
void GetPointDataOnPath(PATHTAG*, s32, RwV3d*);
PATHTAG* scanpathGetTheNearestPath(RwV3d*, RwV3d*, f32);
s32 InitPath(PATHTAG**);
s32 EndPath();
#endif
