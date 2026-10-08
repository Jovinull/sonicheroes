#ifndef GAME_EFFECT_EFF_BOMB_H
#define GAME_EFFECT_EFF_BOMB_H
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
	void ClearInfo();
	void Init(CCL_INFO*, int, u8);
	void CalcRange();
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
enum EffBombMode { INIT_EffBombMode = 0, BOMB_EffBombMode = 1, END_EffBombMode = 2 };
enum ENUM_EFF_BOMB_TYPE {
	ENUM_EFF_BOMB_TYPE_SBOMB           = 0,
	ENUM_EFF_BOMB_TYPE_LBOMB           = 1,
	ENUM_EFF_BOMB_TYPE_ONLY_DISP_SBOMB = 2,
	ENUM_EFF_BOMB_TYPE_ONLY_DISP_LBOMB = 3,
	// The GC constructor handles this additional value; its original name is unknown.
	ENUM_EFF_BOMB_TYPE_GC4 = 4
};
class TObjEffBomb : public TObject, public C_COLLI
{
public:
	virtual void TDisp();
	virtual void Exec();
	void SetPosition();
	virtual ~TObjEffBomb();
	void SetCollisionParameter();
	TObjEffBomb(TObject*, s32, RwV3d*, sAngle*, ENUM_EFF_BOMB_TYPE);
	EffBombMode mode;
	s8 teamNo, flagTimeStop;
	s16 timer;
	ENUM_EFF_BOMB_TYPE type;
	RwV3d pos;
	sAngle ang;
	f32 rotation;
	f32 scale[3], alpha[3];
	void* pClumpInstance;
	RpAtomic* pAtomicInstance[3];
};
CHARACTER_ID GetCCLCharacterIdFromTeamNoOfBomb(s32);
void EndEffBomb();
void InitEffBomb();
void SetEffectBomb(TObject*, RwV3d*, sAngle*, ENUM_EFF_BOMB_TYPE, s32);
#endif
