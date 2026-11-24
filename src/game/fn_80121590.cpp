// Creates the singleton task lbl_8042C700 under lbl_8042C100 when the word 0x4 of lbl_80289AE8
// is set and no instance exists yet. The class (vtable lbl_80289BA8, class name lbl_8042B928,
// display priority 0x30, 0x30 bytes) and its role are UNKNOWN; the constructor is inlined. The
// pointer is stored even when the allocation fails, as retail does.
#include "types.h"

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

struct THeapCtrl {
	void* Malloc(u32);
};

extern "C" THeapCtrl* lbl_8042C148;

// Local view of TObject for an inlined constructor: the vtable pointer is a data member (the
// class's vtable is in another split), the destructor is declared for the exception cleanup, and
// operator delete is the out-of-line __dl__7TObjectFPv, as the retail exception table shows.
class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	~TObject();
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);

	void* vtable; // 0x18
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

struct Settings80121590 {
	s32 f0;
	u32 enabled; // 0x4
	u8 pad8[0x48 - 0x8];
};

extern "C" {
extern Settings80121590 lbl_80289AE8;
extern void* lbl_80289BA8[];
extern char* lbl_8042B928;
extern TObject* lbl_8042C100;
extern TObject* lbl_8042C700;
}

class Obj80121590 : public TObject
{
public:
	Obj80121590(TObject* parent)
	    : TObject(parent)
	{
		vtable    = lbl_80289BA8;
		ClassName = lbl_8042B928;
		DispTime  = 0x30;
	}

	u8 pad28[0x30 - 0x28];
};

extern "C" void fn_80121590(void)
{
	if (lbl_80289AE8.enabled != 0 && lbl_8042C700 == NULL) {
		lbl_8042C700 = new Obj80121590(lbl_8042C100);
	}
}
