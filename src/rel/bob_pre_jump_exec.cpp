// TObjBobPreJumpCollision::Exec: every player whose character went into the
// pre-jump box gets fn_80089204 (the player is found from the hitter's type),
// then the box keeps its last position and follows the jump it belongs to
// before entering its collision again. The class is in
// game/obj_bob_jump_collision.h.

#define BOB_PRE_JUMP_DTOR_FIRST
#include "game/obj_bob_jump_collision.h"

struct PreJumpHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
};

struct PreJumpHit {
	u8 pad00[0x4];
	PreJumpHitter* hitter; // 0x04
};

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_802AD070[6];
extern "C" void fn_80021824(void* world);
extern "C" PreJumpHit* fn_800211A8(C_COLLI& colli);
extern "C" s32 fn_80041B64(s32 type);
extern "C" void fn_80089204(void* player);

static inline PreJumpHitter* preJumpHitter(PreJumpHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

void TObjBobPreJumpCollision::Exec()
{
	PreJumpHitter* hitter;
	TObjBobJumpCollision* jump;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = preJumpHitter(fn_800211A8(*this))) != NULL) {
		fn_80089204(lbl_802AD070[fn_80041B64(hitter->type)]);
	}
	jump    = owner;
	pre_pos = pos;
	pos     = jump->pos;
	ang     = jump->ang;
	Entry();
}
