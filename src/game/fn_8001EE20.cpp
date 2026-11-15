// Virtual method (vtable lbl_80241244 +0x64) of a TObject-derived class whose name is UNKNOWN:
// calls the virtual at +0x40 and then sets the word at +0x30 to -1. HYPOTHESIS: a state reset that
// also clears a cached index; the roles are UNKNOWN.
#include "types.h"

// Minimal local view of the vtable up to the slots used: TObject's nine virtuals, then the class's
// own (names UNKNOWN). Nothing is defined here, so no vtable is emitted.
struct Header8001EE20 {
	u8 pad00[0x18];
};

class Obj8001EE20 : public Header8001EE20
{
public:
	virtual ~Obj8001EE20();
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

	u8 pad1C[0x30 - 0x1C];
	s32 unknown30; // 0x30
};

extern "C" void fn_8001EE20(Obj8001EE20* o)
{
	o->UnknownSlot40();
	o->unknown30 = -1;
}
