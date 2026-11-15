// Pushes a new record into the team's 10-entry history at +0x15C: the entries move up by one and
// entry 0 becomes the lbl_802B0310 record of the leader's character kind (kinds at +0x110, leader
// at +0x3A). Record and field roles are UNKNOWN.
#include "types.h"

struct Record80092650 {
	f32 unknown0; // 0x0
	s32 unknown4; // 0x4
	// Six separate bytes: the retail copy moves them one by one, as members (an array is copied
	// in words).
	u8 unknown8; // 0x8
	u8 unknown9; // 0x9
	u8 unknownA; // 0xA
	u8 unknownB; // 0xB
	u8 unknownC; // 0xC
	u8 unknownD; // 0xD
};

struct Team80092650 {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 kinds[3]; // 0x110
	u8 pad113[0x15C - 0x113];
	Record80092650 history[10]; // 0x15C
};

extern "C" {
extern Record80092650 lbl_802B0310[];

void fn_80092650(Team80092650* team)
{
	Record80092650* source = &lbl_802B0310[team->kinds[team->leader]];
	int i;

	for (i = 9; i > 0; i--) {
		team->history[i] = team->history[i - 1];
	}
	team->history[0] = *source;
}
}
