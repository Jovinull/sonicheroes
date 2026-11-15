#include "types.h"

// SetEffectVolcanicDunk (CORROBORATED by PS2 metadata and the stored class name order): creates a TObjEffVolcanicDunk
// (out-of-line constructor fn_800F8CB4) through TObject's task-heap operator new. Names are from PS2; the symbols keep their
// address-based names.

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

extern "C" void fn_800F8CB4(void* self, TObject* parent, s32 kind, void* position, void* rotation);

class TObjEffVolcanicDunk : public TObject
{
public:
	TObjEffVolcanicDunk(TObject* parent, s32 kind, void* position, void* rotation)
	{
		fn_800F8CB4(this, parent, kind, position, rotation);
	}

private:
	u8 unk00[0xE0];
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;

extern "C" void fn_800FA750(s32 kind, void* position, void* rotation)
{
	TObject* parent = lbl_8042C2A0;
	if (lbl_8042C2A0 == NULL)
		parent = lbl_8042C110;
	new TObjEffVolcanicDunk(parent, kind, position, rotation);
}
