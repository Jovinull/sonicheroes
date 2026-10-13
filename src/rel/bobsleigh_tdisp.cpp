#include "types.h"

// TObjBobsleigh::TDisp (the PS2 build's name). With the game not paused and
// the sled in the camera's view and near its team leader's recent position:
// in the two-player bobsleigh stages (26 to 28) it places the arrows and draws
// the other team's arrow model with culling off; then, while the sled is
// running (not finished), it drops its shadow, fading with the height above
// the ground, turned like the sled (Z, X and Y angles and the path's yaw).

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

struct RwMatrixTag {
	u8 data[0x40];
};

class PlayerMaster
{
public:
	RwV3d* GetPlayerPositionHistory(int player, u8 frame);
};

typedef struct BobsleighTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4]; // 0x110
} BobsleighTeam;

typedef struct Bobsleigh {
	u8 unk000[0x100];
	s32 state;   // 0x100
	RwV3d pos;   // 0x104
	s32 pathYaw; // 0x110 (unused here)
	s32 yaw;     // 0x114
	u8 unk118[0x84];
	s32 team; // 0x19C
	u8 unk1A0[0x4C];
	f32 height; // 0x1EC
	u8 unk1F0[0x4];
	RwV3d ground; // 0x1F4
	s32 angX;     // 0x200
	s32 angY;     // 0x204
	s32 angZ;     // 0x208
	u8 unk20C[0x15C];
	s32 shadow; // 0x368
} Bobsleigh;

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" PlayerMaster lbl_8042C1BC;
typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" s32 lbl_8042C1FC;
extern "C" RpClump* s31bobDummyModels[2];
extern "C" f32 bobsleighDrawReach;
extern "C" const f32 bobsleighViewRadius[1];
extern "C" const f32 bobsleighOne[1];
extern "C" const f32 sledShadowFade[1];
extern "C" const f32 sledShadowMin[1];
extern "C" const f32 sledShadowWidth[1];
extern "C" const f32 sledShadowLength[1];
extern "C" const RwV3d sledShadowOffset;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" s32 fn_80194294(s32 state, void* value);
extern "C" s32 fn_80194234(s32 state, void* value);
extern "C" void SetArrowPosition__13TObjBobsleighFv(Bobsleigh* object);
extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B7584(RwV3d* pos, s32* angle, RwV3d* scale, f32 strength);
extern "C" void fn_800B7820(void);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);
void GetRotYXZ(RwMatrixTag* matrix, s32* x, s32* y, s32* z);

static inline RwV3d* bobsleighLeaderPos(Bobsleigh* object)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];

	return lbl_8042C1BC.GetPlayerPositionHistory(team->members[team->leader], 0);
}

extern "C" void TDisp__13TObjBobsleighFv(Bobsleigh* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		RwSphere sphere;

		sphere.center = object->ground;
		sphere.radius = bobsleighViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)
		    && !(Distance2P2P(&object->pos, bobsleighLeaderPos(object))
		        > bobsleighDrawReach * bobsleighDrawReach)) {
			if (lbl_8029C310.stage == 26 || lbl_8029C310.stage == 27 || lbl_8029C310.stage == 28) {
				int i;

				SetArrowPosition__13TObjBobsleighFv(object);
				for (i = 0; i < 2; i++) {
					if (i != lbl_8042C1FC && object->team == i && s31bobDummyModels[i] != NULL) {
						s32 cull;

						fn_80194294(0x14, &cull);
						fn_80194234(0x14, (void*)1);
						fn_8014FF2C(s31bobDummyModels[i]);
						fn_80194234(0x14, (void*)cull);
					}
				}
			}
			if (object->shadow != 0 && object->state != 5) {
				f32 strength = bobsleighOne[0] - sledShadowFade[0] * object->height;

				if (strength > sledShadowMin[0]) {
					fn_800B7864(6);
					RwV3d scale;
					s32 angle[3];
					RwV3d offset = sledShadowOffset;
					RwV3d pos;
					RwMatrixTag matrix;

					scale.x = sledShadowWidth[0];
					scale.y = bobsleighOne[0];
					scale.z = sledShadowLength[0];
					fn_80196050(&matrix, &object->ground, 0);
					fn_80195790(&matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(object->angZ),
					    fn_800D7B00(object->angZ), 1);
					fn_80195790(&matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(object->angX),
					    fn_800D7B00(object->angX), 1);
					fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->angY),
					    fn_800D7B00(object->angY), 1);
					fn_80195790(&matrix, &AxisY, bobsleighOne[0] - fn_800D7AE4(object->yaw),
					    fn_800D7B00(object->yaw), 1);
					CalcPoint(&matrix, &offset, &pos);
					GetRotYXZ(&matrix, &angle[0], &angle[1], &angle[2]);
					fn_800B7584(&pos, angle, &scale, strength);
					fn_800B7820();
				}
			}
		}
	}
}
