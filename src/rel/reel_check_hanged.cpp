#include "types.h"

// TObjReel::CheckHangedPlayer (the PS2 build's name, by its place in the PS2
// order; reelCheckHangedPlayer here). A reel at rest (state 1) and not waiting
// looks, in the frame of its hook (below the reel by its length, facing the
// reel), for the team leader nearest the hook's axis within reach and between
// the heights allowed; that leader is hung (action 0x15/0x3D), the reel winds
// or lets out by its kind, and the team reacts.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct ReelPlayerBody {
	u8 unk000[0x89C];
	f32 height; // 0x89C
} ReelPlayerBody;

typedef struct ReelTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4];             // 0x110
	ReelPlayerBody* bodies[4]; // 0x114
} ReelTeam;

typedef struct ReelPlayer {
	u8 unk000[0x25E];
	s8 team; // 0x25E
} ReelPlayer;

typedef struct Reel {
	u8 unk00[0xB8];
	s32 state;     // 0xB8
	s8 kind;       // 0xBC
	s8 holder;     // 0xBD
	u8 unkBE[0x2]; // 0xBE
	f32 current;   // 0xC0
	u8 unkC4[0x14];
	s8 wait;       // 0xD8
	u8 unkD9[0x3]; // 0xD9
	RwV3d pos;     // 0xDC
	s32 angX;      // 0xE8
	s32 angY;      // 0xEC
} Reel;

extern "C" ReelTeam* lbl_80303DC8[];
extern "C" ReelPlayer* lbl_802AD0D0[];
extern "C" const RwV3d AxisY;
extern "C" const f32 reelZero[1];
extern "C" const f32 reelOne[1];
extern "C" const f32 reelHookDepth[1];
extern "C" const f32 reelHangDepth[1];
extern "C" const f32 reelCatchReach[1];
extern "C" const f32 reelCatchStart[1];
extern "C" const f32 reelCatchLow[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" RwMatrixTag* fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" s32 fn_8003E2E4(s32 player, s32 a, RwV3d* pos, s32 b);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_800E1208(s32 player, s32 action, s32 arg);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg);

extern "C" void reelCheckHangedPlayer(Reel* object)
{
	if (object->state == 1 && object->wait <= 0) {
		RwMatrixTag matrix;
		RwMatrixTag inverse;
		RwV3d offset;
		RwV3d pos;
		RwV3d local;

		fn_80195790(&matrix, &AxisY, reelOne[0] - fn_800D7AE4(0xC000 - object->angY),
		    fn_800D7B00(0xC000 - object->angY), 0);
		offset.x = offset.z = reelZero[0];
		offset.y            = -object->current - reelHangDepth[0];
		fn_80196050(&matrix, &offset, 2);
		fn_80196050(&matrix, &object->pos, 2);
		fn_80195B5C(&inverse, &matrix);
		f32 best  = reelCatchStart[0];
		s32 found = -1;
		for (int i = 0; i < 4; i++) {
			s32 leader;
			ReelTeam* team = lbl_80303DC8[i];

			if (team == NULL) {
				continue;
			}
			leader = team->members[team->leader];
			if (fn_8003E2E4(leader, 0, &pos, 0) == 0) {
				continue;
			}
			pos.y += team->bodies[team->leader]->height;
			fn_8019941C(&local, &pos, 1, &inverse);
			f32 distance = local.x * local.x + local.y * local.y;
			if (distance > reelCatchReach[0] || local.z > reelHookDepth[0]
			    || local.z < reelCatchLow[0] || best < distance) {
				continue;
			}
			best  = distance;
			found = leader;
		}
		if (found != -1) {
			object->holder = found;
			fn_800E1208(found, 0x15, 0x3D);
			object->wait = 4;
			switch (object->kind) {
				case 0:
					object->state = 2;
					break;
				case 1:
					object->state = 4;
					break;
			}
			fn_8001F674(lbl_802AD0D0[found]->team, 4, 0xF, 0);
		}
	}
}
