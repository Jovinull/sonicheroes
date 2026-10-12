// TObjContIron::CheckBreak: the iron crate goes through what hit its collision
// as kinds 0xC, 0xE and 0x10, in that order, and answers with the first hitter
// whose type says who broke it, the way
// rel/unbreakable_container_check_break.cpp does with kind 0xE alone. With
// three calls in the condition the helper has to be a conditional expression:
// written as two returns, the hitter does not go through r0 as it does in the
// original. The class is shared through iron_container_class.inc.

#define IRON_CONTAINER_CTOR inline
#include "src/rel/iron_container_class.inc"

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

extern "C" u8 lbl_8042C1A4[];
extern "C" ContainerTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* world);
extern "C" ContainerHit* fn_80020BD8(C_COLLI& colli, s32 kind);

static inline ContainerHitter* containerHitter(ContainerHit* hit)
{
	return hit != NULL ? hit->hitter : NULL;
}

s32 TObjContIron::CheckBreak()
{
	ContainerHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = containerHitter(fn_80020BD8(*this, 0xC))) != NULL
	    || (hitter = containerHitter(fn_80020BD8(*this, 0xE))) != NULL
	    || (hitter = containerHitter(fn_80020BD8(*this, 0x10))) != NULL) {
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
