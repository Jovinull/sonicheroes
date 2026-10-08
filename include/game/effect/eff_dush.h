#ifndef GAME_EFFECT_EFF_DUSH_H
#define GAME_EFFECT_EFF_DUSH_H
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
class EffDush
{
public:
	void RenderEffDush();
	void SetEffDushMaterialColor(const RwRGBA*);
	~EffDush(); // NON-virtual: metadata/GC subobject size8, no vptr.
	EffDush();
	RwRGBA rgba;
	void* pClumpInstance;
};
class EffDash : public TObject, public EffDush
{
public:
	virtual void TDisp();
	virtual void Exec();
	virtual ~EffDash();
	EffDash(TObject*, s32);
	s8 playerno, timer;
	u8 alpha;
	sRealAngle3 ang3;
};
void SetEffectDash(s32);
void EndEffDush();
void InitEffDush();

#endif
