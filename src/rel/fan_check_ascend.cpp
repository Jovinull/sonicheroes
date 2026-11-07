#include "types.h"

// TObjFan::CheckAscend (the PS2 build's name; fanCheckAscend here), whether the
// fan lifts anyone this frame. While the game runs and nothing of collision
// kind 0x13 touches it, each player inside the column (within its width on the
// ground plane and from its base to its height, a higher one for a player in
// mode 0x43) is lifted: the first one on the base also starts the wind sound,
// at the camera's height kept within the column. Near the base a falling
// player is slowed; above it the lift fades with the square root of the height
// left, kept between the stage's floor and ceiling for the character. A player
// in mode 0x43 has its fall scaled, and nobody rises faster than the cap.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct PlayerTask {
	s16 mode; // 0x0
	u8 unk2[0x2];
	s16 state; // 0x4
} PlayerTask;

typedef struct PlayerWork {
	u8 unk000[0x628];
	s32 action; // 0x628
} PlayerWork;

typedef struct PlayerParam {
	u8 unk0;
	s8 character; // 0x1
} PlayerParam;

typedef struct CharacterInfo {
	u8 unk00[0x78];
	f32 lift; // 0x78
	u8 unk7C[0x8];
} CharacterInfo; // 0x84

typedef struct ColliHit {
	u8 unk0[0x4];
	u32 touching; // 0x4
} ColliHit;

typedef struct Fan {
	u8 unk00[0x30];
	u8 colli[0x90]; // 0x30, a C_COLLI
	RwV3d pos;      // 0xC0
	u8 unkCC[0x14];
	f32 height;   // 0xE0
	f32 reach;    // 0xE4
	f32 strength; // 0xE8
	f32 top;      // 0xEC
	f32 column;   // 0xF0
} Fan;

typedef struct Camera {
	u8 unk0[0x4];
	f32 y; // 0x4
} Camera;

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" Camera* lbl_802D59E0;
extern "C" PlayerTask* lbl_802AD090[8];
extern "C" PlayerWork* lbl_802AD070[8];
extern "C" RwV3d* lbl_802AD0B0[8];
extern "C" PlayerParam* lbl_802AD0D0[8];
extern "C" CharacterInfo lbl_80241560[];
extern "C" u8 fanSoundSlot;
extern "C" const f32 fanStopSpeed;
extern "C" const f32 fanBaseSize;
extern "C" const f32 fanOne;
extern "C" const f32 fanSoundReach;
extern "C" const f32 fanBaseLift;
extern "C" const f32 fanBaseSlow;
extern "C" const double fanHalf;
extern "C" const double fanThree;
extern "C" f32 fanLiftFloor;
extern "C" f32 fanFallCap;
extern "C" f32 fanLiftCeiling;
extern "C" f32 fanFallScale;

extern "C" void fn_80021824(void* colli);
extern "C" ColliHit* fn_80020BD8(void* colli, s32 kind);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);
extern "C" void fn_800E10B8(s32 player, f32 x, f32 y, f32 z);
extern "C" void fn_800DFF34(s32 player, f32 x, f32 y, f32 z);
double __frsqrte(double x);

// MSL's sqrtf, as rel/cage_class.inc has it.
static inline f32 fanSqrtf(f32 x)
{
	volatile f32 y;

	if (x > fanStopSpeed) {
		double guess = __frsqrte((double)x);
		double half  = fanHalf;
		double three;
		guess = half * guess * ((three = fanThree) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

static inline void fanLift(s32 player, f32 lift)
{
	fn_800DFF34(player, fanStopSpeed, lift, fanStopSpeed);
}

extern "C" s32 fanCheckAscend(Fan* fan)
{
	ColliHit* hit;
	s32 lifted;
	s32 sounded;
	s32 i;

	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	fn_80021824(fan->colli);
	hit = fn_80020BD8(fan->colli, 0x13);
	if ((hit != NULL ? hit->touching : 0) != 0) {
		return 0;
	}

	lifted  = 0;
	sounded = 0;
	for (i = 0; i < 8; i++) {
		PlayerTask* task = lbl_802AD090[i];
		f32 dy;
		f32 column;
		f32 lift;
		RwV3d pos;
		RwV3d offset;

		if (task == NULL || task->mode == 0x26 || task->mode == 0x27 || task->state == 0x17
		    || lbl_802AD070[i]->action == 0x12) {
			continue;
		}
		if (task->mode == 0x43) {
			column = fan->top;
		} else {
			column = fan->column;
		}
		if (fn_8003E2E4(i, 1, &pos, 0) == 0) {
			continue;
		}
		offset.x = pos.x - fan->pos.x;
		offset.y = dy = pos.y - fan->pos.y;
		offset.z      = pos.z - fan->pos.z;
		offset.y      = fanStopSpeed;
		if (fn_801991B4(&offset) > fan->height * fan->reach) {
			continue;
		}

		if (sounded == 0 && dy >= fanStopSpeed && dy <= fanSoundReach * column
		    && (s8)lbl_8042C180[0x1F] == 0) {
			if ((s8)lbl_8042C180[0x1E] == 0) {
				RwV3d at = fan->pos;

				at.y = lbl_802D59E0->y;
				if (at.y < fan->pos.y) {
					at.y = fan->pos.y;
				} else if (at.y > fan->pos.y + fan->top) {
					at.y = fan->pos.y + fan->top;
				}
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x1058, &at, (u8*)fan + 1, 3, (s8)fanSoundSlot, 5);
				}
			} else if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x1058, &fan->pos, (u8*)fan + 1, 3, (s8)fanSoundSlot, 5);
			}
			sounded = 1;
		}

		f32 zero = fanStopSpeed;
		if (dy < zero || dy > column) {
			continue;
		}
		lift = fan->strength;
		if (dy < fanBaseSize) {
			RwV3d* speed = lbl_802AD0B0[i];
			f32 fall     = -speed->y;

			if (fall > fanStopSpeed) {
				f32 diff = dy - fanBaseLift;

				if (fall > fanBaseSlow * diff) {
					fn_800E10B8(i, speed->x, fanBaseSlow * -diff, speed->z);
				}
			}
		} else {
			f32 left  = column - dy;
			f32 scale = fanOne / (column - fanBaseSize);
			lift *= fanSqrtf(left * scale);
		}
		if (lift > fanLiftCeiling) {
			lift = fanLiftCeiling;
		} else {
			f32 floor = fanLiftFloor * lbl_80241560[lbl_802AD0D0[i]->character].lift;

			if (lift < floor) {
				lift = floor;
			}
		}
		fn_800DFF34(i, 0.0f, lift, 0.0f);
		lifted = 1;
		if (lbl_802AD090[i]->mode == 0x43) {
			RwV3d* speed = lbl_802AD0B0[i];

			fn_800E10B8(i, speed->x, fanFallScale * speed->y, speed->z);
		}
		{
			RwV3d* speed = lbl_802AD0B0[i];

			if (speed->y > fanFallCap) {
				fn_800E10B8(i, speed->x, fanFallCap, speed->z);
			}
		}
	}
	return lifted;
}
