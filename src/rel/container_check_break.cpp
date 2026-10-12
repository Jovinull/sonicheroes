// TObjContainer::CheckBreak, the crate's own (the wood crate keeps it; the iron
// and unbreakable ones override it). It goes through two of its collision's hit
// lists, fn_800211A8's and then fn_800210C4's, while the collision's flag 0x20
// is set, and answers with the first hitter whose type says who broke it: types
// 1 to 6 name characters 0 to 5, types 7 to 10 the leader of the first team
// slot, from 7's on, that holds a team. It returns -1 when nothing it knows hit
// it. The type test is one inline function, so each list gets its own switch
// and jump table. The class is in game/obj_container.h.

#include "game/obj_container.h"

struct ContainerHitter {
	u8 pad000[0x78];
	u32 type; // 0x78
};

struct ContainerHit {
	u8 pad00[0x4];
	ContainerHitter* hitter; // 0x04
};

struct ContainerTeam {
	u8 pad000[0x3B];
	s8 leader; // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
};

extern "C" ContainerTeam* lbl_80303DC8[];
extern "C" void fn_80021824(C_COLLI& colli);
extern "C" ContainerHit* fn_800211A8(C_COLLI& colli);
extern "C" ContainerHit* fn_800210C4(C_COLLI& colli);

static inline ContainerHitter* containerHitter(ContainerHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

static inline s32 containerBreaker(ContainerHitter* hitter)
{
	ContainerTeam* team;

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
	return -1;
}

s32 TObjContainer::CheckBreak()
{
	ContainerHitter* hitter;
	s32 breaker;

	fn_80021824(*this);
	while ((hitter = containerHitter(fn_800211A8(*this))) != NULL) {
		if (C_COLLI::flag & 0x20) {
			breaker = containerBreaker(hitter);
			if (breaker != -1) {
				return breaker;
			}
		}
	}
	while ((hitter = containerHitter(fn_800210C4(*this))) != NULL) {
		if (C_COLLI::flag & 0x20) {
			breaker = containerBreaker(hitter);
			if (breaker != -1) {
				return breaker;
			}
		}
	}
	return -1;
}
