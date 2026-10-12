#include "types.h"

// The checkpoint star's pass check (checkpointStarCheckPass here). Outside the
// game modes 3, 4 and 8 and while the game's flag at 0x21 is clear, it looks
// at the eight players: a leader or partner of its team, not in the poses
// 0x26 and 0x3B and not the one who last passed, that is within reach of the
// star (a little above its centre) passes it. The star goes to state 2, the
// score manager counts the pass, the post keeps the player, the star takes
// the player's speed scaled down (none for a player out of range) and the
// post saves the restart position; the pass sound plays and the post's eight
// pending flags are cleared, each through fn_800E1208.
//
// The unit is built without fused multiply-add (the distance is summed with
// separate multiplies and adds), and the post's kind is read before the other
// arguments of setSavePos, as the volatile load keeps it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CheckpointTeam {
	u8 pad000[0x3A];
	s8 partner; // 0x3A
	s8 leader;  // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
} CheckpointTeam;

typedef struct CheckpointPlayerTask {
	u8 pad000[0x6F0];
	s16 pose; // 0x6F0
} CheckpointPlayerTask;

typedef struct CheckpointPlayerWork {
	u8 pad000[0x258];
	CheckpointTeam* team; // 0x258
} CheckpointPlayerWork;

typedef struct CheckpointPlayerInfo {
	u8 pad00[0x10];
	s32 unk10; // 0x10
} CheckpointPlayerInfo;

typedef struct CheckpointPost {
	u8 pad00[0x30];
	s8 passedBy; // 0x30
	u8 pad31;    // 0x31
	s16 unk32;   // 0x32
	u8 pad34[4]; // 0x34
	RwV3d save;  // 0x38
	u8 pad44[0x30];
	s8 pending[8]; // 0x74
} CheckpointPost;

typedef struct CheckpointStar {
	s32 state;             // 0x00
	RwV3d pos;             // 0x04
	u8 unk10[0xC];         // 0x10
	RwV3d velocity;        // 0x1C
	u8 unk28[0x4];         // 0x28
	CheckpointPost* owner; // 0x2C
	u8 unk30[0x50];        // 0x30
	s32 unk80;             // 0x80
} CheckpointStar;

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" CheckpointPlayerTask* lbl_802AD070[8];
extern "C" CheckpointPlayerInfo* lbl_802AD090[8];
extern "C" RwV3d* lbl_802AD0B0[8];
extern "C" CheckpointPlayerWork* lbl_802AD0D0[8];
extern "C" void* EnemyScoreMan__14TEnemyScoreMan;
extern "C" const f32 checkpointZero[1];
extern "C" const f32 checkpointPassHeight[1];
extern "C" const f32 checkpointPassReach[1];
extern "C" const f32 checkpointPassSpeed[1];

extern "C" s32 fn_80018C98(void);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" void CreateInstance__14TEnemyScoreManFv(void);
extern "C" void SaveDestroyEnemyTotal__14TEnemyScoreManFv(void* manager);
extern "C" void setSavePos__18PARAM_SAVEPOSITIONFPC5RwV3dii(
    void* self, RwV3d* position, s32 arg2, s32 arg3);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 arg2, s32 arg3);
extern "C" void fn_800E1208(s32 index, s32 arg1, s32 arg2);

extern "C" void checkpointStarCheckPass(CheckpointStar* star)
{
	if (fn_80018C98() == 3 || fn_80018C98() == 4 || fn_80018C98() == 8
	    || (s8)lbl_8042C180[0x21] != 0) {
		return;
	}
	for (s32 i = 0; i < 8; i++) {
		CheckpointPlayerTask* task = lbl_802AD070[i];
		if (task == NULL) {
			continue;
		}
		CheckpointTeam* team;
		s32 pose = task->pose;
		if (pose == 0x26) {
			continue;
		}
		team = lbl_802AD0D0[i]->team;
		if (i != team->members[team->leader] && i != team->members[team->partner]) {
			continue;
		}
		if (pose == 0x3B) {
			continue;
		}
		if (star->owner->passedBy == i) {
			continue;
		}
		RwV3d found;
		if (fn_8003E2E4(i, 1, &found, 0) == 0) {
			continue;
		}
		RwV3d centre = star->pos;
		centre.y += checkpointPassHeight[0];
		found.x -= centre.x;
		found.y -= centre.y;
		found.z -= centre.z;
		if (found.z * found.z + (found.x * found.x + found.y * found.y) > checkpointPassReach[0]) {
			continue;
		}

		star->state = 2;
		if (EnemyScoreMan__14TEnemyScoreMan == NULL) {
			CreateInstance__14TEnemyScoreManFv();
		}
		SaveDestroyEnemyTotal__14TEnemyScoreManFv(EnemyScoreMan__14TEnemyScoreMan);
		star->owner->passedBy = i;
		star->unk80           = 0x4FA;
		if (i < 0 || i >= 8 || lbl_802AD0D0[i] == NULL) {
			star->velocity.x = star->velocity.y = star->velocity.z = checkpointZero[0];
		} else {
			RwV3d* speed     = lbl_802AD0B0[i];
			star->velocity.x = speed->x;
			star->velocity.y = speed->y;
			star->velocity.z = speed->z;
			star->velocity.x *= checkpointPassSpeed[0];
			star->velocity.y *= checkpointPassSpeed[0];
			star->velocity.z *= checkpointPassSpeed[0];
		}
		CheckpointPost* post = star->owner;
		s32 kind             = *(volatile s16*)&post->unk32;
		setSavePos__18PARAM_SAVEPOSITIONFPC5RwV3dii(
		    star, &post->save, lbl_802AD090[i]->unk10, kind);
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1024, 0, 0);
		}
		for (s32 j = 0; j < 8; j++) {
			if (star->owner->pending[j] != 0) {
				fn_800E1208(j, 0xF, 0);
				star->owner->pending[j] = 0;
			}
		}
	}
}
