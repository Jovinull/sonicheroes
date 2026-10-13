#include "types.h"

// TObjEnemyPawn::EnemyMD_TornadoStirredUp (the PS2 build's name, by its member
// order): entering it (0) sets the stirred-up motion (8) and its rise speed,
// starts the enemy base's lift (fn_800A3CBC), keeps the team that blew it and
// scores the tornado for it, and lets both collision shapes hurt again (the
// first one grown to 10); while in it (1), once the lift is over
// (fn_800A37A4) the pawn loses a hit point, keeps the leader of the blowing
// team as who broke it and asks for mode 0x1C.

class TEnemyScoreMan
{
public:
	static void CreateInstance();
	static TEnemyScoreMan* EnemyScoreMan;
	void TornadoEnemy(s32 teamnumber);
};

typedef struct PawnShape {
	u8 kind;   // 0x00
	u8 form;   // 0x01
	u8 push;   // 0x02
	u8 damage; // 0x03
	u8 unk04[0x10];
	f32 a; // 0x14
	u8 unk18[0x18];
} PawnShape; // 0x30

typedef struct PawnTeam PawnTeam;

typedef struct Pawn {
	u8 unk000[0x2E];
	s16 hpShown; // 0x02E
	u8 unk030[0x8];
	PawnShape* shapes; // 0x038
	u8 unk03C[0x98];
	s32 motion; // 0x0D4
	u8 unk0D8[0x84];
	f32 riseSpeed; // 0x15C
	u8 unk160[0x44];
	f32 hp; // 0x1A4
	u8 unk1A8[0x88];
	s32 breaker; // 0x230
	s32 blower;  // 0x234
	u8 unk238[0x10];
	s32 nextMode; // 0x248
	u8 unk24C[0xA8];
	s32 blowerTeam; // 0x2F4
} Pawn;

extern "C" PawnTeam* lbl_80303DC8[];
extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnStirSpeed[1];
extern "C" const f32 pawnStirShapeSize[1];
extern "C" const f32 pawnOne[1];

extern "C" void fn_800A3CBC(Pawn* pawn);
extern "C" int fn_800A37A4(Pawn* pawn);
extern "C" s32 fn_8009278C(PawnTeam* team, int type);

static inline TEnemyScoreMan* pawnScoreMan()
{
	if (TEnemyScoreMan::EnemyScoreMan == NULL) {
		TEnemyScoreMan::CreateInstance();
	}
	return TEnemyScoreMan::EnemyScoreMan;
}

static inline void pawnUnflagShape(PawnShape* shape)
{
	if (shape != NULL) {
		shape->damage &= ~0x20;
	}
}

extern "C" void EnemyMD_TornadoStirredUp__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(
    Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			PawnShape* shape;

			pawn->motion    = 8;
			pawn->riseSpeed = pawnStirSpeed[0];
			fn_800A3CBC(pawn);
			pawn->blowerTeam = pawn->blower;
			pawnScoreMan()->TornadoEnemy(pawn->blower);
			shape = pawn->shapes;
			if (shape != NULL) {
				shape->damage &= ~0x20;
				shape->a = pawnStirShapeSize[0];
			}
			pawnUnflagShape(&pawn->shapes[1]);
			break;
		}
		case 1:
			if (fn_800A37A4(pawn)) {
				const f32* limit;

				if ((pawn->hp -= pawnOne[0]) < *(limit = pawnZero)) {
					pawn->hp = *limit;
				}
				pawn->hpShown = pawn->hp;
				if (pawn->blowerTeam != -1 && lbl_80303DC8[pawn->blowerTeam] != NULL) {
					pawn->breaker = fn_8009278C(lbl_80303DC8[pawn->blowerTeam], 0);
				}
				pawn->nextMode = 0x1C;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
