#ifndef GAME_ENEMY_E_OBJ_ENEMY_H
#define GAME_ENEMY_E_OBJ_ENEMY_H
#include "types.h"
#include "game/setObj.h"

// View of TObject/TObjEnemy for the per-function units of the TObjEnemy methods in main.dol.
//
// The virtual order is VERIFIED against the retail TObjEnemy vtable (0x80252FB4): the TObject
// slots (+0x08..+0x28), the TObjSetObj sub-table (+0x2C..+0x34, EditOnChange), then the
// TObjEnemy virtuals from +0x38. Method names come from the retail map where it has them and from
// the PS2 build otherwise (same list as src/rel/e_eggmobile_stage11.cpp). CtrlMode and AddItemBox
// are pure (0 in the vtable).
//
// Neither destructor is defined in these units, so including this header never emits a vtable.
// Data members are padding except the fields the units read; their names are HYPOTHESIS.

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

class TObject : public TObjectBase
{
public:
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
};

// Bytes 0x28..0xB0 of an enemy, between the TObject and TObjSetObj bases: the collision block.
// TObjEnemy::Exec calls ClearInfo__7C_COLLIFv on this+0x28, and the vtable has no sub-table for
// it (non-polymorphic). Only the size and that member are used here.
class C_COLLI
{
public:
	void ClearInfo();
	u8 unknown[0x88];
};

enum ENEMY_MD { ENEMY_MD_0 };

struct sEnemyCommand;

class TObjEnemy : public TObject, public C_COLLI, public TObjSetObj
{
public:
	// Phase passed to CtrlMode by the InitMode/ExecMode/ExitMode wrappers (0, 1 and 3). The
	// names, and the meaning of 2, are HYPOTHESIS/UNKNOWN.
	enum eCtrlSMode { CTRL_SMODE_INIT = 0, CTRL_SMODE_EXEC = 1, CTRL_SMODE_EXIT = 3 };

	virtual ~TObjEnemy();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void CheckDamage2();                                    // +0x38
	virtual void DestroyMyself();                                   // +0x3C
	virtual void Explosion();                                       // +0x40
	virtual void InitMode(ENEMY_MD);                                // +0x44
	virtual void ExecMode(ENEMY_MD);                                // +0x48
	virtual void ExitMode(ENEMY_MD);                                // +0x4C
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode) = 0;                // +0x50
	virtual void Update();                                          // +0x54
	virtual void UpdateOnEdit();                                    // +0x58
	virtual void DispOpaq();                                        // +0x5C
	virtual void DispTrans();                                       // +0x60
	virtual void DispShadow();                                      // +0x64
	virtual void DispOpaqOnEdit();                                  // +0x68
	virtual void Virtual33D94();                                    // +0x6C
	virtual s32 KillMySelf();                                       // +0x70
	virtual s32 CheckCameraFrustumTest(const RwV3d*, f32);          // +0x74
	virtual s32 CheckCameraFrustumTestForShadow(const RwV3d*, f32); // +0x78
	virtual void AddScore();                                        // +0x7C
	virtual s32 CanCheckTechnicPointForThunderShoot();              // +0x80
	virtual s32 IsSleep();                                          // +0x84
	virtual void AddItemBox(RwV3d*) = 0;                            // +0x88
	virtual RwV3d* Virtual33D98();                                  // +0x8C
	virtual s32 GetCurrentLightNum();                               // +0x90
	virtual void RcvCommand(sEnemyCommand*);                        // +0x94
	virtual void DispEnemySetting();                                // +0x98
	virtual void Virtual33DA0();                                    // +0x9C
	virtual void Virtual33DA4();                                    // +0xA0

	u8 unknownB8[0x140 - 0xB8];
	RwV3d position; // 0x140 (HYPOTHESIS: copied for the frustum tests in Disp/TDisp)
	u8 unknown14C[0x191 - 0x14C];
	s8 timers[8]; // 0x191 (HYPOTHESIS: frame countdowns, decremented to 0 by Exec)
	u8 unknown199[0x19C - 0x199];
	s32 mode; // 0x19C (see fn_800A31B8)
	u8 unknown1A0[0x220 - 0x1A0];
	f32 radius; // 0x220 (HYPOTHESIS: the frustum-test radius in Disp)
	u8 unknown224[0x230 - 0x224];
	s32 destroyer; // 0x230 (HYPOTHESIS: index of the player that destroyed the enemy, or -1)
};

#endif
