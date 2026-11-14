#include "types.h"

// SetEffectMeteorBomb (CORROBORATED by PS2 metadata and the stored class name order): creates a TObjMeteorBomb
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

extern "C" void fn_800F7308(void* self, TObject* parent, s32 a, s32 b, s32 c);

class TObjMeteorBomb : public TObject
{
public:
	TObjMeteorBomb(TObject* parent, s32 a, s32 b, s32 c) { fn_800F7308(this, parent, a, b, c); }

private:
	u8 unk00[0x124];
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;

extern "C" void fn_800FA494(s32 a, s32 b, s32 c)
{
	TObject* parent = lbl_8042C2A0;
	if (lbl_8042C2A0 == NULL)
		parent = lbl_8042C110;
	new TObjMeteorBomb(parent, a, b, c);
}
