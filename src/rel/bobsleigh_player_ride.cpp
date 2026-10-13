#include "types.h"

// TObjBobsleigh::PlayerRide (the PS2 build's name): seats rider i. It builds
// the sled's matrix (moved to the sled, turned by its Z, X and Y angles and
// then by the path's Z, X and Y angles), moves a copy to the module's seat
// offset i and keeps the seat position in the sled (0x1A0 + i * 0xC); when the
// team member is found, it puts the member there facing the sled's way.

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

// The same layout under another name, for the copy: copying an RwMatrixTag
// member by member leaves &seat.pos as a common subexpression (kept in a saved
// register) that the retail does not share.
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

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BobsleighTeam {
	u8 unk000[0x110];
	s8 members[4]; // 0x110
} BobsleighTeam;

typedef struct Bobsleigh {
	u8 unk000[0xF0];
	u8 replace[0x14]; // 0x0F0 (OBJ_ReplacePlayer)
	RwV3d pos;        // 0x104
	s32 pathAngX;     // 0x110
	s32 pathAngY;     // 0x114
	s32 pathAngZ;     // 0x118
	u8 unk11C[0xC];
	sAngle seatAngle; // 0x128
	u8 unk134[0x68];
	s32 team;       // 0x19C
	RwV3d seats[3]; // 0x1A0
	u8 unk1C4[0x3C];
	s32 angX; // 0x200
	s32 angY; // 0x204
	s32 angZ; // 0x208
} Bobsleigh;

extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" RwV3d bobsleighSeatOffsets[];
extern "C" const f32 bobsleighOne[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern RwMatrixTag* pCurrentMatrix;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, sAngle* angle);

static inline RwV3d* bobsleighMatrixPos(RwMatrixTag* matrix)
{
	return matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos;
}

extern "C" void PlayerRide__13TObjBobsleighFi(Bobsleigh* object, int i)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];
	RwMatrixTag matrix;
	RwMatrixTag seat;
	RwV3d found;
	sAngle angle;
	int no;

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
	*(RwMatrixCopy*)&seat = *(RwMatrixCopy*)&matrix;
	fn_80196050(&seat, &bobsleighSeatOffsets[i], 1);
	object->seats[i] = *bobsleighMatrixPos(&seat);
	no               = team->members[i];
	if (fn_8003E2E4(no, 0, &found, 0)) {
		angle.x = object->seatAngle.x;
		angle.y = 0x4000 - (object->seatAngle.y ^ 0x8000);
		angle.z = object->seatAngle.z;
		objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
		    object->replace, no, 0, &found, &angle);
	}
}
