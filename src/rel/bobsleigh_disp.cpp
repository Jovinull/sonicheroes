#include "types.h"

// TObjBobsleigh::Disp (the PS2 build's name). With the game not paused it
// draws the bobsleigh when it is in the camera's view, near enough to its
// team leader's recent position and not finished (state 5): grey and without
// texture on the flashing frames while it is hurt. Then it draws the second
// model (the bobsleigh's other part) the same way when it has one.

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

class DealMaterial
{
public:
	void DefaultColor();
	void SetColor(RwRGBA* color);
	void DefaultTexture();
	void NoTexture();
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
	s32 state; // 0x100
	RwV3d pos; // 0x104
	u8 unk110[0x28];
	RwV3d partPos; // 0x138
	u8 unk144[0x58];
	s32 team; // 0x19C
	u8 unk1A0[0x144];
	s32 hurt; // 0x2E4
	u8 unk2E8[0x28];
	RpClump* clump; // 0x310
	RpClump* part;  // 0x314
	u8 unk318[0x4C];
	s32 hasPart; // 0x364
	u8 unk368[0x24];
	DealMaterial* material; // 0x38C
} Bobsleigh;

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" PlayerMaster lbl_8042C1BC;
extern "C" f32 bobsleighDrawReach;
extern "C" s32 bobsleighLastTimer;
extern "C" const f32 bobsleighViewRadius[1];
extern "C" const f32 bobsleighPartViewRadius[1];

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_8014FF2C(RpClump* clump);

static inline RwV3d* bobsleighLeaderPos(Bobsleigh* object)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];

	return lbl_8042C1BC.GetPlayerPositionHistory(team->members[team->leader], 0);
}

extern "C" void Disp__13TObjBobsleighFv(Bobsleigh* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		RwSphere sphere;

		sphere.center = object->pos;
		sphere.radius = bobsleighViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)
		    && Distance2P2P(&object->pos, bobsleighLeaderPos(object))
		        < bobsleighDrawReach * bobsleighDrawReach
		    && object->state != 5) {
			s32 flash = (bool)(object->hurt > 0 && (object->hurt / 4) % 2 != 0);

			if (flash) {
				RwRGBA color;

				color.red = color.green = color.blue = 0x80;
				color.alpha                          = 0xFF;
				object->material->NoTexture();
				object->material->SetColor(&color);
			}
			fn_8014FF2C(object->clump);
			if (flash) {
				object->material->DefaultTexture();
				object->material->DefaultColor();
			}
		}
		sphere.center = object->partPos;
		sphere.radius = bobsleighPartViewRadius[0];
		if (object->hasPart != 0 && fn_8019CE34(*lbl_8042C9A4, &sphere)
		    && Distance2P2P(&object->partPos, bobsleighLeaderPos(object))
		        < bobsleighDrawReach * bobsleighDrawReach) {
			s32 timer = *(s32*)(lbl_8042C180 + 0x30);

			if (bobsleighLastTimer != timer) {
				bobsleighLastTimer = timer;
			}
			fn_8014FF2C(object->part);
		}
	}
}
