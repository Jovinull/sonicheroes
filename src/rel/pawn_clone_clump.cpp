#include "types.h"

// TObjEnemyPawn::CloneClump (the PS2 build's name, by its member order):
// destroys the pawn's weapon, shield, body and base models, then clones them
// again from the module's model table by pawn kind (the material-effect bodies
// and shields only when the effects are loaded) and the weapon by gait, and
// finds the weapon's hierarchy, its muzzle bone (3000) and its muzzle and
// second frames (3000, 3500) when not set yet. pawnModels is our name.

typedef struct RwFrame RwFrame;
typedef struct RpHAnimHierarchy RpHAnimHierarchy;

typedef struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

class HAnimClass
{
public:
	RpHAnimHierarchy* GetHierarchy(RpClump* clump);
};

namespace nRenderWare
{
RwFrame* SearchFrameFromFrameID(RwFrame* parent, int id);
}

typedef struct Pawn {
	u8 unk000[0xE8];
	RpClump* clump; // 0xE8
	u8 unk0EC[0x154];
	HAnimClass hanim; // 0x240
	u8 unk241[0xC];
	s8 kind; // 0x24D
	s8 gait; // 0x24E
	u8 unk24F[0x35];
	RpClump* weapon;             // 0x284
	RpHAnimHierarchy* hierarchy; // 0x288
	RwFrame* muzzleBone;         // 0x28C
	u8 unk290[0x7C];
	RwFrame* muzzle; // 0x30C
	RwFrame* second; // 0x310
	u8 unk314[0x54];
	RpClump* body;   // 0x368
	RpClump* shield; // 0x36C
} Pawn;

extern "C" s32 pawnFxReady;
extern "C" RpClump* pawnModels[11];

extern "C" RpClump* fn_80150588(RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);
RwFrame* objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, int id);

extern "C" void CloneClump__13TObjEnemyPawnFv(Pawn* pawn)
{
	RpClump* clump;

	if (pawn->weapon != NULL) {
		fn_80150958(pawn->weapon);
		pawn->weapon = NULL;
	}
	if (pawn->shield != NULL) {
		fn_80150958(pawn->shield);
		pawn->shield = NULL;
	}
	if (pawn->body != NULL) {
		fn_80150958(pawn->body);
		pawn->body = NULL;
	}
	if (pawn->clump != NULL) {
		fn_80150958(pawn->clump);
		pawn->clump = NULL;
	}
	if (pawnFxReady != 0) {
		switch (pawn->kind) {
			case 2:
			case 3:
				clump = fn_80150588(pawnModels[1]);
				break;
			case 0:
			case 1:
				clump = fn_80150588(pawnModels[0]);
				break;
			case 4:
			case 5:
				clump = fn_80150588(pawnModels[5]);
				break;
			case 6:
			case 7:
				clump = fn_80150588(pawnModels[6]);
				break;
		}
	} else {
		switch (pawn->kind) {
			case 2:
			case 3:
				clump = fn_80150588(pawnModels[1]);
				break;
			case 0:
			case 1:
				clump = fn_80150588(pawnModels[0]);
				break;
			case 4:
			case 5:
				clump = fn_80150588(pawnModels[0]);
				break;
			case 6:
			case 7:
				clump = fn_80150588(pawnModels[0]);
				break;
		}
	}
	pawn->clump = clump;
	if (pawnFxReady != 0) {
		switch (pawn->kind) {
			case 0:
			case 1:
				pawn->body = fn_80150588(pawnModels[7]);
				break;
			case 4:
			case 5:
				pawn->body = fn_80150588(pawnModels[8]);
				break;
			case 6:
			case 7:
				pawn->body   = fn_80150588(pawnModels[9]);
				pawn->shield = fn_80150588(pawnModels[10]);
				break;
		}
	}
	switch (pawn->gait) {
		case 1:
			pawn->weapon = fn_80150588(pawnModels[2]);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
			pawn->weapon = fn_80150588(pawnModels[3]);
			break;
		case 2:
			pawn->weapon = fn_80150588(pawnModels[4]);
			break;
	}
	if (pawn->weapon != NULL) {
		pawn->hierarchy = pawn->hanim.GetHierarchy(pawn->weapon);
		if (pawn->hierarchy != NULL) {
			pawn->muzzleBone = objRpHAnimHierarchyFindFrameFromBoneID(pawn->hierarchy, 3000);
		}
		if (pawn->muzzle == NULL) {
			pawn->muzzle = nRenderWare::SearchFrameFromFrameID(pawn->weapon->frame, 3000);
		}
		if (pawn->second == NULL) {
			pawn->second = nRenderWare::SearchFrameFromFrameID(pawn->weapon->frame, 3500);
		}
	}
}
