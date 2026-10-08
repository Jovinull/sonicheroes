#ifndef GAME_ENEMY_E_GADGET_H
#define GAME_ENEMY_E_GADGET_H
#include "game/pathctrl.h"
struct RpClump;
class TObjEnemy;
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
class TEnemyGadget : public TObject
{
public:
	enum eGadgetMode {
		E_GM_NOACTION,
		E_GM_STANDBY,
		E_GM_PREATTACK,
		E_GM_ATTACK,
		E_GM_POSTATTACK,
		E_GM_NUM
	};

	TEnemyGadget(TObjEnemy*);
	virtual ~TEnemyGadget() { }
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void SetClump(RpClump* pcp) { pClump = pcp; }
	virtual void Update() { }
	virtual void DispOpaq() { }
	virtual void DispTrans() { }
	// The two UnknownSlot methods retain provisional reconstruction names.
	virtual s32 ReqGadgetMode(eGadgetMode) = 0;
	virtual void DelClump() { }
	virtual void UnknownSlot44() { }
	virtual void UnknownSlot48() { }
	virtual s32 CanDisp() { return 1; }
	s32 CheckCameraFrustum(const RwV3d*, f32);
	TObjEnemy* pOwner;
	RpClump* pClump;
	eGadgetMode gmode;
	s32 IsKilled;
};
#endif
