#include "types.h"

// The no-input collision's NoInputCollisionParameter (the PS2 build's name;
// noInputCollisionParameter here): it gives the collision's shape the box size
// and has the collision work out its range again.

typedef struct NoInputShape {
	u8 unk00[0x14]; // 0x00
	f32 x, y, z;    // 0x14
} NoInputShape;

typedef struct NoInputCollision {
	u8 base[0x30];       // 0x00
	u8 colli[0x10];      // 0x30
	NoInputShape* shape; // 0x40
	u8 unk44[0x94];      // 0x44
	f32 sizeX;           // 0xD8
	f32 sizeY;           // 0xDC
	f32 sizeZ;           // 0xE0
} NoInputCollision;

extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void noInputCollisionParameter(NoInputCollision* object)
{
	if (object->shape != NULL) {
		object->shape->x = object->sizeX;
		object->shape->y = object->sizeY;
		object->shape->z = object->sizeZ;
		CalcRange__7C_COLLIFv(object->colli);
	}
}
