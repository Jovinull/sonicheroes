#include "types.h"

// Stops a player's HUD animations (HYPOTHESIS: the life/item display of player +0x28): after
// fn_800C343C, while the HUD is active (lbl_8042C710), the player's main animation id
// (lbl_8042B3F0) leaves the 64-entry id table lbl_803042C8 (see fn_800C0B04); a running extra
// animation (lbl_803043E8, state +0x3C at 1) is stopped and its id (lbl_8042B3F8) removed too.
// Flag 1 of +0x74 is cleared, and each of the flags 0x2..0x8 and 0x10..0x40 that is set removes
// the matching id of lbl_80253DB8 or lbl_80253DD0 (three per player) and is cleared.
// NonMatching (one instruction shorter, registers): for the stop retail reads the extra
// animation's entry again and also rescales the player index (slwi); MWCC reuses the scaled
// index (r4/r5 then differ). A volatile table brings back the reload; inlines taking the index,
// signed flags and opt_common_subs off did not bring back the rescale.

struct Hud800C2EB4 {
	u8 pad0[0x28];
	s8 player; // 0x28
	u8 pad29[0x74 - 0x29];
	s32 flags; // 0x74
};

struct Anim800C2EB4 {
	u8 pad0[0x3C];
	s32 state; // 0x3C
};

extern "C" {
extern s32 lbl_8042C710;
extern void* lbl_8042B3F0[2];
extern void* lbl_8042B3F8[2];
// Declared volatile here: the retail code reads the entry again for the stop (whether the
// original is volatile is UNKNOWN).
extern Anim800C2EB4* volatile lbl_803043E8[];
extern void* lbl_80253DB8[][3];
extern void* lbl_80253DD0[][3];
extern void* lbl_803042C8[0x40];
void fn_800C343C(Hud800C2EB4* hud);
}

// Clears `id` from the id table (the first matching entry; as in fn_800C0B04).
static inline void Unregister(void* id)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		void* entry = lbl_803042C8[i];

		if (entry == id) {
			lbl_803042C8[i] = NULL;
			break;
		}
	}
}

static inline s32 State(Anim800C2EB4* anim)
{
	return anim == NULL ? 0 : anim->state;
}

static inline void Stop(s32 player)
{
	Anim800C2EB4* anim = lbl_803043E8[player];

	if (anim != NULL && anim->state == 1) {
		anim->state = 0;
		Unregister(lbl_8042B3F8[player]);
	}
}

extern "C" void fn_800C2EB4(Hud800C2EB4* hud)
{
	s32 i;
	s32 bit;

	fn_800C343C(hud);
	if (lbl_8042C710 == 0) {
		return;
	}
	Unregister(lbl_8042B3F0[hud->player]);
	s32 player = hud->player;
	if (State(lbl_803043E8[player]) != 0) {
		Stop(player);
	}
	hud->flags &= ~1;
	for (i = 0, bit = 2; i < 3; i++, bit <<= 1) {
		if (hud->flags & bit) {
			Unregister(lbl_80253DB8[hud->player][i]);
			hud->flags &= ~bit;
		}
	}
	for (i = 0, bit = 0x10; i < 3; i++, bit <<= 1) {
		if (hud->flags & bit) {
			Unregister(lbl_80253DD0[hud->player][i]);
			hud->flags &= ~bit;
		}
	}
}
