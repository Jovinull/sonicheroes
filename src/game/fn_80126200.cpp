#include "types.h"

// TMemoryCardCtrl::Create(TObject*) (CORROBORATED by PS2 metadata and the stored class name
// "TMemoryCardCtrl"): creates a TMemoryCardCtrl through TObject's task-heap operator new and its
// out-of-line constructor. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32 size);
};

extern "C" THeapCtrl* lbl_8042C148;

class TObject
{
public:
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);
};

class TMemoryCardCtrl : public TObject
{
public:
	TMemoryCardCtrl(TObject* parent);

private:
	u8 unk00[0x27c];
};

extern "C" void* fn_80126200(TObject* parent)
{
	return new TMemoryCardCtrl(parent);
}
