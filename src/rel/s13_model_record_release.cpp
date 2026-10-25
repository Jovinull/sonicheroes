#include "types.h"

// fn_9_76448, which the stage 13 and 14 families' Unload hooks run over their
// model records: the record's model is released as s13ModelInfoRelease
// releases an info's (the same flags undo the same set-ups), then its animation
// by its kind (a delta morph, a hierarchical animation, or a UV animation with
// its buffer freed) and forgotten.

struct RpClump;

// the flags of a model info
typedef struct S13ModelFlags {
	u16 bits; // 0x00
} S13ModelFlags;

// one of the stage's larger model records
typedef struct S13ModelRecord {
	S13ModelFlags flags; // 0x00
	u8 unk02[0x6];
	S13ModelFlags stage15Flags; // 0x08
	u8 unk0A[0x6];
	RpClump* model; // 0x10
	s8 animKind;    // 0x14
	u8 unk15[0x3];
	void* anim; // 0x18
	u8 unk1C[0x4];
	void* animBuffer; // 0x20
	u8 unk24[0x8];
} S13ModelRecord; // 0x2C

// the shared material animation (s13ModelInfoLoad makes it)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

// the game state: only the stage is read here
typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" MatAnim* s13ModelInfoMatAnim;
extern "C" void* s13ModelInfoMatAnimData;
extern "C" u8* lbl_8042C9A4;

extern "C" void fn_800B8ADC(RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8013BD74(void* anim);
extern "C" void fn_8020C2D8(void* anim);
extern "C" void fn_8011B7CC(void* anim);

extern "C" void fn_9_76448(S13ModelRecord* record)
{
	s32 stage            = lbl_8029C310.stage;
	S13ModelFlags* flags = &record->flags;

	if ((record->flags.bits & 0x200) && stage == 15) {
		flags = &record->stage15Flags;
	}
	if (record->model != NULL) {
		if (flags->bits & 0x1) {
			fn_800B8ADC(record->model);
		}
		if (flags->bits & 0x4) {
			fn_800B8ADC(record->model);
		}
		if (flags->bits & 0x400) {
			if (s13ModelInfoMatAnim != NULL) {
				delete s13ModelInfoMatAnim;
				s13ModelInfoMatAnim = NULL;
			}
			if (s13ModelInfoMatAnimData != NULL) {
				delete (u8*)s13ModelInfoMatAnimData;
				s13ModelInfoMatAnimData = NULL;
			}
		}
		fn_80150958(record->model);
		record->model = NULL;
	}
	if (record->anim != NULL) {
		switch (record->animKind) {
			case 2:
				fn_8020C2D8(record->anim);
				break;
			case 1:
				fn_8013BD74(record->anim);
				break;
			case 3:
				fn_8011B7CC(record->anim);
				if (record->animBuffer != NULL) {
					(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(record->animBuffer);
					record->animBuffer = NULL;
				}
				break;
		}
		record->anim = NULL;
	}
}
