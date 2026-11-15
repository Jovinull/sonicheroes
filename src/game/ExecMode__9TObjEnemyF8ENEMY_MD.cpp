// TObjEnemy::ExecMode (symbol name from the retail map): runs the control routine of a mode in the exec phase.
// The control-phase values are read from the three wrappers (InitMode 0, ExecMode 1, ExitMode 3);
// their names, and the meaning of 2, are HYPOTHESIS/UNKNOWN.
#include "types.h"

enum ENEMY_MD { ENEMY_MD_0 };

// Minimal local view of the TObject/TObjEnemy virtual table up to CtrlMode (vtable +0x50). Slot
// names come from the PS2 build where known (see src/rel/e_eggmobile_stage11.cpp); the three
// UnknownSlot entries are unnamed. Neither destructor is defined here, so this unit does not
// emit a vtable. TObject's first 0x18 bytes are a non-polymorphic header (name, signal, tree
// links), so the vtable pointer is at +0x18.
struct TObjectHdr {
	u8 pad00[0x18];
};

class TObject : public TObjectHdr
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
};

class TObjEnemy : public TObject
{
public:
	enum eCtrlSMode { CTRL_SMODE_INIT = 0, CTRL_SMODE_EXEC = 1, CTRL_SMODE_EXIT = 3 };

	virtual ~TObjEnemy();
	virtual void CheckDamage2();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void UnknownSlot38();
	virtual void UnknownSlot3C();
	virtual void UnknownSlot40();
	virtual void InitMode(ENEMY_MD);
	virtual void ExecMode(ENEMY_MD);
	virtual void ExitMode(ENEMY_MD);
	virtual void CtrlMode(ENEMY_MD, eCtrlSMode) = 0;
};

void TObjEnemy::ExecMode(ENEMY_MD mode)
{
	CtrlMode(mode, CTRL_SMODE_EXEC);
}
