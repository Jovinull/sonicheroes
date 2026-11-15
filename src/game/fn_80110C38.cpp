#include "types.h"

// InitHintManager (CORROBORATED by PS2 metadata): creates the stage's hint and message task,
// DispMessageTask, and keeps it in lbl_8042C610 (PS2: pDispMessageTask). DispMessageTask is a
// TObject, so the new-expression allocates and cleans up through TObject's operator new/delete.

struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;

// Only the part of TObject this unit needs (the full class is in game/effect/eff_footprints.h).
// Its operator delete is the out-of-line __dl__7TObjectFPv, as the retail exception table shows.
class TObject
{
public:
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

class DispMessageTask : public TObject
{
public:
	DispMessageTask();

private:
	u8 unk00[0x84];
};

extern DispMessageTask* lbl_8042C610;

extern "C" void fn_80110C38(void)
{
	lbl_8042C610 = new DispMessageTask;
}
