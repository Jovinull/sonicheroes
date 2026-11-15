#include "types.h"

// Minimal local view of the TObject/TObjEnemy layout (see game/enemy/e_link.h
// and the local TObjEnemy view in src/game/enemy/e_link.cpp). TObjectBase is a
// non-polymorphic 0x18-byte base, so TObject's vtable pointer lands at 0x18.

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

class TObjEnemy : public TObject
{
public:
	virtual void UnknownSlot2C();
	virtual void UnknownSlot30();
	virtual void UnknownSlot34();
	virtual void UnknownSlot38();
	virtual void UnknownSlot3C();
	virtual void UnknownSlot40();
	virtual void UnknownSlot44(s32);
	virtual void UnknownSlot48();
	virtual void UnknownSlot4C(s32);
	u8 unknown28[0x19C - 0x28];
	s32 state; // 0x19C
};

extern "C" void fn_800A31B8(TObjEnemy* enemy, s32 state)
{
	enemy->UnknownSlot4C(enemy->state);
	enemy->state = state;
	enemy->UnknownSlot44(enemy->state);
}
