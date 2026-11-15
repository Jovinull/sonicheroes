#include "types.h"

// SetEffectFirePillar (CORROBORATED by PS2 metadata and the stored class name order): creates a TObjEffFirePillar
// (vtable lbl_8025A100) through TObject's task-heap operator new. Names are from PS2; the symbols keep their
// address-based names.
// The class's vtable is not defined in this unit yet, so the constructor stores it by its current name.

struct TObjectBase {
	char* ClassName;
	u16 Signal;
	u16 Tag;
	TObjectBase* Prev;
	TObjectBase* Next;
	TObjectBase* Parent;
	TObjectBase* Child;
};

struct THeapCtrl {
	void* Malloc(u32 size);
	void Free(void* object);
};
extern "C" THeapCtrl* lbl_8042C148;

struct TObject : public TObjectBase {
	TObject(TObject* parent);
	~TObject();
	void** vtable; // 0x18
	u16 field1C;
	u16 field1E;
	u16 field20;
	u16 pad22;
	u16 field24;
	u16 pad26;
	static void* operator new(unsigned long size) { return lbl_8042C148->Malloc(size); }
	static void operator delete(void* object);
};

struct RpClump;
struct RpAtomic;
struct V3f {
	f32 x, y, z;
};
struct V3i {
	s32 x, y, z;
};

class TObjEffFirePillar : public TObject
{
public:
	TObjEffFirePillar(TObject* parent, s32 player, V3f* pos, V3i* ang);
	s8 player;      // 0x28
	u8 alpha;       // 0x29
	u16 field2A;    // 0x2A
	f32 scale;      // 0x2C
	u32 field30;    // 0x30
	RpClump* clump; // 0x34
	V3i field38;    // 0x38
	V3f field44;    // 0x44
};

extern "C" {
extern char* lbl_8042B6F4;
extern char lbl_8025A100[];
extern char lbl_8042B700[7];
extern f32 lbl_8042E584;
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern RpClump* lbl_8042C510;

RpClump* fn_80150588(RpClump*);
int fn_801491A8(int owner);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, u32);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(RpClump*, RpAtomic*, char*);
}

inline TObjEffFirePillar::TObjEffFirePillar(TObject* parent, s32 playerNo, V3f* pos, V3i* ang)
    : TObject(parent)
{
	vtable    = (void**)lbl_8025A100;
	ClassName = lbl_8042B6F4;
	field1E   = sizeof(TObjEffFirePillar);
	player    = playerNo;
	alpha     = 0x80;
	scale     = lbl_8042E584;
	field44   = *pos;
	field38   = *ang;
	field30   = 0;
	field2A   = 0;
	clump     = fn_80150588(lbl_8042C510);
	if (clump) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(clump, 0x10);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(clump);
		fn_801491A8(
		    (int)objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(clump, NULL, lbl_8042B700));
	}
}

extern "C" void fn_800FA630(s8 player, V3f* pos, V3i* ang)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new TObjEffFirePillar(parent, player, pos, ang);
}
