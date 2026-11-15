#include "types.h"

// SetEffectFirePillarBig (CORROBORATED by PS2 metadata and the stored class name order): creates a TObjEffFirePillarBig
// through TObject's task-heap operator new. Names are from PS2; the symbol keeps its address-based name.

extern "C" void* Malloc__9THeapCtrlFUi(void*, u32);
extern "C" void* lbl_8042C148;

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

typedef void RpAtomic;

struct TObject {
	const char* className;
	u16 flags;
	u8 pad6[0x12];
	void** vtable;
	u8 pad1c[0xc];

	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}
	static void operator delete(void*);
};

struct TObjEffFirePillarBig : TObject {
	s8 kind;
	u8 alpha;
	u16 timer;
	f32 scale;
	s32 state;
	void* model;
	sAngle angle;
	RwV3d position;

	inline TObjEffFirePillarBig(TObject*, s32, RwV3d*, sAngle*);
};

extern "C" {
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern const char* lbl_8042B6F8;
extern void* lbl_8025A0D4[];
extern f32 lbl_8042E584;
extern void* lbl_8042C514;
extern char lbl_8042B700;

void* fn_80150588(void*);
RpAtomic* fn_801491A8(RpAtomic*);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(void*, u32);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(void*);
void* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(void*, void*, char*);
}

inline TObjEffFirePillarBig::TObjEffFirePillarBig(
    TObject* parent, s32 kindValue, RwV3d* pos, sAngle* rot)
    : TObject(parent)
{
	vtable                    = lbl_8025A0D4;
	className                 = lbl_8042B6F8;
	*(u16*)((u8*)this + 0x1e) = 0x50;
	kind                      = kindValue;
	alpha                     = 0x80;
	scale                     = lbl_8042E584;
	position.x                = pos->x;
	position.y                = pos->y;
	position.z                = pos->z;
	angle.x                   = rot->x;
	angle.y                   = rot->y;
	angle.z                   = rot->z;
	state                     = 0;
	timer                     = 0;
	model                     = fn_80150588(lbl_8042C514);
	if (model != 0) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(model, 0x10);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(model);
		fn_801491A8(
		    objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(model, 0, &lbl_8042B700));
	}
}

extern "C" void fn_800FA510(s32 kind, RwV3d* pos, sAngle* rot)
{
	TObject* parent = lbl_8042C2A0;
	if (parent == 0)
		parent = lbl_8042C110;
	new TObjEffFirePillarBig(parent, kind, pos, rot);
}
