#include "types.h"

// SetEffectFireDunk (CORROBORATED by PS2 metadata and the stored class name order): creates an EffFireDunk
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};
extern "C" THeapCtrl* lbl_8042C148;

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

class TObject : public TObjectBase
{
public:
	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* p);

	void* vt;
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	u8 pad[2];
};

struct RpClump;
struct RpAtomic;

extern "C" {
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern int lbl_8042C500;
extern unsigned char lbl_8025A184[];
extern char lbl_8042B700[7];
void* fn_80150588(void*);
void fn_801491A8(RpAtomic*);
}
void objRpClumpForAllGeometrysToIgnoreLights(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump*);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump*, RpAtomic*, char*);

class EffFireDunk : public TObject
{
public:
	EffFireDunk(TObject* p, int a)
	    : TObject(p)
	{
		vt  = lbl_8025A184;
		f28 = a;
		f29 = 0xff;
		f2a = 0;
		f2c = (RpClump*)fn_80150588((void*)lbl_8042C500);
		if (f2c) {
			objRpClumpForAllGeometrysToIgnoreLights(f2c);
			objRpClumpForAllGeometrysToModulateMaterialColor(f2c);
			fn_801491A8(objRpClumpGetAtomicWithTexture(f2c, 0, lbl_8042B700));
		}
	}
	s8 f28;
	u8 f29;
	u16 f2a;
	RpClump* f2c;
	u32 f30;
	u32 f34;
	u32 f38;
};

extern "C" void fn_800FA95C(int a)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new EffFireDunk(parent, a);
}
