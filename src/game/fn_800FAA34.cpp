#include "types.h"

// SetEffectFireSpike (CORROBORATED by PS2 metadata and the stored class name order): creates a EffFireSpike
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

struct THeapCtrl {
	void* Malloc(u32);
	void Free(void*);
};

extern "C" THeapCtrl* lbl_8042C148;

// TObject layout used by this family (cf. matched src/game/enemy_voice.cpp): the class
// keeps its dispatch table pointer in a plain field at 0x18, not an ABI vptr.
struct TObject {
	u8 pad[0x18];
	void** vtable;
	u8 pad2[0x28 - 0x1C];

	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size);
	static void operator delete(void* p);
};

inline void* TObject::operator new(unsigned long size)
{
	return lbl_8042C148->Malloc(size);
}

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;
extern "C" void* lbl_8042C504;
extern "C" void* lbl_8025A1DC[];
extern "C" f32 lbl_8042E5DC;
extern "C" void* fn_80150588(void*);
extern "C" void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(void*);
extern "C" void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(void*);

struct EffFireSpike : TObject {
	s8 unk28;
	u8 unk29;
	u16 unk2a;
	f32 unk2c;
	u32 unk30;
	void* clump;

	EffFireSpike(s32 a, TObject* parent);
};

inline EffFireSpike::EffFireSpike(s32 a, TObject* parent)
    : TObject(parent)
{
	vtable = lbl_8025A1DC;
	unk28  = a;
	unk29  = 0xFF;
	unk2a  = 0;
	unk2c  = lbl_8042E5DC;
	clump  = fn_80150588(lbl_8042C504);
	if (clump != 0) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(clump);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(clump);
	}
}

extern "C" void fn_800FAA34(s32 arg0)
{
	TObject* parent = lbl_8042C2A0;
	if (parent == 0)
		parent = lbl_8042C110;
	new EffFireSpike(arg0, parent);
}
