#include "game/effect/eff_bomb.h"

// TObjFormGateSub::Exec (the PS2 build's name). A gate part waiting (state 0)
// looks for a leader player passing through it (CheckLeaderPlayerInGate,
// inlined): the first player touching it that is a leader (or its formation
// check passes) and is not in states 0x3B or 0x3C. With one found it is passed
// (state 1) and the player's team is told the formation the part's kind gives
// (0 for speed, 2 for fly, 1 for power). A passed part waits until no leader is
// in it any more. Either way the collision is entered again where it is.

#include "src/rel/formgate_sub_class.inc"

void TObjFormGateSub::Exec()
{
	switch (passed) {
		case 0: {
			s32 no = CheckLeaderPlayerInGate();

			if (no != -1) {
				passed   = 1;
				s32 team = lbl_802AD0D0[no]->team;

				switch (kind) {
					case 0:
						fn_80091830(lbl_80303DC8[team], 0);
						break;
					case 1:
						fn_80091830(lbl_80303DC8[team], 2);
						break;
					case 2:
						fn_80091830(lbl_80303DC8[team], 1);
						break;
				}
			}
			break;
		}
		case 1:
			if (CheckLeaderPlayerInGate() == -1) {
				passed = 0;
			}
			break;
	}
	SetColli(&Colli().pos, &Colli().ang);
	Entry();
}
