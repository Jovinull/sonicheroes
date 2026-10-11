// TObjKey::CheckPlayer (the PS2 build's name): unless something of kind 0x13
// or 1 hits the key's collision, it goes through the players touching it and
// answers 1 for the first one that is its team's leader or partner, else 0.
// It is TObjChao::CheckTouchedByLeader's walk (rel/chao_check_touched.cpp),
// with the character kept across the hits and the player tested before its
// team is read. The class is in key_object_class.inc.

#define KEY_OBJECT_CTOR inline
#include "src/rel/key_object_class.inc"

struct KeyHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
};

struct KeyHit {
	u8 pad00[0x4];
	KeyHitter* hitter; // 0x04
};

struct KeyPlayer {
	u8 pad000[0x25C];
	s8 team; // 0x25C
};

struct KeyTeam {
	u8 pad000[0x3A];
	s8 partner; // 0x3A
	s8 leader;  // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
};

extern "C" u8 lbl_8042C1A4[];
extern "C" KeyPlayer* lbl_802AD0D0[];
extern "C" KeyTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* world);
extern "C" KeyHit* fn_80020BD8(C_COLLI& colli, s32 kind);
extern "C" KeyHit* fn_800211A8(C_COLLI& colli);

static inline KeyHitter* keyHitter(KeyHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

s32 TObjKey::CheckPlayer()
{
	s32 character = -1;
	KeyHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	if (keyHitter(fn_80020BD8(*this, 0x13)) != NULL) {
		return 0;
	}
	fn_80021824(lbl_8042C1A4);
	if (keyHitter(fn_80020BD8(*this, 1)) != NULL) {
		return 0;
	}
	fn_80021824(&static_cast<C_COLLI&>(*this));
	while ((hitter = keyHitter(fn_800211A8(*this))) != NULL) {
		switch (hitter->type) {
			case 1:
				character = 0;
				break;
			case 2:
				character = 1;
				break;
			case 3:
				character = 2;
				break;
			case 4:
				character = 3;
				break;
			case 5:
				character = 4;
				break;
			case 6:
				character = 5;
				break;
		}
		if (character != -1) {
			KeyPlayer* player = lbl_802AD0D0[character];
			if (player != NULL) {
				KeyTeam* info = lbl_80303DC8[player->team];
				if (character == info->members[info->leader]
				    || character == info->members[info->partner]) {
					return 1;
				}
			}
		}
	}
	return 0;
}
