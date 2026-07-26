#include "types.h"

// The pair that moves a stage object's placement around: push the scale it is
// carrying out to the part it drives, and pull position, rotation and scale in
// from the keyframe it was placed with.
//
// The claim is .text 0x5984 to 0x5A34 and nothing else. Neither reads a
// constant or a table of its own, which is what makes the pair cuttable without
// taking any data with it.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// The push rereads the part between the three stores and the pull rereads the
// keyframe between the position and the rotation, both because a store through
// the object could have changed the pointer it just read. That is why the two
// are written out through the object rather than through a local: a local would
// hold the pointer across the stores and drop the rereads. The parameter block
// is read once into a local, on the other hand, because the original keeps it.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
} Rot3;

typedef struct Params {
	s32 kind;   // 0x00
	Vec3 scale; // 0x04
} Params;

typedef struct Frame {
	Vec3 position;  // 0x00
	Rot3 rotation;  // 0x0C
	u8 unk18[0x14]; // 0x18
	Params* params; // 0x2C
} Frame;

typedef struct Part {
	u8 unk0[0x14]; // 0x00
	Vec3 scale;    // 0x14
} Part;

typedef struct Object {
	u8 unk0[0x28];  // 0x00
	Frame* frame;   // 0x28
	u8 unk2C[0x4];  // 0x2C
	u8 unk30[0x10]; // 0x30
	Part* part;     // 0x40
	u8 unk44[0x74]; // 0x44
	s32 kind;       // 0xB8
	u8 unkBC[0x4];  // 0xBC
	Vec3 position;  // 0xC0
	Rot3 rotation;  // 0xCC
	Vec3 scale;     // 0xD8
} Object;

extern "C" void fn_80021384(void* part);

extern "C" void objPushScale(Object* object)
{
	if (object->part != NULL) {
		object->part->scale.x = object->scale.x;
		object->part->scale.y = object->scale.y;
		object->part->scale.z = object->scale.z;
		fn_80021384(&object->unk30);
	}
}

extern "C" void objPullPlacement(Object* object)
{
	Params* params = object->frame->params;

	object->position = object->frame->position;
	object->rotation = object->frame->rotation;
	object->scale    = params->scale;
	object->kind     = params->kind;
}
