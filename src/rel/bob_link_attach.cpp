#include "types.h"

// A helper of the special stages' sled link object (bobLinkAttach here; the
// class has no PS2 name), in stage01D and stage07D: it fills the shared link
// target with the object's point and direction, registers the object
// (fn_80131088, kind 0xE), puts its slot in the world's list and marks it
// linked and active.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct BobLink {
	u8 unk00[0x28];
	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
	u8 active;   // 0x34
	u8 pad35[0x3];
	RwV3d at;  // 0x38
	RwV3d dir; // 0x44
} BobLink;

typedef struct BobLinkTarget {
	s32 unk00[4]; // 0x00
	RwV3d dir;    // 0x10
	u8 unk1C[0x18];
	RwV3d at; // 0x34
} BobLinkTarget;

extern "C" BobLinkTarget lbl_803EA4E8;
extern "C" void* lbl_8042C1F8;
extern "C" void fn_80131088(s32 kind, void* object);
extern "C" void fn_8004D9B8(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

extern "C" void bobLinkAttach(BobLink* object)
{
	lbl_803EA4E8.unk00[0] = 0;
	lbl_803EA4E8.unk00[1] = 0;
	lbl_803EA4E8.unk00[2] = 0;
	lbl_803EA4E8.unk00[3] = 0;
	lbl_803EA4E8.at.x     = object->at.x;
	lbl_803EA4E8.at.y     = object->at.y;
	lbl_803EA4E8.at.z     = object->at.z;
	lbl_803EA4E8.dir.x    = object->dir.x;
	lbl_803EA4E8.dir.y    = object->dir.y;
	lbl_803EA4E8.dir.z    = object->dir.z;
	fn_80131088(0xE, object);
	fn_8004D9B8(lbl_8042C1F8);
	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotIn);
	object->linked = 1;
	object->active = 1;
}
