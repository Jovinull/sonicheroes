#include "game/rw_types.h"

// Resets a player's motion state: clears the counters, flags and targets (+0x5DC..+0x6AC, the
// three bytes +0x9E4/+0x9E6/+0x9E8), the target id (+0x5FC = -1), the action state (+0x6F0 mode,
// +0x6F2, timer +0x6F8, action flags 0x2D00 cleared), the motion vectors (+0x720, +0x72C, the
// speed +0x7C0 and its neighbours) and angles, sets the scale (+0x714) and +0x79C/+0x7A0 to
// lbl_8042D0E8, then runs fn_8003FDD4. The field names are HYPOTHESIS (see fn_800892C4,
// fn_8008A2D4 and fn_8008A3C4 for the target fields).

struct Player8003FC44 {
	u8 pad0[0x5DC - 0x0];
	s32 unknown5DC;  // 0x5DC
	s32 unknown5E0;  // 0x5E0
	RwV3d vector5E4; // 0x5E4
	RwV3d target;    // 0x5F0
	s32 targetId;    // 0x5FC
	f32 unknown600;  // 0x600
	f32 range;       // 0x604
	f32 distanceXZ;  // 0x608
	f32 distance;    // 0x60C
	RwV3d offset;    // 0x610
	RwV3d vector61C; // 0x61C
	u8 pad628[0x634 - 0x628];
	u8 bytes634[4]; // 0x634
	u8 pad638[0x678 - 0x638];
	s32 unknown678; // 0x678
	s32 unknown67C; // 0x67C
	s32 unknown680; // 0x680
	s32 unknown684; // 0x684
	u8 pad688[0x6A8 - 0x688];
	s32 unknown6A8; // 0x6A8
	s32 unknown6AC; // 0x6AC
	u8 pad6B0[0x6F0 - 0x6B0];
	s16 mode;        // 0x6F0
	s16 unknown6F2;  // 0x6F2
	s16 action;      // 0x6F4
	s16 actionFlags; // 0x6F6
	s16 timer;       // 0x6F8
	u8 pad6FA[0x714 - 0x6FA];
	RwV3d scale;        // 0x714
	RwV3d velocity;     // 0x720
	RwV3d acceleration; // 0x72C
	s32 angle[3];       // 0x738
	s32 angle744[3];    // 0x744
	u8 pad750[0x772 - 0x750];
	s16 unknown772[7]; // 0x772
	u8 pad780[0x788 - 0x780];
	s32 unknown788; // 0x788
	f32 unknown78C; // 0x78C
	f32 unknown790; // 0x790
	f32 unknown794; // 0x794
	f32 unknown798; // 0x798
	f32 unknown79C; // 0x79C
	f32 unknown7A0; // 0x7A0
	u8 pad7A4[0x7A8 - 0x7A4];
	RwV3d vector7A8; // 0x7A8
	RwV3d vector7B4; // 0x7B4
	RwV3d speed;     // 0x7C0
	RwV3d vector7CC; // 0x7CC
	RwV3d vector7D8; // 0x7D8
	RwV3d vector7E4; // 0x7E4
	u8 pad7F0[0x9E4 - 0x7F0];
	u8 unknown9E4; // 0x9E4
	u8 pad9E5[0x9E6 - 0x9E5];
	u8 unknown9E6; // 0x9E6
	u8 pad9E7[0x9E8 - 0x9E7];
	u8 unknown9E8; // 0x9E8
};

extern "C" {
extern const f32 lbl_8042D120; // 0.0f
extern const f32 lbl_8042D0E8; // 1.0f
void fn_8003FDD4(Player8003FC44* player);
}

extern "C" void fn_8003FC44(Player8003FC44* player)
{
	player->unknown5DC = 0;
	player->unknown678 = player->unknown680 = 0;
	player->unknown67C = player->unknown684 = 0;
	player->unknown6A8                      = 0;
	player->bytes634[0]                     = 0;
	player->bytes634[1]                     = 0;
	player->bytes634[2]                     = 0;
	player->bytes634[3]                     = 0;
	player->unknown5E0                      = 0;
	player->unknown9E4                      = 0;
	player->unknown9E6                      = 0;
	player->vector5E4.x = player->vector5E4.y = player->vector5E4.z = lbl_8042D120;
	player->target.x = player->target.y = player->target.z = lbl_8042D120;
	player->offset.x = player->offset.y = player->offset.z = lbl_8042D120;
	player->vector61C.x = player->vector61C.y = player->vector61C.z = lbl_8042D120;
	player->unknown600                                              = lbl_8042D120;
	player->range                                                   = lbl_8042D120;
	player->distanceXZ                                              = lbl_8042D120;
	player->distance                                                = lbl_8042D120;
	player->targetId                                                = -1;
	player->unknown6AC                                              = 0;
	player->unknown9E8                                              = 0;
	player->mode                                                    = 0;
	player->unknown6F2                                              = 0;
	player->timer                                                   = 0;
	player->actionFlags &= ~0x2D00;
	player->scale.x        = lbl_8042D0E8;
	player->scale.y        = lbl_8042D0E8;
	player->scale.z        = lbl_8042D0E8;
	player->acceleration.x = player->acceleration.y = player->acceleration.z = lbl_8042D120;
	player->velocity.x = player->velocity.y = player->velocity.z = lbl_8042D120;
	player->angle[0]                                             = 0;
	player->angle[1]                                             = 0;
	player->angle[2]                                             = 0;
	player->angle744[0]                                          = 0;
	player->angle744[1]                                          = 0;
	player->angle744[2]                                          = 0;
	for (s32 i = 0; i < 7; i++) {
		player->unknown772[i] = 0;
	}
	player->unknown788  = 0;
	player->unknown78C  = lbl_8042D120;
	player->unknown790  = lbl_8042D120;
	player->unknown788  = 0;
	player->unknown794  = lbl_8042D120;
	player->unknown798  = lbl_8042D120;
	player->unknown79C  = lbl_8042D0E8;
	player->unknown7A0  = lbl_8042D0E8;
	player->vector7A8.x = player->vector7A8.y = player->vector7A8.z = lbl_8042D120;
	player->vector7B4.x = player->vector7B4.y = player->vector7B4.z = lbl_8042D120;
	player->vector7CC.x = player->vector7CC.y = player->vector7CC.z = lbl_8042D120;
	player->vector7D8.x = player->vector7D8.y = player->vector7D8.z = lbl_8042D120;
	player->vector7E4.x = player->vector7E4.y = player->vector7E4.z = lbl_8042D120;
	player->speed.x = player->speed.y = player->speed.z = lbl_8042D120;
	fn_8003FDD4(player);
}
