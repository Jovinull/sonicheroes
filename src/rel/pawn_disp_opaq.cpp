#include "types.h"

// TObjEnemyPawn::DispOpaq (the PS2 build's name): draws the pawn when it is
// shown (and, on the split screen, not on the other player's view). Once per
// frame and pawn kind it first steps the kind's material effect animation and
// hands its effect data to each atomic of the body (and of the shield, for kinds
// 6 and 7); then it lights the pawn and renders its clump, body, shield and
// weapon. The pawnFx* names are ours.

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

typedef struct PawnSet {
	u8 unk00[0x18];
	u32 flags; // 0x18
} PawnSet;

typedef struct PawnFxData {
	u8 unk00[0x44];
} PawnFxData;

typedef struct Pawn {
	u8 unk000[0xB0];
	PawnSet* set; // 0xB0
	u8 unk0B4[0x34];
	RpClump* clump; // 0xE8
	u8 unk0EC[0x161];
	s8 kind; // 0x24D
	u8 unk24E[0x26];
	s32 weaponMotion; // 0x274
	u8 unk278[0x4];
	s32 weaponMotion2; // 0x27C
	u8 unk280[0x4];
	RpClump* weapon; // 0x284
	u8 unk288[0x64];
	s32 shown; // 0x2EC
	u8 unk2F0[0x78];
	RpClump* body;   // 0x368
	RpClump* shield; // 0x36C
} Pawn;

extern "C" u8* lbl_8042C180;
extern "C" CLIGHT lbl_802D5E80;
extern "C" s32 pawnFxReady;
extern "C" s32 pawnFxFrame[4];
extern "C" void* pawnFxAnim[4];
extern "C" PawnFxData pawnFxData[4];
extern "C" const f32 pawnAimReach[1];

RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);
extern "C" int fn_800A4584(Pawn* pawn);
extern "C" void fn_8011B844(void* anim, f32 step);
extern "C" RpClump* fn_8014FFBC(
    RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void DispOpaq__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->shown == 0) {
		return;
	}
	if (fn_800A4584(pawn) > 0 && (*(s32*)(lbl_8042C180 + 0x30) & 2) == 0) {
		return;
	}
	if (pawnFxReady != 0) {
		switch (pawn->kind) {
			case 0:
			case 1: {
				s32 frame = *(s32*)(lbl_8042C180 + 0x30);

				if (pawn->body != NULL && pawnFxFrame[0] != frame) {
					pawnFxFrame[0] = frame;
					fn_8011B844(pawnFxAnim[0], pawnAimReach[0]);
					fn_8014FFBC(pawn->body, SetAtomicCustomFXData, &pawnFxData[0]);
				}
				break;
			}
			case 4:
			case 5: {
				s32 frame = *(s32*)(lbl_8042C180 + 0x30);

				if (pawn->body != NULL && pawnFxFrame[1] != frame) {
					pawnFxFrame[1] = frame;
					fn_8011B844(pawnFxAnim[1], pawnAimReach[0]);
					fn_8014FFBC(pawn->body, SetAtomicCustomFXData, &pawnFxData[1]);
				}
				break;
			}
			case 6:
			case 7: {
				s32 frame = *(s32*)(lbl_8042C180 + 0x30);

				if (pawn->body != NULL && pawnFxFrame[2] != frame) {
					pawnFxFrame[2] = frame;
					fn_8011B844(pawnFxAnim[2], pawnAimReach[0]);
					fn_8014FFBC(pawn->body, SetAtomicCustomFXData, &pawnFxData[2]);
				}
				if (pawn->shield != NULL && pawnFxFrame[3] != frame) {
					pawnFxFrame[3] = frame;
					fn_8011B844(pawnFxAnim[3], pawnAimReach[0]);
					fn_8014FFBC(pawn->shield, SetAtomicCustomFXData, &pawnFxData[3]);
				}
				break;
			}
		}
	}
	lbl_802D5E80.SetCurrentNum(((pawn->set->flags & 0x1C0000) >> 18) + 8);
	lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
	if (pawn->clump != NULL) {
		fn_8014FF2C(pawn->clump);
	}
	if (pawn->body != NULL) {
		fn_8014FF2C(pawn->body);
	}
	if (pawn->shield != NULL) {
		fn_8014FF2C(pawn->shield);
	}
	if ((pawn->weaponMotion != -1 || pawn->weaponMotion2 != -1) && pawn->weapon != NULL) {
		fn_8014FF2C(pawn->weapon);
	}
}
