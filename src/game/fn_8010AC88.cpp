#include "types.h"

// SetDummyRingBomb (CORROBORATED by PS2 metadata and the stored class name "TObjDummyRingBomb"): creates a TObjDummyRingBomb
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* p);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject
{
public:
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

extern "C" void fn_8010AA24(void* self, TObject* parent, s32 a, s32 b, s32 c);

class TObjDummyRingBomb : public TObject
{
public:
	TObjDummyRingBomb(TObject* parent, s32 a, s32 b, s32 c) { fn_8010AA24(this, parent, a, b, c); }

private:
	u8 unk00[0x130];
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C114;

extern "C" TObjDummyRingBomb* fn_8010AC88(TObject* parent, s32 a, s32 b, s32 c)
{
	if (parent == NULL) {
		parent = lbl_8042C2A0;
		if (lbl_8042C2A0 == NULL)
			parent = lbl_8042C114;
	}
	return new TObjDummyRingBomb(parent, a, b, c);
}
