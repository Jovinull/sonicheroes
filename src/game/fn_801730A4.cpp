// Initialises an object of the unit around 0x8017306C (HYPOTHESIS): stores the given word and the
// kind 0x29A, sets both matrices at 0xC and 0x4C to the identity (with this unit's .sdata2 1.0f
// lbl_8042F498 and 0.0f lbl_8042F49C), sets the four floats at 0x8C to 1.0f and those at 0x9C to
// 0.0f, the mode at 0x8 to 6, and clears the 0x54 bytes from 0xAC. Returns the object. Field
// names are inferred from this function only.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Object801730A4 {
	void* owner;   // 0x0
	s32 kind;      // 0x4
	s32 mode;      // 0x8
	RwMatrix a;    // 0xC
	RwMatrix b;    // 0x4C
	f32 ones[4];   // 0x8C
	f32 zeros[4];  // 0x9C
	u8 rest[0x54]; // 0xAC
};

extern "C" {
extern f32 lbl_8042F498;
extern f32 lbl_8042F49C;

Object801730A4* fn_801730A4(Object801730A4* object, void* owner)
{
	object->owner = owner;
	object->kind  = 0x29A;
	RW_MATRIX_SET_IDENTITY(&object->a, lbl_8042F498, lbl_8042F49C);
	RW_MATRIX_SET_IDENTITY(&object->b, lbl_8042F498, lbl_8042F49C);
	object->ones[0]  = lbl_8042F498;
	object->ones[1]  = lbl_8042F498;
	object->ones[2]  = lbl_8042F498;
	object->ones[3]  = lbl_8042F498;
	object->zeros[0] = lbl_8042F49C;
	object->zeros[1] = lbl_8042F49C;
	object->zeros[2] = lbl_8042F49C;
	object->zeros[3] = lbl_8042F49C;
	object->mode     = 6;
	memset(object->rest, 0, sizeof(object->rest));
	return object;
}
}
