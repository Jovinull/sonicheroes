#include "types.h"
#include "game/effect/eff_bomb.h"

// TObjEnemyPawn::EnemyMD_Destroy (the PS2 build's name, by its member order):
// entering it (0) runs the enemy's destruction (its virtual at vtable offset
// 0x3C) and, for kinds 2 and 3, sends command 7 with the pawn's team and who
// broke it; while in it (1) the pawn asks to be removed (Signal bit 1).

struct sEnemyCommand {
	u8 type;    // 0x00
	s8 team;    // 0x01
	s32 sender; // 0x04

	sEnemyCommand()
	{
		type = 0;
		team = 0;
	}
	void Send();
};

typedef struct PawnSetData {
	u8 unk00[0x2A];
	s8 team; // 0x2A
} PawnSetData;

class TObjEnemyPawn : public TObject
{
public:
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void Virtual38();
	virtual void Destroyed(); // 0x3C

	u8 unk028[0x88];
	PawnSetData* setData; // 0x0B0
	u8 unk0B4[0x17C];
	s32 breaker; // 0x230
	u8 unk234[0x159];
	s8 kind; // 0x38D
};

extern "C" void EnemyMD_Destroy__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(
    TObjEnemyPawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->Destroyed();
			if (pawn->kind == 2 || pawn->kind == 3) {
				sEnemyCommand command;

				command.type   = 7;
				command.sender = 0;
				command.team   = pawn->setData->team;
				command.sender = pawn->breaker;
				command.Send();
			}
			break;
		case 1:
			pawn->Signal |= 1;
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
