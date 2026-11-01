// TObjWarp::checkCollision (the PS2 build's name), the copy out of line that
// nothing calls (Exec in rel/warp_exec.cpp has the same walk written in), kept
// with force_active: for each object the warp's collision block touches whose
// character is the current player's team leader, the destination in the
// placement's parameters (+4) goes to fn_8004D2C4. The class is shared through
// warp_class.inc.

#define WARP_CTOR inline
#define WARP_EDIT_FIRST
#include "src/rel/warp_class.inc"

extern "C" u8 lbl_8042C1A4[];
extern "C" s32 lbl_8042C1FC;
extern "C" u8* lbl_80303DC8[];
extern "C" void* lbl_8042C1F8;
extern "C" void fn_80021824(void* list);
extern "C" CCL_HIT_INFO* fn_800211A8(C_COLLI* colli);
extern "C" s32 fn_80041B64(CHARACTER_ID character);
extern "C" void fn_8004D2C4(void* target, void* destination);

inline C_COLLI* NextHit(C_COLLI& colli)
{
	CCL_HIT_INFO* hit = fn_800211A8(&colli);
	return hit != NULL ? hit->hit_ccl : NULL;
}

void TObjWarp::checkCollision()
{
	fn_80021824(lbl_8042C1A4);
	C_COLLI* hit;
	while ((hit = NextHit(*this)) != NULL) {
		u8* player = lbl_80303DC8[lbl_8042C1FC];
		s32 team   = fn_80041B64(hit->character_id);
		if (team == (s8)player[0x110 + (s8)player[0x3A]]) {
			fn_8004D2C4(lbl_8042C1F8, (u8*)ObjParam->setData.setBuffer + 4);
		}
	}
}
