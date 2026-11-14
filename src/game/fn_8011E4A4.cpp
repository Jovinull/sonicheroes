#include "types.h"

// SetPlayerFlame (CORROBORATED by PS2 metadata and the stored class name "TObjPlayerFlame"): creates a TObjPlayerFlame
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

extern "C" void fn_8011DCC0(void* self, TObject* parent, s32 a, s32 b);

class TObjPlayerFlame : public TObject
{
public:
	TObjPlayerFlame(TObject* parent, s32 a, s32 b) { fn_8011DCC0(this, parent, a, b); }

private:
	u8 unk00[0xD8];
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;

extern "C" TObject* fn_8011E4A4(s32 a, s32 b)
{
	TObject* parent = lbl_8042C2A0;
	if (lbl_8042C2A0 == NULL)
		parent = lbl_8042C110;
	return new TObjPlayerFlame(parent, a, b);
}
