#include "types.h"

// TObjEnemyPawn::EnemyMD_Dropped (the PS2 build's name, by its member order):
// entering it (0) flags both collision shapes (0x20 in their damage byte),
// sets the dropped motion (10) and clears the drop counter; leaving it (3)
// resets the first shape's size.

typedef struct PawnShape {
	u8 kind;   // 0x00
	u8 form;   // 0x01
	u8 push;   // 0x02
	u8 damage; // 0x03
	u8 unk04[0x10];
	f32 a; // 0x14
	u8 unk18[0x18];
} PawnShape; // 0x30

typedef struct Pawn {
	u8 unk000[0x38];
	PawnShape* shapes; // 0x038
	u8 unk03C[0x98];
	s32 motion; // 0x0D4
	u8 unk0D8[0x178];
	s32 drops; // 0x250
} Pawn;

extern "C" const f32 pawnShapeSize[1];

static inline void pawnFlagShape(PawnShape* shape)
{
	if (shape != NULL) {
		shape->damage |= 0x20;
	}
}

extern "C" void EnemyMD_Dropped__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawnFlagShape(&pawn->shapes[0]);
			pawnFlagShape(&pawn->shapes[1]);
			pawn->motion = 10;
			pawn->drops  = 0;
			break;
		case 3:
			if (pawn->shapes != NULL) {
				pawn->shapes->a = pawnShapeSize[0];
			}
			break;
	}
}
