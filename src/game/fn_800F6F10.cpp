// Creates an effect object (vtable lbl_80259E6C; the class name is UNKNOWN) under lbl_8042C2A0, or
// under lbl_8042C110 when there is none: the inlined constructor stores `kind` (+0x28), 0xFE
// (+0x29), clears +0x2A, sets +0x2C to 0.6 and loads the model lbl_8042C4CC (fn_80150588) at +0x34,
// which is then set to ignore lights and to modulate its material colour. The object is not kept
// (it lives in the task tree). HYPOTHESIS: a result-screen decoration; the roles are UNKNOWN.
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

struct RpClump;

void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);

extern "C" {
extern void* lbl_80259E6C[];
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern void* lbl_8042C4CC;
extern f32 lbl_8042E53C; // 0.6f
RpClump* fn_80150588(void* model);
}

class Obj800F6F10 : public TObject
{
public:
	Obj800F6F10(TObject* parent, s32 kind)
	    : TObject(parent)
	{
		vtable     = lbl_80259E6C;
		this->kind = kind;
		unknown29  = 0xFE;
		unknown2A  = 0;
		unknown2C  = lbl_8042E53C;
		clump      = fn_80150588(lbl_8042C4CC);
		if (clump != NULL) {
			objRpClumpForAllGeometrysToIgnoreLights(clump);
			objRpClumpForAllGeometrysToModulateMaterialColor(clump);
		}
	}

	s8 kind;       // 0x28
	u8 unknown29;  // 0x29
	s16 unknown2A; // 0x2A
	f32 unknown2C; // 0x2C
	u8 pad30[4];
	RpClump* clump; // 0x34
};

extern "C" void fn_800F6F10(s8 kind)
{
	TObject* parent = lbl_8042C2A0;

	if (parent == NULL) {
		parent = lbl_8042C110;
	}
	new Obj800F6F10(parent, kind);
}
