#include "types.h"

// TObjBobsleigh::PlayersRide (the PS2 build's name): brings the team aboard,
// returning whether all three members are seated. It works out the three seat
// positions (the sled's matrix moved to each of the module's seat offsets).
// A member not in boarding mode (0x21) is just dropped (and counts as done).
// One that is found flies to its seat (by its type 0, 1 or 2): close enough
// (or in a race) it is seated with its riding pose; well above the seat it
// glides down; otherwise it jumps over with its own velocity, launched by
// CalcV2 when it has none, and lands (velocity cleared) once falling below it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
} RwMatrixTag;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BobsleighTeam {
	u8 unk000[0x110];
	s8 members[4]; // 0x110
} BobsleighTeam;

typedef struct BobsleighPlayerState {
	s16 mode; // 0x00
} BobsleighPlayerState;

typedef struct BobsleighRider {
	u8 unk000[0x150];
	s16 pose; // 0x150
	u8 unk152[0x102];
	s32 type; // 0x254
} BobsleighRider;

typedef struct Bobsleigh {
	u8 unk000[0xF0];
	u8 replace[0x14]; // 0x0F0 (OBJ_ReplacePlayer)
	RwV3d pos;        // 0x104
	s32 pathAngX;     // 0x110
	s32 pathAngY;     // 0x114
	s32 pathAngZ;     // 0x118
	u8 unk11C[0xC];
	sAngle seatAngle; // 0x128
	u8 unk134[0x44];
	RwV3d riderVel[3]; // 0x178
	s32 team;          // 0x19C
	RwV3d seats[3];    // 0x1A0
	u8 unk1C4[0x3C];
	s32 angX; // 0x200
	s32 angY; // 0x204
	s32 angZ; // 0x208
	u8 unk20C[0x154];
	s32 race; // 0x360
} Bobsleigh;

extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" BobsleighPlayerState* lbl_802AD090[];
extern "C" BobsleighRider* lbl_802AD0D0[];
extern "C" RwV3d bobsleighSeatOffsets[];
extern "C" s32 bobsleighSeatTypes[];
extern "C" const f32 bobsleighOne[1];
extern "C" const f32 bobsleighZero[1];
extern "C" const f32 bobsleighSeatReach[1];
extern "C" const f32 bobsleighGlideHeight[1];
extern "C" const f32 bobsleighGlideRate[1];
extern "C" const f32 bobsleighJumpSpeed[1];
extern "C" const f32 bobsleighGravity[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern RwMatrixTag* pCurrentMatrix;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" s32 fn_800927D0(BobsleighTeam* team, int type);
extern "C" void fn_800E1208(int player, int kind, int arg);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, sAngle* angle);
f32 AdjustFloat(f32 value, f32 target, f32 rate);
int CalcV2(RwV3d* from, RwV3d* to, f32 height, f32 speed, RwV3d* velocity);

// The same layout under another name, for the copy (see rel/bobsleigh_player_ride.cpp).
typedef struct RwMatrixCopy {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
} RwMatrixCopy;

static inline RwV3d* bobsleighMatrixPos(RwMatrixTag* matrix)
{
	return matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos;
}

extern "C" bool PlayersRide__13TObjBobsleighFv(Bobsleigh* object)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];
	u32 done            = 0;
	RwMatrixTag seats[3];
	RwMatrixTag matrix;
	RwV3d pos;
	RwV3d delta;
	sAngle angle;
	int seatNo;
	int i;

	fn_80196050(&matrix, &object->pos, 0);
	fn_80195790(
	    &matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->angZ), fn_800D7B00(object->angZ), 1);
	fn_80195790(
	    &matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->angX), fn_800D7B00(object->angX), 1);
	fn_80195790(
	    &matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->angY), fn_800D7B00(object->angY), 1);
	fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->pathAngZ),
	    fn_800D7B00(object->pathAngZ), 1);
	fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->pathAngX),
	    fn_800D7B00(object->pathAngX), 1);
	fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->pathAngY),
	    fn_800D7B00(object->pathAngY), 1);
	for (seatNo = 0; seatNo < 3; seatNo++) {
		*(RwMatrixCopy*)&seats[seatNo] = *(RwMatrixCopy*)&matrix;
		fn_80196050(&seats[seatNo], &bobsleighSeatOffsets[seatNo], 1);
		object->seats[seatNo] = *bobsleighMatrixPos(&seats[seatNo]);
	}
	for (i = 0; i < 3; i++) {
		int no = team->members[fn_800927D0(team, bobsleighSeatTypes[i])];
		RwV3d* seat;
		f32 dy;

		if (lbl_802AD090[no]->mode != 0x21) {
			fn_800E1208(no, 9, 0);
			done |= 1 << i;
			continue;
		}
		if (!fn_8003E2E4(no, 0, &pos, 0)) {
			continue;
		}
		if (lbl_802AD0D0[no]->pose != 9) {
			fn_800E1208(no, 10, 9);
		}
		switch (lbl_802AD0D0[no]->type) {
			case 0:
				seat = &object->seats[0];
				break;
			case 1:
				seat = &object->seats[1];
				break;
			case 2:
				seat = &object->seats[2];
				break;
		}
		delta.x = seat->x - pos.x;
		delta.y = seat->y - pos.y;
		delta.z = seat->z - pos.z;
		if (fn_801991B4(&delta) < bobsleighSeatReach[0] || object->race != 0) {
			pos = *seat;
			done |= 1 << i;
			switch (lbl_802AD0D0[no]->type) {
				case 0:
					fn_800E1208(no, 9, 9);
					break;
				case 1:
					fn_800E1208(no, 9, 0x5C);
					break;
				case 2:
					fn_800E1208(no, 9, 0x66);
					break;
			}
			angle.x = object->seatAngle.x;
			angle.y = 0x4000 - (object->seatAngle.y ^ 0x8000);
			angle.z = object->seatAngle.z;
			objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
			    object->replace, no, 0, &pos, &angle);
		} else {
			dy = pos.y - seat->y;
			if (dy > bobsleighGlideHeight[0]) {
				pos.x = AdjustFloat(pos.x, seat->x, bobsleighGlideRate[0]);
				pos.z = AdjustFloat(pos.z, seat->z, bobsleighGlideRate[0]);
				pos.y = AdjustFloat(pos.y, seat->y, bobsleighGlideRate[0]);
			} else if (bobsleighZero[0] == fn_801991B4(&object->riderVel[i])) {
				if (CalcV2(&pos, seat, bobsleighGlideHeight[0] + seat->y, bobsleighJumpSpeed[0],
				        &object->riderVel[i])
				    != 0) {
					goto fly;
				}
				pos.x                 = AdjustFloat(pos.x, seat->x, bobsleighGlideRate[0]);
				pos.z                 = AdjustFloat(pos.z, seat->z, bobsleighGlideRate[0]);
				pos.y                 = AdjustFloat(pos.y, seat->y, bobsleighGlideRate[0]);
				object->riderVel[i].x = object->riderVel[i].y = object->riderVel[i].z
				    = bobsleighZero[0];
			} else if (object->riderVel[i].y < bobsleighZero[0] && dy < bobsleighZero[0]) {
				pos.x                 = AdjustFloat(pos.x, seat->x, bobsleighGlideRate[0]);
				pos.z                 = AdjustFloat(pos.z, seat->z, bobsleighGlideRate[0]);
				pos.y                 = AdjustFloat(pos.y, seat->y, bobsleighGlideRate[0]);
				object->riderVel[i].x = object->riderVel[i].y = object->riderVel[i].z
				    = bobsleighZero[0];
			} else {
			fly:
				pos.x += object->riderVel[i].x;
				pos.y += object->riderVel[i].y;
				pos.z += object->riderVel[i].z;
				object->riderVel[i].y += bobsleighGravity[0];
			}
		}
		objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
		    object->replace, no, 0, &pos, NULL);
	}
	return done == 7;
}
