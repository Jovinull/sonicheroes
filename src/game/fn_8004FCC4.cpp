#include "types.h"

// Debug pad controls of the team record manager `world` (HYPOTHESIS: a developer menu left in the
// retail build): lbl_8042C23C starts at 200 the first time. With play-mode flag 0 set and flag 5
// clear, while the debug block lbl_802B9080 is enabled (+0x4), each player whose pad
// (lbl_8029BBD0 by port lbl_802408F8) holds 0x200 and presses 0x800 outside play-mode flag 6
// steps its team record (lbl_8042C1FC selects the player) to the next entry of lbl_80239A30 with
// a non-zero +0x8 (27 entries, wrapping) and resets it (fn_8004E408, fn_8004DEC0, fn_8004DD60,
// fn_8004DD3C with the player's block lbl_802D5B48). Pad 0 holding 0x200 cycles the debug
// player (+0x0, 0..player count) with 0x100 and toggles +0x8 with 0x400; holding 0x8 and
// pressing 0x100 runs fn_8004DB3C.

// The 0x4C-byte pad records (see adv_2p.cpp). The pressed buttons are read at +0x50, past the
// record: the record base is probably not the table start (UNKNOWN).
struct Pad8004FCC4 {
	u8 pad0[0x48];
	u32 held; // 0x48
};

static inline u32 Pressed(Pad8004FCC4* pad)
{
	return *(u32*)((u8*)pad + 0x50);
}

struct Debug8004FCC4 {
	s32 player;  // 0x0
	s32 enabled; // 0x4
	s32 toggle;  // 0x8
};

struct Entry8004FCC4 {
	u8 pad0[0x8];
	s32 valid; // 0x8
};

struct PlayerBlock8004FCC4 {
	u8 unknown[0x9C];
};

struct PlayMode8004FCC4 {
	s8 flags[44];
};

extern "C" {
extern s8 lbl_8042C240;
extern s32 lbl_8042C23C;
extern PlayMode8004FCC4* lbl_8042C180;
extern Debug8004FCC4 lbl_802B9080;
extern s32 lbl_802408F8[];
extern Pad8004FCC4 lbl_8029BBD0[];
extern PlayerBlock8004FCC4 lbl_802D5B48[];
extern Entry8004FCC4 lbl_80239A30[0x1B];
extern s32 lbl_8042C1FC;
extern s32 lbl_8042C204;
s32 fn_8004E608(void* world);
s32 fn_8004E588(void* world, s32 kind);
void fn_8004E408(void* world, s32 kind, s32 entry);
void fn_8004DEC0(void* world, s32 kind, s32 value);
void fn_8004DD60(void* world, s32 kind, s32 value);
void fn_8004DD3C(void* world, s32 kind, PlayerBlock8004FCC4* block);
void fn_8004DB3C(void* world, s32 unknown);
}

// Steps *entry to the next valid entry of lbl_80239A30 (wrapping after 27) and returns it.
// HYPOTHESIS: the entry is volatile in the original too (retail keeps it in memory).
static inline s32 NextEntry(volatile s32* entry)
{
	s32 next;

	do {
		if (++*entry >= 0x1B) {
			*entry = 0;
		}
		next = *entry;
	} while (lbl_80239A30[next].valid == 0);
	return next;
}

extern "C" void fn_8004FCC4(void* world)
{
	s32 i;
	s32 kind;
	s32 saved;
	u32 debug;
	u32 held;

	if (lbl_8042C240 == 0) {
		lbl_8042C23C = 200;
		lbl_8042C240 = 1;
	}
	if (lbl_8042C180->flags[0] == 0 || lbl_8042C180->flags[5] != 0) {
		return;
	}
	if (lbl_802B9080.enabled != 0) {
		for (i = 0; i < lbl_8042C204; i++) {
			Pad8004FCC4* pad = &lbl_8029BBD0[lbl_802408F8[i]];
			if ((pad->held & 0x200) && (Pressed(pad) & 0x800) && lbl_8042C180->flags[6] == 0) {
				saved              = lbl_8042C1FC;
				lbl_8042C1FC       = i;
				kind               = fn_8004E608(world);
				volatile s32 entry = fn_8004E588(world, kind);
				fn_8004E408(world, kind, NextEntry(&entry));
				fn_8004DEC0(world, kind, 0);
				fn_8004DD60(world, kind, 0);
				fn_8004DD3C(world, kind, &lbl_802D5B48[i]);
				lbl_8042C1FC = saved;
			}
		}
	}
	held  = lbl_8029BBD0[lbl_802408F8[0]].held;
	debug = held & 0x200;
	if (debug && (Pressed(&lbl_8029BBD0[lbl_802408F8[0]]) & 0x100)) {
		lbl_802B9080.player++;
		lbl_802B9080.player %= lbl_8042C204 + 1;
	}
	if (debug && (Pressed(&lbl_8029BBD0[lbl_802408F8[0]]) & 0x400)) {
		lbl_802B9080.toggle = lbl_802B9080.toggle == 0;
	}
	if ((held & 8) && (Pressed(&lbl_8029BBD0[lbl_802408F8[0]]) & 0x100)) {
		fn_8004DB3C(world, 0);
	}
}
