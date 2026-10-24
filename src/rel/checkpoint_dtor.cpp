#include "types.h"

// TObjCheckpoint's destructor (the PS2 build's name; checkpointDtor here, as
// the family names its constructor checkpointCtor). Every player marked as
// having entered is let go (one held in state 0x26 is released by
// fn_80043DEC) and its mark cleared; the star is deleted (its destructor,
// rel/checkpoint_star.cpp, inlined); then the set-object base and the object
// base run down and the object is freed when the delete flag asks for it.

typedef struct RpClump RpClump;

extern "C" void fn_80150958(RpClump* clump);

class CheckpointStar
{
public:
	u8 unk00[0x30];
	RpClump* model;  // 0x30
	RpClump* effect; // 0x34

	~CheckpointStar()
	{
		if (model != NULL) {
			fn_80150958(model);
			model = NULL;
		}
		if (effect != NULL) {
			fn_80150958(effect);
			effect = NULL;
		}
	}
};

typedef struct CheckpointPlayer {
	u8 unk000[0x6F0];
	s16 state; // 0x6F0
	u8 unk6F2[0x6E];
	s8 no; // 0x760
} CheckpointPlayer;

typedef struct Checkpoint {
	u8 unk00[0x18];       // 0x00
	void** vtable;        // 0x18
	u8 unk1C[0xC];        // 0x1C
	void* frame;          // 0x28, the set object's
	void** setObjVtable;  // 0x2C
	u8 unk30[0x20];       // 0x30
	CheckpointStar* star; // 0x50
	u8 unk54[0x20];       // 0x54
	s8 entered[8];        // 0x74
} Checkpoint;

extern "C" void* lbl_8042C148;
extern "C" void* checkpointVtable[];
extern "C" CheckpointPlayer* lbl_802AD070[];

extern "C" void fn_80043DEC(CheckpointPlayer* player);
extern "C" void __dt__10TObjSetObjFv(void* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" Checkpoint* checkpointDtor(Checkpoint* object, s16 flags)
{
	if (object != NULL) {
		object->vtable       = checkpointVtable;
		object->setObjVtable = checkpointVtable + 0xB;
		for (int i = 0; i < 8; i++) {
			if (object->entered[i] != 0) {
				CheckpointPlayer* player = lbl_802AD070[i];

				if (player != NULL && player->state == 0x26) {
					fn_80043DEC(player);
				}
				object->entered[player->no] = 0;
			}
		}
		if (object->star != NULL) {
			delete object->star;
			object->star = NULL;
		}
		__dt__10TObjSetObjFv(&object->frame, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
