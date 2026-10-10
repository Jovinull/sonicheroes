// TObjContUnbreakable::CheckBreak: the unbreakable crate goes through what hit
// its collision as kind 0xE and answers with the first hitter whose type says
// who broke it. Types 1 to 6 name characters 0 to 5 outright; types 7 to 10
// mean "a player", read from the first team slot, from 7's on, that holds a
// team: that team's leader. It returns -1 when nothing it knows hit it. The
// class is shared through unbreakable_container_class.inc.

#define UNBREAKABLE_CONTAINER_CTOR inline
#include "src/rel/unbreakable_container_class.inc"

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
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

s32 TObjContUnbreakable::CheckBreak()
{
	ContainerHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = containerHitter(fn_80020BD8(*this, 0xE))) != NULL) {
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
