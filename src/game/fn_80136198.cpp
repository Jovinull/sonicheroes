#include "types.h"

// When the current team's entry of lbl_802D5AF0 has its word 0x8 set: hands the value from
// fn_8004E608 back to fn_8004DE10 on lbl_8042C1F8, calls the virtual at vtable offset 0x2C of the
// team's active player (lbl_802AD070[lbl_803EC330[team]]), clears bit 4 of that player's signal
// word and finishes with fn_8004D99C. The roles of the globals and of the virtual are UNKNOWN.

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
};

// Local view of the player class: only its first own virtual (vtable offset 0x2C) is used.
class Player80136198 : public TObject
{
public:
	virtual void Virtual2C();
};

struct TeamEntry80136198 {
	s32 f0;
	s32 f4;
	s32 f8;
};

extern "C" {
extern TeamEntry80136198 lbl_802D5AF0[4];
extern s32 lbl_8042C1FC;
extern s32 lbl_803EC330[4];
extern Player80136198* lbl_802AD070[8];
extern void* lbl_8042C1F8;
s32 fn_8004E608(void* p);
void fn_8004DE10(void* p, s32 value);
void fn_8004D99C(void* p);

void fn_80136198(void)
{
	if (lbl_802D5AF0[lbl_8042C1FC].f8 != 0) {
		fn_8004DE10(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8));
		lbl_802AD070[lbl_803EC330[lbl_8042C1FC]]->Virtual2C();
		lbl_802AD070[lbl_803EC330[lbl_8042C1FC]]->Signal &= ~0x10;
		fn_8004D99C(lbl_8042C1F8);
	}
}
}
