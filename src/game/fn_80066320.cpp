// Creates the particle core lbl_8042C2E0 (a TObjPtclCore, the object the PARTICLE_MATERIAL
// constructors register with) under lbl_8042C11C when there is none, and clears lbl_8042C2E4.
// HYPOTHESIS: the core's creation function; its own name and lbl_8042C2E4's role are UNKNOWN.
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
	void Free(void*);
};

extern "C" THeapCtrl* lbl_8042C148;

class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	virtual ~TObject();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	// Out of line (__dl__7TObjectFPv), as the retail exception table shows.
	static void operator delete(void* p);
};

// Local view (0x78 bytes; the constructor's mangled name is CORROBORATED by the PS2 build).
class TObjPtclCore : public TObject
{
public:
	TObjPtclCore(TObject* parent);
	virtual ~TObjPtclCore();

	u8 unknown28[0x78 - 0x28];
};

extern "C" {
extern TObject* lbl_8042C11C;
extern TObjPtclCore* lbl_8042C2E0;
extern s32 lbl_8042C2E4;
}

extern "C" void fn_80066320(void)
{
	if (lbl_8042C2E0 == NULL) {
		lbl_8042C2E0 = new TObjPtclCore(lbl_8042C11C);
		lbl_8042C2E4 = 0;
	}
}
