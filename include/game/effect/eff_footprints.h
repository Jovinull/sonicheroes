#ifndef GAME_EFFECT_EFF_FOOTPRINTS_H
#define GAME_EFFECT_EFF_FOOTPRINTS_H
#include "types.h"
#include "game/pathctrl.h"
#include "game/link.h"
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
class EffFootPrints : public CLASS_LINK
{
public:
	s32 Disp();
	s32 Exec();
	~EffFootPrints();
	EffFootPrints(s32);
	s8 flagLeft, noFoot, teamNo;
	f32 nowAlpha;
	RwV3d pos[4];
	RwRGBA rgba;
};
class EffFootPrintsManager : public TObject, public CLASS_LINK_MANAGER
{
public:
	virtual void TDisp();
	virtual void Exec();
	s32 EraseEffect(EffFootPrints*);
	s32 InsertEffect(EffFootPrints*);
	virtual ~EffFootPrintsManager();
	EffFootPrintsManager(TObject*, s32);
	s32 teamNo;
};
void CreateEffFootPrints(RwV3d*, sAngle*, s32, s32, RwRGBA*, s32);
void EndEffFootPrints();
void InitEffFootPrints();
#endif
