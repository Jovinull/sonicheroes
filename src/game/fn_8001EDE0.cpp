// Virtual method (vtable lbl_80241244 +0x60) of a TObject-derived class whose name is UNKNOWN:
// calls the virtual at +0x44 and then sets the word at +0x2C to -1. HYPOTHESIS: a state reset that
// also clears a cached index; the roles are UNKNOWN.
#include "types.h"

// Minimal local view of the vtable up to the slots used: TObject's nine virtuals, then the class's
// own (names UNKNOWN). Nothing is defined here, so no vtable is emitted.
struct Header8001EDE0 {
	u8 pad00[0x18];
};

class Obj8001EDE0 : public Header8001EDE0
{
public:
	virtual ~Obj8001EDE0();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	virtual void UnknownSlot2C();
	virtual void UnknownSlot30();
	virtual void UnknownSlot34();
	virtual void UnknownSlot38();
	virtual void UnknownSlot3C();
	virtual void UnknownSlot40();
	virtual void UnknownSlot44();

	u8 pad1C[0x2C - 0x1C];
	s32 unknown2C; // 0x2C
};

extern "C" void fn_8001EDE0(Obj8001EDE0* o)
{
	o->UnknownSlot44();
	o->unknown2C = -1;
}
