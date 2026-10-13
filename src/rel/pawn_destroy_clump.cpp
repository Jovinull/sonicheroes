#include "types.h"

// TObjEnemyPawn::DestroyClump (the PS2 build's name, by its member order):
// frees the pawn's four models (weapon, two extras and the body).

typedef struct RpClump RpClump;

typedef struct Pawn {
	u8 unk000[0xE8];
	RpClump* body; // 0x0E8
	u8 unk0EC[0x198];
	RpClump* weapon; // 0x284
	u8 unk288[0xE0];
	RpClump* extraB; // 0x368
	RpClump* extraA; // 0x36C
} Pawn;

extern "C" void fn_80150958(RpClump* clump);

extern "C" void DestroyClump__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->weapon != NULL) {
		fn_80150958(pawn->weapon);
		pawn->weapon = NULL;
	}
	if (pawn->extraA != NULL) {
		fn_80150958(pawn->extraA);
		pawn->extraA = NULL;
	}
	if (pawn->extraB != NULL) {
		fn_80150958(pawn->extraB);
		pawn->extraB = NULL;
	}
	if (pawn->body != NULL) {
		fn_80150958(pawn->body);
		pawn->body = NULL;
	}
}
