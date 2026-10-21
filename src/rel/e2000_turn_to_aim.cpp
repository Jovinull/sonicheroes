#include "types.h"

// TObjEnemyE2000::TurnToAimForE2000 (the PS2 build's name, by its place in the
// PS2 order of the E2000's members: after DecideHoverSpeed, before
// DispJetEffect). The body of TObjEnemySearcher's TurnToAimForSearcher
// (rel/searcher_turn_to_aim.inc): it turns toward the aim and reports whether
// it got there (an angle difference under 0x80 snaps it on).

typedef struct E2000 {
	u8 unk000[0x150];
	s32 angY;         // 0x150
	u8 unk154[0x20];  // 0x154
	s32 aimAngY;      // 0x174
	u8 unk178[0x8];   // 0x178
	s32 turnSpeed;    // 0x180
	u8 unk184[0x140]; // 0x184
	s32 turning;      // 0x2C4
} E2000;

s32 AdjustAngle(s32 angle, s32 aim, s32 speed);
extern "C" s32 fn_800A5A54(E2000* enemy);

extern "C" int TurnToAimForE2000__14TObjEnemyE2000Fv(E2000* enemy)
{
	s32 diff;

	if (enemy->turning == 0) {
		return 0;
	}
	diff        = fn_800A5A54(enemy);
	enemy->angY = AdjustAngle(enemy->angY, enemy->aimAngY, enemy->turnSpeed);
	if (diff < 0x80) {
		enemy->angY = enemy->aimAngY;
		return 1;
	}
	return 0;
}
