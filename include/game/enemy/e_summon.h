#ifndef GAME_ENEMY_E_SUMMON_H
#define GAME_ENEMY_E_SUMMON_H
#include "types.h"
// TObject's GC contract: inherited member prefix, vptr at 0x18, size 0x28.
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
class TEnemySummon : public TObject
{
public:
	s32 SummonEnemy();
	s32 CreateSummonPtcl();
	virtual void Exec();
	virtual ~TEnemySummon();
	TEnemySummon(TObject* ptp, u8 communicationId);
	static void Create(u8 communicationId);
	s32 mMode;
	s32 mTimer;
	u8 mCommunicationId;
};
#endif
