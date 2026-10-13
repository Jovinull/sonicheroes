#include "types.h"

// TObjEnemyPawn::RcvHpIncCommand (the PS2 build's name, by its member order):
// for kinds 0, 1 and 4 to 7, raises the maximum hit points by the command's
// amount and fills the hit points up to it.

typedef struct sEnemyCommand {
	u8 unk00[0x4];
	union {
		s32 sender; // 0x04
		f32 amount; // 0x04
	};
	u8 unk08[0xC];
	f32 recover; // 0x14
} sEnemyCommand;

typedef struct Pawn {
	u8 unk000[0x2E];
	s16 hpShown; // 0x02E
	u8 unk030[0x16C];
	s32 state; // 0x19C
	u8 unk1A0[0x4];
	f32 hp; // 0x1A4
	u8 unk1A8[0x88];
	s32 breaker; // 0x230
	u8 unk234[0xA4];
	void* gauge; // 0x2D8
	void* icon;  // 0x2DC
	f32 shownHp; // 0x2E0
	u8 unk2E4[0x14];
	f32 maxHp; // 0x2F8
	u8 unk2FC[0x84];
	s32 broken; // 0x380
	u8 unk384[0x9];
	s8 kind; // 0x38D
} Pawn;

extern "C" void RcvHpIncCommand__13TObjEnemyPawnFP13sEnemyCommand(
    Pawn* pawn, sEnemyCommand* command)
{
	switch (pawn->kind) {
		case 0:
		case 1:
		case 4:
		case 5:
		case 6:
		case 7:
			pawn->maxHp += command->amount;
			pawn->hpShown = pawn->hp = pawn->maxHp;
			pawn->shownHp            = pawn->hp;
			break;
	}
}
