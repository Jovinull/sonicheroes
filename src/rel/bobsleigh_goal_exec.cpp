#include "types.h"

// TObjBobsleighGoal::Exec (the PS2 build's name), the same in the twelve stage
// modules that carry the bobsleigh: once the goal is done it asks to be
// killed; otherwise, while the game is running (the mode byte at 0x22 clear,
// the bobsleigh state not 1 to 5) and its owner lives, it keeps the
// collision's last position, moves it to the goal and enters it, and clears it
// at any other time. The destructor is rel/bobsleigh_goal_dtor.cpp.

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct sAngle {
	s32 x;
	s32 y;
	s32 z;
} sAngle;

typedef struct BobsleighWorld {
	u8 unk0000[0x725C];
	void* world; // 0x725C
} BobsleighWorld;

typedef struct BobsleighGoal {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
	u8 colli[0x60]; // 0x28, C_COLLI
	RwV3d pos;      // 0x88, the collision's
	sAngle ang;     // 0x94
	u8 unkA0[0x4];
	RwV3d prePos;       // 0xA4
	s32 count;          // 0xB0
	RwV3d goalPos;      // 0xB4
	sAngle goalAng;     // 0xC0
	s32 done;           // 0xCC
	RpClump* clumps[1]; // 0xD0
} BobsleighGoal;

typedef struct BobsleighOwner {
	u8 unk0[0x4];
	u16 signal; // 0x04
} BobsleighOwner;

typedef struct BobsleighMode {
	u8 unk00[0x18];
	s32 mode; // 0x18
} BobsleighMode;

typedef struct BobsleighGoalHead {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0xA];
	BobsleighOwner* owner; // 0x10
} BobsleighGoalHead;

extern "C" void* lbl_8042C148;
extern "C" BobsleighWorld* lbl_8042C1D0;
extern "C" void* __vt__17TObjBobsleighGoal[];
extern "C" u8* lbl_8042C180;
extern "C" BobsleighMode lbl_8029C310;

extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void ClearInfo__7C_COLLIFv(void* colli);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" void Exec__17TObjBobsleighGoalFv(BobsleighGoal* object)
{
	BobsleighGoalHead* head = (BobsleighGoalHead*)object;

	if (object->done != 0) {
		head->signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x22] == 0 && lbl_8029C310.mode != 1 && lbl_8029C310.mode != 2
	    && lbl_8029C310.mode != 3 && lbl_8029C310.mode != 4 && lbl_8029C310.mode != 5
	    && !(head->owner->signal & 1)) {
		object->prePos = object->pos;
		object->pos    = object->goalPos;
		object->ang    = object->goalAng;
		Entry__7C_COLLIFv(object->colli);
	} else {
		ClearInfo__7C_COLLIFv(object->colli);
	}
}
