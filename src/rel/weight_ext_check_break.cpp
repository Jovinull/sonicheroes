#include "types.h"

// TObjWeightExtSub::CheckBreak (the PS2 build's name; weightExtCheckBreak
// here): the first hitter on the piece's collision, while the collision's flag
// 0x20 is set, whose type says who broke it: types 1 to 6 name characters 0 to
// 5, types 7 to 10 the leader of the first team slot, from 7's on, that holds
// a team (as the crate's CheckBreak). It returns -1 when nothing it knows hit
// it.

typedef struct WeightExtHitter {
	u8 unk00[0x78]; // 0x00
	u32 type;       // 0x78
} WeightExtHitter;

typedef struct WeightExtHit {
	u8 unk00[0x4];           // 0x00
	WeightExtHitter* hitter; // 0x04
} WeightExtHit;

typedef struct WeightExtTeam {
	u8 unk000[0x3B]; // 0x000
	s8 leader;       // 0x03B
	u8 unk03C[0xD4]; // 0x03C
	s8 members[1];   // 0x110
} WeightExtTeam;

typedef struct WeightExt {
	u8 unk00[0x28]; // 0x00
	u8 colli[0x8];  // 0x28 (C_COLLI)
	u16 colliFlag;  // 0x30
} WeightExt;

extern "C" WeightExtTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* colli);
extern "C" WeightExtHit* fn_800211A8(void* colli);

static inline WeightExtHitter* weightExtHitter(WeightExtHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" s32 weightExtCheckBreak(WeightExt* object)
{
	WeightExtHitter* hitter;
	WeightExtTeam* team;

	fn_80021824(object->colli);
	while ((hitter = weightExtHitter(fn_800211A8(object->colli))) != NULL) {
		if (object->colliFlag & 0x20) {
			switch (hitter->type) {
				case 1:
					return 0;
				case 2:
					return 1;
				case 3:
					return 2;
				case 4:
					return 3;
				case 5:
					return 4;
				case 6:
					return 5;
				case 7:
					if ((team = lbl_80303DC8[0]) != NULL) {
						return team->members[team->leader];
					}
				case 8:
					if ((team = lbl_80303DC8[1]) != NULL) {
						return team->members[team->leader];
					}
				case 9:
					if ((team = lbl_80303DC8[2]) != NULL) {
						return team->members[team->leader];
					}
				case 10:
					if ((team = lbl_80303DC8[3]) != NULL) {
						return team->members[team->leader];
					}
			}
		}
	}
	return -1;
}
