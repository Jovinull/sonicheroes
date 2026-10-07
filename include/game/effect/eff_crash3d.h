#ifndef GAME_EFFECT_EFF_CRASH3D_H
#define GAME_EFFECT_EFF_CRASH3D_H
#include "types.h"
#include "game/pathctrl.h"
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

struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct sRealAngle3 {
	f32 x, y, z;
};
struct RpClump;
struct RpAtomic;
struct RwFrame;
struct RpHAnimHierarchy;
enum EffCrash3DMode {
	INIT_EffCrash3DMode,
	CRASH_EffCrash3DMode,
	BLINX_EffCrash3DMode,
	END_EffCrash3DMode
};
enum ENUM_EFF_CRASH3D_TYPE {
	ENUM_EFF_CRASH3D_TYPE_SPHERE,
	ENUM_EFF_CRASH3D_TYPE_CUBE,
	MAX_ENUM_EFF_CRASH3D_TYPE
};
enum RwBlendFunction {
	rwBLENDNABLEND = 0,
	rwBLENDZERO,
	rwBLENDONE,
	rwBLENDSRCCOLOR,
	rwBLENDINVSRCCOLOR,
	rwBLENDSRCALPHA,
	rwBLENDINVSRCALPHA,
	rwBLENDDESTALPHA,
	rwBLENDINVDESTALPHA,
	rwBLENDDESTCOLOR,
	rwBLENDINVDESTCOLOR,
	rwBLENDSRCALPHASAT,
	rwBLENDFUNCTIONFORCEENUMSIZEINT = 0x7fffffff
};
struct Crash3DObjs {
	char* p_dff_name;
	s32 num_objs;
};
class TObjEffCrash3DRChildObj : public TObject
{
public:
	virtual void Exec();
	void SetPosition();
	virtual ~TObjEffCrash3DRChildObj();
	TObjEffCrash3DRChildObj(
	    TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, RwFrame*, RpAtomic*, f32, s32, s16);
	EffCrash3DMode mode;
	s16 timer, blink_time;
	s32 check_ground_flag;
	RwV3d pos, spd;
	sAngle ang;
	RwV3d scl;
	sRealAngle3 ang_spd;
	f32 alpha, y_ground_pos;
	RwFrame* p_frame;
	RpAtomic* p_atomic;
	s32 ignore_time_stop_flag;
};
class TObjEffCrash3DR : public TObject
{
public:
	RpAtomic* SearchAtomicFromFrame(RwFrame*);
	RwFrame* SearchNodeFrameFromNodeID(s32);
	virtual void TDisp();
	virtual void Disp();
	virtual void Exec();
	virtual ~TObjEffCrash3DR();
	TObjEffCrash3DR(TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, s16,
	    RwBlendFunction, RpClump*);
	RwV3d pos;
	sAngle ang;
	RwBlendFunction blend;
	RpHAnimHierarchy* hierarchy;
	RpClump* p_clump_instance;
};
class TObjEffCrash3DChildObj : public TObject
{
public:
	virtual void TDisp();
	virtual void Disp();
	virtual void Exec();
	void SetPosition();
	virtual ~TObjEffCrash3DChildObj();
	TObjEffCrash3DChildObj(
	    TObject*, RwV3d*, sAngle*, f32, RpClump*, ENUM_EFF_CRASH3D_TYPE, f32, f32, s16);
	EffCrash3DMode mode;
	s16 timer;
	RwV3d pos, spd;
	sAngle ang;
	sRealAngle3 ang_spd;
	f32 alpha, y_ground_pos;
	void* p_clump_instance;
	s32 ignore_time_stop_flag;
};
class TObjEffCrash3D : public TObject
{
public:
	virtual void Exec();
	virtual ~TObjEffCrash3D();
	TObjEffCrash3D(TObject*, RwV3d*, sAngle*, f32, ENUM_EFF_CRASH3D_TYPE, s16, f32, f32, RpClump**,
	    Crash3DObjs*, s16);
	RwV3d pos;
	sAngle ang;
};
void SetEffectCrash3D_R(
    TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, s16, RwBlendFunction, RpClump*);
void SetEffectCrash3D_R(TObject*, RwV3d*, sAngle*, RwV3d*, RwV3d*, f32, f32, s32, s16, RpClump*);
void SetEffectCrash3D_R(TObject*, RwV3d*, sAngle*, RwV3d*, f32, f32, RpClump*);
void SetEffectCrash3D(
    TObject*, RwV3d*, sAngle*, f32, ENUM_EFF_CRASH3D_TYPE, f32, f32, RpClump**, Crash3DObjs*, s16);
#endif
