// Destroys the particle manager singleton lbl_8042C2E0 (virtual destructor) and the heap control
// lbl_8042C2E4 when they exist, clearing both pointers. HYPOTHESIS: the manager's DestroyInstance,
// counterpart of fn_80066320.
#include "types.h"

struct Header800662BC {
	u8 pad00[0x18];
};

// Local view: the manager is polymorphic (vtable at +0x18, virtual destructor in the first slot).
class Manager800662BC : public Header800662BC
{
public:
	virtual ~Manager800662BC();
};

class THeapCtrl
{
public:
	~THeapCtrl();
};

extern "C" {
extern Manager800662BC* lbl_8042C2E0;
extern THeapCtrl* lbl_8042C2E4;
}

extern "C" void fn_800662BC(void)
{
	if (lbl_8042C2E0 != NULL) {
		delete lbl_8042C2E0;
		lbl_8042C2E0 = NULL;
	}
	if (lbl_8042C2E4 != NULL) {
		delete lbl_8042C2E4;
		lbl_8042C2E4 = NULL;
	}
}
