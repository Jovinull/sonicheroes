// TObjBobJumpCollision::Exec: the jump ends itself when it is out of range or
// must be killed. Otherwise every player whose character went into the box gets
// fn_80089204, and when that says the player jumped, the word at 0x30 of the
// table at lbl_8029BBD0 for that player's team slot is set; then the box keeps
// its last position, takes its own placement again and enters its collision.
// The class is in game/obj_bob_jump_collision.h.

#define BOB_JUMP_DTOR_FIRST
#include "game/obj_bob_jump_collision.h"

struct BobJumpHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
};

struct BobJumpHit {
	u8 pad00[0x4];
	BobJumpHitter* hitter; // 0x04
};

struct BobJumpPlayer {
	u8 pad000[0x9BC];
	s8 team; // 0x9BC
};

struct BobJumpTeam {
	u8 pad000[0x14C];
	s8 slot; // 0x14C
};

struct BobJumpTable {
	u8 pad00[0x30];
	s32 jumped[4]; // 0x30
};

extern "C" u8 lbl_8042C1A4[];
extern "C" BobJumpPlayer* lbl_802AD070[6];
extern "C" BobJumpTeam* lbl_80303DC8[];
extern "C" BobJumpTable lbl_8029BBD0;
extern "C" void fn_80021824(void* world);
extern "C" BobJumpHit* fn_800211A8(C_COLLI& colli);
extern "C" s32 fn_80041B64(s32 type);
extern "C" s32 fn_80089204(BobJumpPlayer* player);

static inline BobJumpHitter* bobJumpHitter(BobJumpHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

void TObjBobJumpCollision::Exec()
{
	BobJumpHitter* hitter;
	s32 no;

	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
		return;
	}
	fn_80021824(lbl_8042C1A4);
	while ((hitter = bobJumpHitter(fn_800211A8(*this))) != NULL) {
		no = fn_80041B64(hitter->type);
		if (fn_80089204(lbl_802AD070[no]) != 0) {
			lbl_8029BBD0.jumped[lbl_80303DC8[lbl_802AD070[no]->team]->slot] = 1;
		}
	}
	pre_pos      = C_COLLI::pos;
	C_COLLI::pos = pos;
	C_COLLI::ang = ang;
	Entry();
}
