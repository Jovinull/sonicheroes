// Records two 2D ranges in the object: origin originA (+0x40, copied as two words) with the extent
// toward a (+0x58), and origin originB (+0x10) with the extent toward b (+0x28). Flag bit 1 of the
// word at +0x64 is set unless all four extent components equal lbl_8042F428 (zero). Names are
// UNKNOWN.
#include "types.h"

struct Vec2_8016A804 {
	float x;
	float y;
};

// The retail code copies the origins as two plain words (integer registers).
struct Vec2Words8016A804 {
	unsigned int w[2];
};

struct Object8016A804 {
	unsigned char pad0[0x10];
	Vec2_8016A804 originB; // 0x10
	unsigned char pad18[0x28 - 0x18];
	Vec2_8016A804 extentB; // 0x28
	unsigned char pad30[0x40 - 0x30];
	Vec2_8016A804 originA; // 0x40
	unsigned char pad48[0x58 - 0x48];
	Vec2_8016A804 extentA; // 0x58
	unsigned char pad60[0x64 - 0x60];
	unsigned int flags; // 0x64
};

extern "C" {
// .sdata2 constant 0.0f (non-const: reloaded as an ordinary global).
extern float lbl_8042F428;

void fn_8016A804(Object8016A804* object, const Vec2_8016A804* originA, const Vec2_8016A804* a,
    const Vec2_8016A804* b, const Vec2_8016A804* originB)
{
	*(Vec2Words8016A804*)&object->originB = *(const Vec2Words8016A804*)originB;
	object->extentB.x                     = b->x - originB->x;
	object->extentB.y                     = b->y - originB->y;
	*(Vec2Words8016A804*)&object->originA = *(const Vec2Words8016A804*)originA;
	object->extentA.x                     = a->x - originA->x;
	object->extentA.y                     = a->y - originA->y;
	if (lbl_8042F428 == object->extentB.x && lbl_8042F428 == object->extentB.y
	    && lbl_8042F428 == object->extentA.x && lbl_8042F428 == object->extentA.y) {
		object->flags &= ~2;
	} else {
		object->flags |= 2;
	}
}
}
