// Calls the virtual at +0x30 of every allocated player object (lbl_802AD070, eight slots). The
// method's name and role are UNKNOWN.
#include "types.h"

struct Header8003CAD4 {
	u8 pad00[0x18];
};

// Minimal local view of the player vtable up to the slot used (TObject's nine virtuals first).
class Player8003CAD4 : public Header8003CAD4
{
public:
	virtual ~Player8003CAD4();
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
};

extern "C" {
extern Player8003CAD4* lbl_802AD070[8];
}

extern "C" void fn_8003CAD4(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (lbl_802AD070[i] != NULL) {
			lbl_802AD070[i]->UnknownSlot30();
		}
	}
}
