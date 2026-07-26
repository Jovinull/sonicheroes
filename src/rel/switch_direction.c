#include "types.h"

// Converts the switch's facing vector into the coordinate system used by its
// collision contact. The horizontal components are scaled and tiny results are
// snapped to zero before the vector is transformed back into world space.
//
// The claim is .text 0x3940 to 0x3A40. The code is shared by the same thirteen
// stage modules as the rest of TObjSwitch.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Contact {
	u8 unk0[0x50];
	u8 matrix[0x40];
} Contact;

typedef struct ContactOwner {
	u8 unk0[0x4];
	Contact* contact;
} ContactOwner;

typedef struct Switch {
	u8 unk0[0x90];
	Vec3 facing;
	u8 unk9C[0x34];
	Vec3 direction;
	u8 unkDC[0x10];
	ContactOwner* owner;
} Switch;

extern "C" const f32 lbl_3_rodata_A0;
extern "C" const f32 lbl_3_rodata_A4;
extern "C" const f32 lbl_3_rodata_A8;

extern "C" void* fn_8019E8EC(void* matrix);
extern "C" void fn_80195B5C(void* out, const void* matrix);
extern "C" void fn_8019941C(Vec3* out, const Vec3* in, s32 count, void* matrix);

extern "C" void switchDirection(Switch* object)
{
	u8 inverse[0x40];
	Vec3 local;
	Contact* contact = object->owner->contact;

	fn_80195B5C(inverse, fn_8019E8EC(contact));
	fn_8019941C(&local, &object->facing, 1, inverse);

	local.y = lbl_3_rodata_A0;
	local.x *= lbl_3_rodata_A4;
	if ((f32)__fabs(local.x) < lbl_3_rodata_A8) {
		local.x = lbl_3_rodata_A0;
	}
	local.z *= lbl_3_rodata_A4;
	if ((f32)__fabs(local.z) < lbl_3_rodata_A8) {
		local.z = lbl_3_rodata_A0;
	}

	fn_8019941C(&object->direction, &local, 1, contact->matrix);
}
