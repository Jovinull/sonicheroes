#include "types.h"

// TObjEnemyPawn::RcvBrokenCommand (the PS2 build's name, by its member order):
// unless the pawn is of kind 2 or 3, keeps who broke it and flags it broken.

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

extern "C" void RcvBrokenCommand__13TObjEnemyPawnFP13sEnemyCommand(
    Pawn* pawn, sEnemyCommand* command)
{
	if (pawn->kind == 2 || pawn->kind == 3) {
		return;
	}
	if (command != NULL) {
		pawn->breaker = command->sender;
		pawn->broken  = 1;
	}
}
