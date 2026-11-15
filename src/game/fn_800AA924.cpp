// Destructor of the class whose vtable is lbl_802531A0 (a TObject with a PARAM_SFA base at +0x29;
// the class name is UNKNOWN): clears the owner player's bit (its team number, +0x9BC of the player
// at +0x34) in the byte +0x1F of lbl_8042C180, resets the team-blast gauge of team +0x30 to 0
// (PARAM_SFA::setTB), runs the TObject destructor and frees the object when flags > 0. Returns the
// object.
#include "game/gparam.h"

struct Player800AA924 {
	u8 pad0[0x9BC];
	s8 team; // 0x9BC
};

struct Obj800AA924 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x29 - 0x1C];
	u8 sfa[1]; // 0x29 (PARAM_SFA base)
	u8 pad2A[0x30 - 0x2A];
	s8 team; // 0x30
	u8 pad31[0x34 - 0x31];
	Player800AA924* player; // 0x34
};

struct State800AA924 {
	u8 pad0[0x1F];
	s8 playerBits; // 0x1F
};

struct THeapCtrl;

extern "C" {
extern void* lbl_802531A0[];
extern State800AA924* lbl_8042C180;
extern f32 lbl_8042DB70; // 0.0f
extern THeapCtrl* lbl_8042C148;
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

static inline void ClearPlayerBit(s32 team)
{
	if (lbl_8042C180 != NULL) {
		lbl_8042C180->playerBits &= ~(1 << team);
	}
}

extern "C" {
Obj800AA924* fn_800AA924(Obj800AA924* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_802531A0;
		ClearPlayerBit(o->player->team);
		((PARAM_SFA*)o->sfa)->setTB(o->team, lbl_8042DB70);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
