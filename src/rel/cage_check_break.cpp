#include "types.h"

// TObjCage::CheckBreak (the PS2 build's name; cageCheckBreak here): the cage
// goes through what hit its collision as kinds 0xC, 0xE and 0x10, in that
// order, and answers with the first hitter whose type says who broke it. The
// body is rel/iron_container_check_break.cpp's (TObjContIron::CheckBreak), with
// the collision at 0x30 of the cage; see there for the conditional helper.

typedef struct CageHitter {
	u8 pad000[0x78];
	u32 type; // 0x78
} CageHitter;

typedef struct CageHit {
	u8 pad00[0x4];
	CageHitter* hitter; // 0x04
} CageHit;

typedef struct CageTeam {
	u8 pad000[0x3B];
	s8 leader; // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
} CageTeam;

typedef struct Cage {
	u8 base[0x30];  // 0x00
	u8 colli[0x10]; // 0x30
} Cage;

extern "C" u8 lbl_8042C1A4[];
extern "C" CageTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* world);
extern "C" CageHit* fn_80020BD8(void* colli, s32 kind);

static inline CageHitter* cageHitter(CageHit* hit)
{
	return hit != NULL ? hit->hitter : NULL;
}

extern "C" s32 cageCheckBreak(Cage* object)
{
	CageHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = cageHitter(fn_80020BD8(object->colli, 0xC))) != NULL
	    || (hitter = cageHitter(fn_80020BD8(object->colli, 0xE))) != NULL
	    || (hitter = cageHitter(fn_80020BD8(object->colli, 0x10))) != NULL) {
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
				if (lbl_80303DC8[0] != NULL) {
					return lbl_80303DC8[0]->members[lbl_80303DC8[0]->leader];
				}
			case 8:
				if (lbl_80303DC8[1] != NULL) {
					return lbl_80303DC8[1]->members[lbl_80303DC8[1]->leader];
				}
			case 9:
				if (lbl_80303DC8[2] != NULL) {
					return lbl_80303DC8[2]->members[lbl_80303DC8[2]->leader];
				}
			case 10:
				if (lbl_80303DC8[3] != NULL) {
					return lbl_80303DC8[3]->members[lbl_80303DC8[3]->leader];
				}
		}
	}
	return -1;
}
