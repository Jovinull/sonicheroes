#include "types.h"

// TObjBigrings::SetBigringsPointer (the PS2 build's name, by its place in the
// PS2 order; bigRingsSetBigringsPointer here): the three rings point back at
// the group.

typedef struct BigRings BigRings;

typedef struct BigRingsElement {
	u8 unk00[0x2C];
	BigRings* owner; // 0x2C
	u8 unk30[0x4];
} BigRingsElement; // 0x34

struct BigRings {
	u8 unk00[0x68];
	BigRingsElement* rings; // 0x68
};

extern "C" void bigRingsSetBigringsPointer(BigRings* object)
{
	if (object->rings != NULL) {
		object->rings[0].owner = object;
		object->rings[1].owner = object;
		object->rings[2].owner = object;
	}
}
