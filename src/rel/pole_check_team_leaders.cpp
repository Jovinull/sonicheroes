#include "types.h"

// TObjPole::CheckTeamLeaders (the PS2 build's name), the same in the thirteen
// stage modules that share the engine core: the team leader nearest the pole
// is taken into the pole's own space (turned by its Z then Y angle, from its
// base); the pole answers the leader's team when the leader is between the
// pole's base and its length and within its reach of the shaft, and -1
// otherwise.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
};

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct PoleShape {
	u8 unk00[0xC];
	f32 centerY; // 0x0C
	u8 unk10[0x4];
	f32 a; // 0x14
	f32 b; // 0x18
	u8 unk1C[0x14];
} PoleShape; // 0x30

typedef struct Pole {
	u8 unk000[0x30];
	u8 colli[0x10];  // 0x030 (C_COLLI)
	PoleShape* info; // 0x040
	u8 unk044[0x78]; // 0x044
	RwV3d pos;       // 0x0BC
	s32 angX;        // 0x0C8
	s32 angY;        // 0x0CC
	s32 angZ;        // 0x0D0
	u8 unk0D4[0x8];  // 0x0D4
	f32 radius;      // 0x0DC
	f32 length;      // 0x0E0
	f32 height;      // 0x0E4
	u8 unk0E8[0x24]; // 0x0E8
	RpClump* model;  // 0x10C
} Pole;

typedef struct PolePlayer {
	u8 unk000[0x9BC];
	s8 team; // 0x9BC
} PolePlayer;

typedef struct PoleCharacter {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} PoleCharacter;

extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 poleOne[1];
extern "C" const f32 poleZero[1];
extern "C" const f32 poleReachSquared;
extern "C" PolePlayer* lbl_802AD070[];
extern "C" PoleCharacter* lbl_802AD090[];

s32 SearchTheNearestLeaderPlayer(RwV3d* pos);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" void fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);

extern "C" s32 CheckTeamLeaders__8TObjPoleFv(Pole* pole)
{
	RwMatrixTag matrix;
	RwMatrixTag inverse;
	s32 no = SearchTheNearestLeaderPlayer(&pole->pos);

	if (no == -1) {
		return -1;
	}
	RwV3d local = lbl_802AD090[no]->pos;
	fn_80195790(&matrix, &AxisZ, poleOne[0] - fn_800D7AE4(pole->angZ), fn_800D7B00(pole->angZ), 0);
	fn_80195790(&matrix, &AxisY, poleOne[0] - fn_800D7AE4(pole->angY), fn_800D7B00(pole->angY), 2);
	fn_80196050(&matrix, &pole->pos, 2);
	fn_80195B5C(&inverse, &matrix);
	fn_8019941C(&local, &local, 1, &inverse);
	if (local.y < poleZero[0] || local.y > pole->length) {
		return -1;
	}
	if (local.x * local.x + local.z * local.z > poleReachSquared) {
		return -1;
	}
	if (lbl_802AD070[no] == NULL) {
		return -1;
	}
	return lbl_802AD070[no]->team;
}
