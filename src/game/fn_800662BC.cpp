#include "types.h"

// EndParticlecoreTask() (CORROBORATED by PS2 metadata): deletes the particle core and its heap, the two
// globals (PS2 pPtclCore, PtclHeap) only EndParticlecoreTask and InitParticlecoreTask use.
// Names are from PS2; the symbol keeps its address-based name.

struct TObjectBase {
	u8 kind[4];
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct THeapCtrl {
	u8 data[12];
	~THeapCtrl();
};

struct TObject : public TObjectBase {
	virtual ~TObject();
};

extern "C" TObject* lbl_8042C2E0;
extern "C" THeapCtrl* lbl_8042C2E4;

extern "C" void fn_800662BC(void)
{
	if (lbl_8042C2E0 != 0) {
		delete lbl_8042C2E0;
		lbl_8042C2E0 = 0;
	}
	if (lbl_8042C2E4 != 0) {
		delete lbl_8042C2E4;
		lbl_8042C2E4 = 0;
	}
}
