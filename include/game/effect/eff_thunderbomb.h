#ifndef GAME_EFFECT_EFF_THUNDERBOMB_H
#define GAME_EFFECT_EFF_THUNDERBOMB_H
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

struct RpClump;
class C_COLLI;
class CCL_REACTOR;
struct CCL_HIT_INFO {
	s8 my_num, hit_num;
	u16 flag;
	C_COLLI* hit_ccl;
};
struct CCL_INFO {
	u8 kind, form, push, damage;
	u32 attr;
	RwV3d center;
	f32 a, b, c;
	CCL_REACTOR* pReactor;
	s32 angx, angy, angz;
};
enum CHARACTER_ID {
	NO_CHARACTER_ID,
	PLAYER_0,
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	PLAYER_5,
	TEAM_0,
	TEAM_1,
	TEAM_2,
	TEAM_3,
	RING,
	STOP_LSD,
	SPECIAL_SHOCK_WAVE_0,
	SPECIAL_SHOCK_WAVE_1,
	DEFINED_NUMBER
};
class CCL_MASTER
{
};
class C_COLLI : public CCL_MASTER
{
public:
	C_COLLI();
	~C_COLLI();
	s32 Init(CCL_INFO*, s32, u8);
	s32 Entry();
	void SetRange(f32);
	void ClearInfo();
	u16 id;
	s16 nbHit, strength, vitality;
	u16 flag, nbInfo;
	f32 colli_range;
	CCL_INFO* info;
	CCL_HIT_INFO hit_info[8];
	RwV3d normal, pos;
	sAngle ang;
	CHARACTER_ID character_id;
	RwV3d pre_pos;
};
struct RpAtomic;
struct RwRGBA {
	u8 red, green, blue, alpha;
};

struct sRealAngle3 {
	f32 x, y, z;
};
class EffThunderBomb
{
public:
	EffThunderBomb();
	~EffThunderBomb();
	void RenderEffThunderBomb();
	void SetEffThunderBombMaterialColor(const RwRGBA*);
	RwRGBA rgba;
	void* pClumpInstance;
};
class TObjEffThunderSphere : public TObject, public EffThunderBomb
{
public:
	TObjEffThunderSphere(TObject*, s32);
	virtual ~TObjEffThunderSphere();
	virtual void TDisp();
	virtual void Exec();
	void UpdateFrame();
	s8 playerno, timer;
	u8 alpha;
	RwV3d pos;
	sRealAngle3 ang3;
	f32 scl;
};
class TObjEffThunderBomb : public TObjEffThunderSphere, public C_COLLI
{
public:
	TObjEffThunderBomb(TObject*, s32);
	virtual ~TObjEffThunderBomb();
	virtual void TDisp();
	virtual void Exec();
	void SetCharcterCollisionID(s32);
};
void SetEffectThunderBombForDRB(s32, RwV3d*);
TObjEffThunderBomb* SetEffectThunderBomb(s32);
void InitEffThunderBomb();
void EndEffThunderBomb();
#endif
