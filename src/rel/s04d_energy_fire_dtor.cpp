#include "types.h"

// TObjS04EnergyFire's destructor (rel/s04d_energy_fire_create.cpp builds the
// object). It is objSecollisionDtor's body (rel/obj_secollision_dtor.cpp): it
// restores both class vtables, ends the placement when its condition has bit
// 0x10000 set, destroys the collision and placement bases and the object
// base, and frees the object when the deleting-destructor flag asks for it.
// Only stage03D has it.

typedef struct EnergyFireSetData {
	u8 unk00[0x18];
	u32 flags; // 0x18
} EnergyFireSetData;

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct EnergyFire {
	TObject base;               // 0x00
	EnergyFireSetData* setdata; // 0x28
	void** vtable2;             // 0x2C
	u8 colli[0x94];             // 0x30
} EnergyFire;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__17TObjS04EnergyFire[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__10TObjSetObjFv(void* setobj, s32 flags);
extern "C" void SetEnd__10TObjSetObjFv(void* setobj);

// TObjSetObj::TstConditionBit, inline in the class.
static inline s32 energyFireTstConditionBit(EnergyFire* object, u32 flag)
{
	return (object->setdata->flags & flag) != 0;
}

extern "C" EnergyFire* __dt__17TObjS04EnergyFireFv(EnergyFire* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = __vt__17TObjS04EnergyFire;
		object->vtable2     = __vt__17TObjS04EnergyFire + 0xB;

		if (energyFireTstConditionBit(object, 0x10000) == 1) {
			SetEnd__10TObjSetObjFv(&object->setdata);
		}

		__dt__7C_COLLIFv(object->colli, 0);
		__dt__10TObjSetObjFv(&object->setdata, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
