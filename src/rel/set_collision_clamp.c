#include "types.h"

// TObjSetCollision's parameter guard, the last slot of its second base's
// vtable, the same slot switchClamp and springClamp fill for their classes.
// Like the switch it also refreshes the four labels the editor shows, one per
// field, all four picked by the shape the volume is set to.
//
// The claim is .text 0x5F4C to 0x6074 and .rodata 0xE8 to 0xF0. The four name
// tables and the label block stay with the module and are reached as
// externals: the block is written by another function that is still assembly,
// and the strings the tables point at sit between them, so no single range
// covers what would have to be claimed.
//
// The strings say what the fields are. The shape picks between "SPHERE",
// "CYLINDER", "RECTANGLE" and "CYLINDER XZ", so it is bounded to zero through
// three, and the three sizes are bounded to zero up to a thousand. Which of the
// three sizes a shape actually uses is what the other tables encode: a sphere
// labels the first "Scale R" and the other two "not in use", a cylinder adds
// "Scale H", and so on.
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else.

typedef struct SetCollisionParams {
	s32 shape; // 0x00
	f32 sizeX; // 0x04
	f32 sizeY; // 0x08
	f32 sizeZ; // 0x0C
} SetCollisionParams;

typedef struct Frame {
	u8 unk0[0x2C];              // 0x00
	SetCollisionParams* params; // 0x2C
} Frame;

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* setCollisionLabels[];
extern "C" const char* setCollisionShapeNames[];
extern "C" const char* setCollisionSizeXNames[];
extern "C" const char* setCollisionSizeYNames[];
extern "C" const char* setCollisionSizeZNames[];

// The object it is called on is not used: everything it touches hangs off the
// keyframe it is handed, or is module wide.
extern "C" void setCollisionClamp(void* object, Frame* frame)
{
	SetCollisionParams* params = frame->params;

	if (params->shape < 0) {
		params->shape = 0;
	}
	if (params->shape >= 4) {
		params->shape = 3;
	}

	if (params->sizeX < 0.0f) {
		params->sizeX = 0.0f;
	}
	if (params->sizeX > 1000.0f) {
		params->sizeX = 1000.0f;
	}

	if (params->sizeY < 0.0f) {
		params->sizeY = 0.0f;
	}
	if (params->sizeY > 1000.0f) {
		params->sizeY = 1000.0f;
	}

	if (params->sizeZ < 0.0f) {
		params->sizeZ = 0.0f;
	}
	if (params->sizeZ > 1000.0f) {
		params->sizeZ = 1000.0f;
	}

	setCollisionLabels[0] = setCollisionShapeNames[params->shape];
	setCollisionLabels[1] = setCollisionSizeXNames[params->shape];
	setCollisionLabels[2] = setCollisionSizeYNames[params->shape];
	setCollisionLabels[3] = setCollisionSizeZNames[params->shape];
}
