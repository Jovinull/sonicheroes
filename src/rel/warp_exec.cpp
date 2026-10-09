// TObjWarp's TDisp (empty) and Exec. Out of range or due to be killed, the
// warp raises its kill bit; otherwise it walks the objects its collision block
// touches (fn_800211A8 gives each hit, whose object is hit_ccl) and, for one
// whose character belongs to the current player's team (fn_80041B64, compared
// with the team the player data at lbl_80303DC8 lists for its leader), hands
// the destination in the placement's parameters (+4) to fn_8004D2C4. Then it
// keeps the collision's last position, moves it to the placement and enters
// it (C_COLLI::Entry). The collision base goes to the hit walk by reference,
// which avoids the null test a pointer conversion adds, and the team number is
// a local, which orders the compare as the original does. The class is shared
// through warp_class.inc.

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

void TObjWarp::TDisp() { }

void TObjWarp::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
		return;
	}

	fn_80021824(lbl_8042C1A4);
	C_COLLI* hit;
	while ((hit = NextHit(*this)) != NULL) {
		u8* player = lbl_80303DC8[lbl_8042C1FC];
		s32 team   = fn_80041B64(hit->character_id);
		if (team == (s8)player[0x110 + (s8)player[0x3A]]) {
			fn_8004D2C4(lbl_8042C1F8, (u8*)ObjParam->setData.setBuffer + 4);
		}
	}
	SETDATA_PARAM* data = &ObjParam->setData;
	C_COLLI::pre_pos    = C_COLLI::pos;
	C_COLLI::pos        = data->pos;
	C_COLLI::ang        = data->ang;
	Entry();
}
