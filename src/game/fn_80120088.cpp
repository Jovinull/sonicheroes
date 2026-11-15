#include "types.h"

// CreateResultDGauge (CORROBORATED by PS2 metadata and the stored class name "SpOutputTex"): creates a SpOutputTex (stored in the RDGauge pointer lbl_8042C704)
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* p);
};
struct TObject;

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern TObject* lbl_8042C118;
extern TObject* lbl_8042C704;
void* fn_80136F14(TObject*, TObject*);
}

class TObject
{
public:
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

class SpOutputTex : public TObject
{
public:
	SpOutputTex(TObject* parent) { fn_80136F14(this, parent); }

private:
	u8 unk00[0x40];
};

extern "C" void fn_80120088()
{
	if (lbl_8042C704 == 0)
		lbl_8042C704 = new SpOutputTex(lbl_8042C118);
}
