#include "types.h"

// The attach step of the special stages' third sled link object
// (bobLinkAttachTurn here; the class has no PS2 name), in stage01D and
// stage07D: as bobLinkAttach, with the target in mode 3 and given the
// object's point, angles and reach.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BobLinkTarget {
	s32 mode;     // 0x00
	s32 unk04[3]; // 0x04
	RwV3d dir;    // 0x10
	sAngle ang;   // 0x1C
	u8 unk28[0xC];
	RwV3d at;  // 0x34
	f32 reach; // 0x40
} BobLinkTarget;

typedef struct BobLinkB {
	u8 unk00[0x28];
	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
	u8 active;   // 0x34
	u8 pad35[0x3];
	RwV3d* at; // 0x38
	RwV3d dir; // 0x3C
} BobLinkB;

typedef struct BobLinkC {
	u8 unk00[0x28];
	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
	u8 active;   // 0x34
	u8 pad35[0x3];
	sAngle ang; // 0x38
	u8 unk44[0x8];
	RwV3d at; // 0x4C
	u8 unk58[0x4];
	f32 reach; // 0x5C
} BobLinkC;

extern "C" BobLinkTarget lbl_803EA4E8;
extern "C" void* lbl_8042C1F8;
extern "C" void fn_80131088(s32 kind, void* object);
extern "C" void fn_8004D9B8(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

extern "C" void bobLinkAttachTurn(BobLinkC* object)
{
	lbl_803EA4E8.mode     = 3;
	lbl_803EA4E8.unk04[0] = 0;
	lbl_803EA4E8.unk04[1] = 0;
	lbl_803EA4E8.unk04[2] = 0;
	lbl_803EA4E8.at.x     = object->at.x;
	lbl_803EA4E8.at.y     = object->at.y;
	lbl_803EA4E8.at.z     = object->at.z;
	lbl_803EA4E8.ang      = object->ang;
	lbl_803EA4E8.reach    = object->reach;
	fn_80131088(0xE, object);
	fn_8004D9B8(lbl_8042C1F8);
	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotIn);
	object->linked = 1;
	object->active = 1;
}
