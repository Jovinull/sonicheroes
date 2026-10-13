#include "types.h"

// TObjEnemyPawn::PlaySEForFoot (the PS2 build's name): in the walk (3) and run
// (4) motions, plays the footstep sound 0x4009 once as the frame passes each of
// the motion's two steps, and rearms when the motion loops.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0xB8];
	f32 frame; // 0xB8
	u8 unk0BC[0xC];
	u32 motionFlags; // 0xC8
	u8 unk0CC[0x4];
	s32 motion; // 0xD0
	u8 unk0D4[0x6C];
	RwV3d pos; // 0x140
	u8 unk14C[0x1B4];
	s32 step; // 0x300
} Pawn;

extern "C" void* lbl_8042C388;
extern "C" const f32 pawnStirSpeed[1];
extern "C" const f32 pawnWalkStep2[1];
extern "C" const f32 pawnRunStep1[1];
extern "C" const f32 pawnRunStep2[1];

extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);

extern "C" void PlaySEForFoot__13TObjEnemyPawnFv(Pawn* pawn)
{
	f32 frame = pawn->frame;

	switch (pawn->motion) {
		case 3:
			if (frame > pawnStirSpeed[0] && pawn->step == 0) {
				pawn->step = 1;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4009, &pawn->pos, NULL, 1, 0, 0);
				}
			}
			if (frame > pawnWalkStep2[0] && pawn->step == 1) {
				pawn->step = 2;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4009, &pawn->pos, NULL, 1, 0, 0);
				}
			}
			if (pawn->step != 0 && (pawn->motionFlags & 2)) {
				pawn->step = 0;
			}
			break;
		case 4:
			if (frame > pawnRunStep1[0] && pawn->step == 0) {
				pawn->step = 1;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4009, &pawn->pos, NULL, 1, 0, 0);
				}
			}
			if (frame > pawnRunStep2[0] && pawn->step == 1) {
				pawn->step = 2;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x4009, &pawn->pos, NULL, 1, 0, 0);
				}
			}
			if (pawn->step != 0 && (pawn->motionFlags & 2)) {
				pawn->step = 0;
			}
			break;
	}
}
