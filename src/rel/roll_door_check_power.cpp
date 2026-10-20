#include "types.h"

// TObjRolldoor::CheckCollisionOfPowerToChangeMode (the PS2 build's name): the
// door only opens for a power member. Touched by kind 0x13 it does nothing;
// when no kind 0xC hitter touches it, it only plays the knock sound (0x1053)
// for a hitter whose collision info is of kinds 1 to 3, and answers 0. A kind
// 0xC hitter pushes it open away from the side it came from (mode 2 or 3,
// pushed at -15 or 15), with sound 0x1055, and the answer is 1.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RollDoorInfo {
	u8 unk00[0x3]; // 0x00
	u8 kind;       // 0x03
} RollDoorInfo;

typedef struct RollDoorHitter {
	u8 unk00[0x10];     // 0x00
	RollDoorInfo* info; // 0x10
	u8 unk14[0x4C];     // 0x14
	RwV3d pos;          // 0x60
} RollDoorHitter;

typedef struct RollDoorHit {
	u8 unk00[0x4];          // 0x00
	RollDoorHitter* hitter; // 0x04
} RollDoorHit;

typedef struct RollDoor {
	u8 unk00[0x30]; // 0x00
	u8 colli[0x88]; // 0x30 (C_COLLI)
	s32 mode;       // 0xB8
	u8 unkBC[0x4];  // 0xBC
	RwV3d pos;      // 0xC0
	s32 angX;       // 0xCC
	s32 angY;       // 0xD0
	u8 unkD4[0x14]; // 0xD4
	f32 side;       // 0xE8
} RollDoor;

extern "C" void* lbl_8042C388;
extern "C" const f32 rollDoorRadToAngle[1];
extern "C" const f32 rollDoorPushBack[1];
extern "C" const f32 rollDoorFifteen[1];

extern "C" void fn_80021824(void* colli);
extern "C" RollDoorHit* fn_80020BD8(void* colli, s32 kind);
extern "C" RollDoorHit* fn_800211A8(void* colli);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
extern "C" double atan2(double y, double x);
int DiffAngle(int a, int b);

static inline RollDoorHitter* rollDoorHitter(RollDoorHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" s32 CheckCollisionOfPowerToChangeMode__12TObjRolldoorFv(RollDoor* object)
{
	RollDoorHitter* hitter;

	fn_80021824(object->colli);
	if (rollDoorHitter(fn_80020BD8(object->colli, 0x13)) != NULL) {
		return 0;
	}
	fn_80021824(object->colli);
	hitter = rollDoorHitter(fn_80020BD8(object->colli, 0xC));
	if (hitter == NULL) {
		s32 knocked = 0;

		fn_80021824(object->colli);
		while ((hitter = rollDoorHitter(fn_800211A8(object->colli))) != NULL) {
			if ((hitter->info->kind & 3) > 0) {
				knocked = 1;
				break;
			}
		}
		if (knocked && lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1053, 0x30, 0);
		}
		return 0;
	}
	RwV3d from = hitter->pos;
	f32 toward = atan2(object->pos.x - from.x, object->pos.z - from.z);
	if (DiffAngle(-object->angY + (s32)(rollDoorRadToAngle[0] * toward), 0) > 0x4000) {
		object->side = rollDoorPushBack[0];
		object->mode = 2;
	} else {
		object->side = rollDoorFifteen[0];
		object->mode = 3;
	}
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1055, 0x10, 0);
	}
	return 1;
}
