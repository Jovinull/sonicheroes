#include "types.h"

// TObjEnemyPawn::EnemyMD_TornadoBlowShield (the PS2 build's name, by its
// member order): entering it (0) lets the shield go (its state 3 and the
// module's speed), clears the guard flags (0x100 and the first shape's 0x800,
// its kind byte too), sets the blown motion (7) and plays its sound (0x400F);
// while in it (1), once flag 0x1000 is off the pawn asks for mode 10.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PawnShape {
	u8 kind; // 0x00
	u8 unk01[0x3];
	u32 attr; // 0x04
} PawnShape;

typedef struct PawnShield {
	u8 unk000[0xF0];
	s32 state; // 0x0F0
	u8 unk0F4[0x3C];
	f32 speed; // 0x130
} PawnShield;

typedef struct Pawn {
	u8 unk000[0x38];
	PawnShape* shapes; // 0x038
	u8 unk03C[0x98];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x3C];
	u32 flags188; // 0x188
	u32 flags;    // 0x18C
	u8 unk190[0xB8];
	s32 nextMode; // 0x248
	u8 unk24C[0x3];
	s8 guard; // 0x24F
	u8 unk250[0x18];
	PawnShield* shield; // 0x268
} Pawn;

extern "C" void* lbl_8042C388;
extern "C" const f32 pawnShieldSpeed[1];

extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_TornadoBlowShield__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(
    Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			PawnShield* shield = pawn->shield;

			if (shield != NULL) {
				shield->state = 3;
				shield->speed = pawnShieldSpeed[0];
				pawn->shield  = NULL;
			}
			pawn->guard  = 0;
			pawn->motion = 7;
			pawn->flags188 &= ~0x100;
			pawn->shapes->attr &= ~0x800;
			pawn->shapes->kind = 0;
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x400F, &pawn->pos, NULL, 1, 0, 0);
			}
			break;
		}
		case 1:
			if (!(pawn->flags & 0x1000)) {
				pawn->nextMode = 10;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
