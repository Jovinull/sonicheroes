#ifndef GAME_ENEMY_E_ICONMAN_H
#define GAME_ENEMY_E_ICONMAN_H
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
class TEnemyIcon;
enum eEnemyIcon {
	E_ICON_HP,
	E_ICON_SEARCH,
	E_ICON_FREEZE,
	E_ICON_COUNTDOWN,
	E_ICON_CIRCLE,
	E_ICON_CROSS,
	E_ICON_NOTE,
	E_ICON_EFFECT,
	E_ICON_SLEEP,
	E_ICON_QUESTION,
	E_ICON_GC_10 // GC-added HP variant; original enumerator is not recovered.
};
class TEnemyIconMan : public TObject
{
public:
	TEnemyIconMan(eEnemyIcon);
	virtual ~TEnemyIconMan();
	virtual void Exec();
	virtual void Disp();
	s32 IsOn();
	void Close();
	void Change(eEnemyIcon);
	void Off();
	void On(f32, f32, s32);
	void On(f32, f32);
	void SetPos(const RwV3d*, const RwV3d*);
	void CreateIconInstance(eEnemyIcon);
	static TEnemyIconMan* Create(eEnemyIcon);
	static void Finalize();
	static void Initialize();
	TEnemyIcon* mpIcon;
	eEnemyIcon mIconNo;
};
// GC class name and virtual slots establish this class; it is absent in the
// earlier PS2 metadata. The private state name is provisional.
class TMissionFailure : public TObject
{
public:
	TMissionFailure();
	virtual ~TMissionFailure();
	virtual void Exec();
	s32 state;
};
extern char* CL_TEnemyIconMan;
extern "C" void fn_8010AF38();
#endif
