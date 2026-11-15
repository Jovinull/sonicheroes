#include "types.h"

// SetChaotixSpotLight (CORROBORATED by PS2 metadata and the stored class name "TObjChaotixSpotLight"): creates a TObjChaotixSpotLight
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

extern "C" void fn_8012282C(TObject* self, TObject* parent, s32 a, s32 b);

class TObjChaotixSpotLight : public TObject
{
public:
	TObjChaotixSpotLight(TObject* parent, s32 a, s32 b) { fn_8012282C(this, parent, a, b); }

private:
	u8 unk00[0x68];
};

extern "C" TObject* lbl_8042C108;

extern "C" TObject* fn_80122AF4(TObject* parent, s32 a, s32 b)
{
	if (parent == NULL)
		parent = lbl_8042C108;
	return new TObjChaotixSpotLight(parent, a, b);
}
