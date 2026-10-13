#include "types.h"

// TObjEnemyPawn::SetCollisionParameter (the PS2 build's name): with its second
// collision, puts it 6.5 along the up of the weapon bone (tilted -56 around X;
// the pawn's own position and the world up when there is no bone) and turns
// it to that direction.

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

typedef struct RpHAnimHierarchy RpHAnimHierarchy;

class ENEMYMTNMAN
{
public:
	RpHAnimHierarchy* GetActiveHAHPointer();
};

typedef struct PawnColli {
	u8 unk00[0x38];
	RwV3d pos; // 0x38
	u8 unk44[0x10];
	s32 angX; // 0x54
	u8 unk58[0x4];
	s32 angY; // 0x5C
} PawnColli;

typedef struct Pawn {
	u8 unk000[0x32];
	u16 colliCount; // 0x32
	u8 unk034[0x4];
	PawnColli* colli; // 0x38
	u8 unk03C[0x7C];
	ENEMYMTNMAN motion; // 0xB8
	u8 unk0B9[0x87];
	RwV3d pos; // 0x140
	u8 unk14C[0x128];
	s32 bone; // 0x274
} Pawn;

extern "C" const RwV3d AxisX;
extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnOne[1];
extern "C" const f32 pawnColliTilt[1];
extern "C" const f32 pawnColliReach[1];

extern "C" RwMatrixTag* fn_8013F47C(RpHAnimHierarchy* hierarchy);
extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
void GetAngleXZ(f32 x, f32 y, f32 z, int* angX, int* angY);

extern "C" void SetCollisionParameter__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->colli != NULL && pawn->colliCount >= 2) {
		int angX;
		int angY;
		RwV3d up;
		RwMatrixTag tilt;
		f32 x;
		f32 y;
		f32 z;
		f32 reach;
		f32 dx;
		f32 dy;
		f32 dz;

		if (pawn->bone != -1) {
			RwMatrixTag* bones = fn_8013F47C(pawn->motion.GetActiveHAHPointer());
			int i              = pawn->bone + 1;
			// &bones[i].pos would share bones + i with the copy below; the retail
			// computes the position's address on its own
			RwV3d* at = (RwV3d*)((u8*)bones + i * 0x40 + 0x30);

			x    = at->x;
			y    = at->y;
			z    = at->z;
			up.x = up.z = pawnZero[0];
			up.y        = pawnOne[0];
			tilt        = bones[i];
			fn_80195A74(&tilt, &AxisX, pawnColliTilt[0], 1);
			fn_8019947C(&up, &up, 1, &tilt);
		} else {
			x    = pawn->pos.x;
			y    = pawn->pos.y;
			z    = pawn->pos.z;
			up.x = up.z = pawnZero[0];
			up.y        = pawnOne[0];
		}
		GetAngleXZ(up.x, up.y, up.z, &angX, &angY);
		reach              = pawnColliReach[0];
		dy                 = reach * up.y;
		dz                 = reach * up.z;
		dx                 = reach * up.x;
		pawn->colli->pos.x = x + dx;
		pawn->colli->pos.y = y + dy;
		pawn->colli->pos.z = z + dz;
		pawn->colli->angX  = angX;
		pawn->colli->angY  = angY;
	}
}
