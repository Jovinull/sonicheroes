#include "types.h"

// TObjCage::Propeler (the PS2 build's name and spelling). Kinds 1 and 3 carry
// a propeller: while the cage is carried (state 2, which also plays the
// propeller sound once the game is not paused) or flying (state 5) the spin
// speed eases up to its top speed, in states 6 to 8 it is left alone, and
// otherwise it eases down to a stop. The spin angle wraps at a full turn.

#include "src/rel/cage_class.inc"

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" const f32 cagePropTopSpeed[1];
extern "C" const f32 cagePropEase[1];
extern "C" const f32 cagePropFullTurn[1];

extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);
f32 AdjustFloat(f32 value, f32 target, f32 step);

void TObjCage::Propeler()
{
	if ((s8)lbl_8042C180[0x1F] == 0 && (kind == 1 || kind == 3)) {
		switch (state) {
			case 2:
				unk130 = cagePropTopSpeed[0];
				if ((s8)lbl_8042C180[0x1F] == 0 && lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x104C, &pos, this, 3, -0x14, 2);
				}
			case 5:
				unk130 = AdjustFloat(unk130, cagePropTopSpeed[0], cagePropEase[0]);
				unk12C += unk130;
				while (unk12C >= cagePropFullTurn[0]) {
					unk12C -= cagePropFullTurn[0];
				}
				break;
			case 6:
			case 7:
			case 8:
				break;
			default:
				unk130 = AdjustFloat(unk130, cageZero[0], cagePropEase[0]);
				unk12C += unk130;
				while (unk12C >= cagePropFullTurn[0]) {
					unk12C -= cagePropFullTurn[0];
				}
				break;
		}
	}
}
