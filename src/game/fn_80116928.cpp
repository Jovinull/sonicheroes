#include "types.h"

// DestroyBobsleigh() (CORROBORATED by the PS2 build, where DestroyBobsleigh__Fv follows the
// BobsleighTime constructor as here): deletes the four task objects of the table lbl_80288E0C
// (virtual destructor) and clears each slot. What the table holds is UNKNOWN (HYPOTHESIS: the
// bobsleighs).

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

// Local view of TObject: only the virtual destructor (vtable slot 0 after the two header words)
// is used here.
class TObject : public TObjectBase
{
public:
	virtual ~TObject();
};

extern "C" TObject* lbl_80288E0C[4];

void DestroyBobsleigh(void)
{
	for (int i = 0; i < 4; i++) {
		if (lbl_80288E0C[i] != NULL) {
			delete lbl_80288E0C[i];
			lbl_80288E0C[i] = NULL;
		}
	}
}
