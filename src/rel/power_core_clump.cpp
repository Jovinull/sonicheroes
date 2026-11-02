#include "types.h"

// TEnemyPowerCore's DestroyClump, CloneClump and destructor (the PS2 build's
// names), the same in the bonus stages (31D-33D): the core holds a clone of
// each of the two loaded power core models; the destructor drops them (as
// DestroyClump does, inlined) and runs the collision and object bases down.

struct RpClump;

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject; // 0x28

typedef struct C_COLLI {
	u8 unk00[0x88];
} C_COLLI; // 0x88

typedef struct PowerCore {
	TObject base;  // 0x00
	C_COLLI colli; // 0x28
	u8 unkB0[0x24];
	RpClump* body;  // 0xD4
	RpClump* shine; // 0xD8
} PowerCore;

extern "C" RpClump* powerCoreModels[2];
extern "C" void* __vt__15TEnemyPowerCore[];
extern "C" void* lbl_8042C148;

extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);
extern "C" void __dt__7C_COLLIFv(C_COLLI* colli, s32 flags);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

static inline void powerCoreDropClumps(PowerCore* object)
{
	if (object->shine != NULL) {
		fn_80150958(object->shine);
		object->shine = NULL;
	}
	if (object->body != NULL) {
		fn_80150958(object->body);
		object->body = NULL;
	}
}

extern "C" void DestroyClump__15TEnemyPowerCoreFv(PowerCore* object)
{
	powerCoreDropClumps(object);
}

extern "C" void CloneClump__15TEnemyPowerCoreFv(PowerCore* object)
{
	object->body  = fn_80150588(powerCoreModels[0]);
	object->shine = fn_80150588(powerCoreModels[1]);
}

extern "C" PowerCore* __dt__15TEnemyPowerCoreFv(PowerCore* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = __vt__15TEnemyPowerCore;
		powerCoreDropClumps(object);
		__dt__7C_COLLIFv(&object->colli, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
