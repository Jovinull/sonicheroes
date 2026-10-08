#ifndef GAME_EFFECT_EFF_ROCKETAXEL_H
#define GAME_EFFECT_EFF_ROCKETAXEL_H
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
	s32 GetChildCount();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	// Natural two-byte tail padding to 0x28; no named filler needed.
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p) { lbl_8042C148->Free(p); }
};

class EffRocketJump : public TObject
{
public:
	EffRocketJump(TObject*, s32);
	virtual ~EffRocketJump();
	virtual void TDisp();
	virtual void Exec();
	s8 playerno;
	u8 alpha;
	s16 rotate;
	void* pClumpInstance;
};

class EffRocketAxel : public TObject
{
public:
	EffRocketAxel(TObject*, s32);
	virtual ~EffRocketAxel();
	virtual void TDisp();
	virtual void Exec();
	s8 playerno;
	u8 alpha;
	s16 rotate;
	void* pClumpInstance;
};

class EffRocketHitB : public TObject
{
public:
	EffRocketHitB(TObject*, s32);
	virtual ~EffRocketHitB();
	virtual void TDisp();
	virtual void Exec();
	s8 playerno;
	u8 alpha;
	s16 rotate;
	f32 scale, scaleMax;
	void* pClumpInstance;
	s16 rotateBase;
	RwV3d vOffset;
};

class EffRocketHit : public TObject
{
public:
	EffRocketHit(TObject*, s32);
	virtual ~EffRocketHit();
	virtual void TDisp();
	virtual void Exec();
	s8 playerno;
	u8 alpha;
	s16 rotate;
	f32 scale, scaleMax;
	void* pClumpInstance;
};

void SetEffectRocketJump(s32);
void SetEffectRocketAxel(s32);
void SetEffectRocketHit(s32);
void InitEffRocketAxel();
void EndEffRocketAxel();
#endif
