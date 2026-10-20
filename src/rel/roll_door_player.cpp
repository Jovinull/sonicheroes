#include "types.h"
#include "MSL_C/math.h"

// TObjRolldoor::RolldoorPlayer (the PS2 build's name): every player standing
// in the doorway (its position seen in the door's frame within 12 across, from
// -2 to 15 high and within 20 deep) is pushed through: along the door's angles
// at its speed when the door has no turn, else (the first time) along its turn
// in the door's plane. Each pushed player's team reacts, and the door plays
// sound 0x1056 when it pushed someone.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RollDoorPlayerInfo {
	u8 unk000[0x25E]; // 0x000
	s8 team;          // 0x25E
} RollDoorPlayerInfo;

typedef struct RollDoor {
	u8 unk00[0xBC]; // 0x00
	s16 pushTime;   // 0xBC
	u8 unkBE[0x2];  // 0xBE
	RwV3d pos;      // 0xC0
	s32 angX;       // 0xCC
	s32 angY;       // 0xD0
	s32 angZ;       // 0xD4
	u8 unkD8[0x4];  // 0xD8
	f32 speed;      // 0xDC
	s32 turn;       // 0xE0
} RollDoor;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 lbl_8_rodata_AE8[1];
extern "C" const f32 lbl_8_rodata_AEC[1];
extern "C" const f32 rollDoorHalfWidth[1];
extern "C" const f32 rollDoorFifteen[1];
extern "C" const f32 rollDoorFloor[1];
extern "C" const f32 rollDoorHalfDepth[1];
extern "C" RollDoorPlayerInfo* lbl_802AD0D0[];
extern "C" void* lbl_8042C388;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" RwMatrixTag* fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, void* angle);
extern "C" void fn_800E0880(s32 player, RwV3d* velocity, s32* angle, s16 time);
extern "C" void fn_800E0710(s32 player, RwV3d* velocity, s32* angle, s16 time);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg3);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);

extern "C" void RolldoorPlayer__12TObjRolldoorFv(RollDoor* object)
{
	RwV3d velocity;
	RwV3d pos;
	RwV3d local;
	RwMatrixTag matrix;
	RwMatrixTag inverse;
	f32 sin;
	s32 pushed;
	s32 i;

	sin = fn_800D7B00(object->angY);
	fn_80195790(&matrix, &AxisY, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angY), sin, 0);
	sin = fn_800D7B00(object->angX);
	fn_80195790(&matrix, &AxisX, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angX), sin, 2);
	sin = fn_800D7B00(object->angZ);
	fn_80195790(&matrix, &AxisZ, lbl_8_rodata_AE8[0] - fn_800D7AE4(object->angZ), sin, 2);
	fn_80196050(&matrix, &object->pos, 2);
	fn_80195B5C(&inverse, &matrix);
	velocity.x = object->speed;
	velocity.y = velocity.z = lbl_8_rodata_AEC[0];
	pushed                  = 0;
	for (i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 1, &pos, NULL) == 0) {
			continue;
		}
		fn_8019941C(&local, &pos, 1, &inverse);
		if ((f32)__fabs(local.x) > rollDoorHalfWidth[0]) {
			continue;
		}
		if (local.y > rollDoorFifteen[0]) {
			continue;
		}
		if (local.y < rollDoorFloor[0]) {
			continue;
		}
		if ((f32)__fabs(local.z) > rollDoorHalfDepth[0]) {
			continue;
		}
		if (object->turn == 0) {
			fn_800E0880(i, &velocity, &object->angX, object->pushTime);
		} else {
			if (pushed == 0) {
				velocity.x = object->speed * fn_800D7AE4(object->turn);
				velocity.y = object->speed * fn_800D7B00(object->turn);
				velocity.z = lbl_8_rodata_AEC[0];
			}
			fn_800E0710(i, &velocity, &object->angX, object->pushTime);
		}
		fn_8001F674(lbl_802AD0D0[i]->team, 4, 0xF, 0);
		pushed = 1;
	}
	if (pushed != 0 && lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1056, 0x10, 0);
	}
}
