#ifndef GAME_EFFECT_EFF_BRIM_H
#define GAME_EFFECT_EFF_BRIM_H
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
struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct sRealAngle3 {
	f32 x, y, z;
};
struct RwMatrix {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
struct RwIm3DVertex {
	RwV3d objVertex;
	RwV3d objNormal;
	RwRGBA color;
	f32 u, v;
};
struct EffBrim_Node {
	RwV3d pos;
	RwRGBA color;
};
class TObjEffBrimS : public TObject
{
public:
	virtual void TDisp();
	virtual void Exec();
	virtual void UpdateFrame();
	virtual void SetMaterialColor(const RwRGBA*);
	virtual ~TObjEffBrimS();
	TObjEffBrimS(TObject*, s32);
	virtual RwRGBA* GetMaterialColor();
	s8 playerno;
	RwRGBA rgba;
	f32 rotation, scaleH_Max, scaleH, scaleV;
	RwV3d pos;
	sRealAngle3 ang;
	RpClump* pClumpInstance;
	RpAtomic* pAtomicInstance;
};
class TObjEffFlyJump;
class TObjEffFlyJump2 : public TObject, public C_COLLI
{
public:
	virtual void TDisp();
	virtual void Exec();
	virtual void UpdateFrame();
	virtual void SetMaterialColor(const RwRGBA*);
	virtual ~TObjEffFlyJump2();
	TObjEffFlyJump2(TObjEffFlyJump*, s32);
	virtual RwRGBA* GetMaterialColor();
	s8 playerno;
	RwRGBA rgba;
	f32 rotation, scaleH_Max, scaleH, scaleV;
	RwV3d pos;
	sAngle ang;
	RpClump* pClumpInstance;
	RpAtomic* pAtomicInstance;
};
class TObjEffFlyJump : public TObject, public C_COLLI
{
public:
	virtual void TDisp();
	virtual void Exec();
	virtual void UpdateFrame();
	virtual void SetMaterialColor(const RwRGBA*);
	virtual ~TObjEffFlyJump();
	TObjEffFlyJump(TObject*, s32);
	const RwV3d& GetPos() { return pos; }
	const sAngle& GetAng() { return ang; }
	virtual RwRGBA* GetMaterialColor();
	s8 playerno, counter;
	s16 timer;
	RwRGBA rgba;
	f32 rad, rad_Max, rotation, scaleH, scaleV;
	RwV3d pos;
	sAngle ang;
	f32 y_offset;
	RwV3d spd;
	// GC uses natural four-byte RwMatrix alignment: F4, then clump134, size138.
	RwMatrix matrix;
	RpClump* pClumpInstance;
};
class TObjEffBrim : public TObject, public C_COLLI
{
public:
	virtual void Disp();
	virtual void TDisp();
	virtual void Exec();
	virtual void UpdateVertexes();
	virtual void AddVertexes();
	virtual void SetEffBrimMaterialColor(const RwRGBA*);
	virtual RwRGBA* GetEffBrimMaterialColor();
	virtual void RenderEffBrim();
	virtual s32 GetCurrentNodeNum();
	virtual EffBrim_Node* GetCurrentNode();
	virtual s32 GetPreviousNodeNum();
	virtual EffBrim_Node* GetPreviousNode();
	virtual ~TObjEffBrim();
	TObjEffBrim(TObject*, s32);
	s8 playerno, characterno;
	s16 num_node;
	RwRGBA rgba;
	f32 rad, rad_Max, rotation;
	EffBrim_Node node[126];
	RwIm3DVertex vtx[126];
	RwV3d pos;
	sAngle ang;
};
void SetEffectBrimForSpeed(s32);
void SetEffectFlyJump(s32);
void SetEffectBrim(s32);
void EndEffBrim();
void InitEffBrim();
#endif
