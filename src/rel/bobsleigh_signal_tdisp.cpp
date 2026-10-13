#include "types.h"

// TObjBobsleighSignal::TDisp (the PS2 build's name). With the game not paused,
// the leader near enough, the signal up (its height not at rest) and in the
// camera's view, it draws its shadow while it is high enough (the strength
// from its height), then the light cone (the shade model) with light set 0x10
// and render states 0xA, 0xB and 0x14 set to 5, 2 and 1 (put back after):
// placed at the shadow point, turned by the cone's angles, its material
// coloured by the lamp (one colour for the sixth texture, one for the rest).

typedef struct RpClump RpClump;
typedef struct RwTexture RwTexture;

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

typedef struct BobsleighMaterial {
	u8 unk00[0x4];
	RwRGBA color; // 0x04
} BobsleighMaterial;

typedef struct BobsleighClump {
	u8 unk00[0x4];
	void* frame; // 0x04
} BobsleighClump;

typedef struct BobsleighSignal {
	u8 unk00[0xB0];
	RwV3d pos; // 0xB0
	u8 unkBC[0x20];
	RwV3d shadow;    // 0xDC
	RwV3d cone;      // 0xE8, angles
	RwTexture* lamp; // 0xF4
} BobsleighSignal;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" RwV3d* lbl_8042C208;
extern "C" void** lbl_8042C9A4;
extern "C" CLIGHT lbl_802D5E80;
extern "C" f32 bobsleighSignalReach;
extern "C" BobsleighClump* bobSignalShadeClump;
extern "C" BobsleighMaterial* bobSignalShadeMaterial;
extern "C" RwTexture* bobsleighTexture6;
extern "C" RwRGBA bobsleighConeColors[2];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 bobsleighSignalRest[1];
extern "C" const f32 bobsleighSignalViewRadius[1];
extern "C" const f32 bobsleighShadowBase[1];
extern "C" const f32 bobsleighShadowScale[1];
extern "C" const f32 bobsleighShadowMin[1];
extern "C" const RwV3d bobsleighShadowNormal;
extern "C" const RwV3d bobsleighConeOffset;

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B7514(RwV3d* pos, RwV3d* angle, RwV3d* normal, f32 strength);
extern "C" void fn_800B7820(void);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019ED68(void* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8014FF2C(BobsleighClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void TDisp__19TObjBobsleighSignalFv(BobsleighSignal* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		if (Distance2P2P(&object->pos, lbl_8042C208)
		    > bobsleighSignalReach * bobsleighSignalReach) {
			return;
		}
		if (bobsleighSignalRest[0] != object->shadow.y) {
			RwSphere sphere;

			sphere.center = object->shadow;
			sphere.radius = bobsleighSignalViewRadius[0];
			if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
				f32 strength = bobsleighShadowBase[0]
				    - bobsleighShadowScale[0] * (object->pos.y - object->shadow.y);

				if (strength > bobsleighShadowMin[0]) {
					fn_800B7864(1);
					RwV3d normal = bobsleighShadowNormal;
					fn_800B7514(&object->shadow, &object->cone, &normal, strength);
					fn_800B7820();
				}
				lbl_802D5E80.SetCurrentNum(0x10);
				lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
				if (bobSignalShadeClump != NULL) {
					s32 src;
					s32 dst;
					s32 cull;
					void* frame;

					fn_80194294(0xA, &src);
					fn_80194294(0xB, &dst);
					fn_80194294(0x14, &cull);
					fn_80194234(0xA, 5);
					fn_80194234(0xB, 2);
					fn_80194234(0x14, 1);
					frame = bobSignalShadeClump->frame;
					fn_8019EB94(frame, (RwV3d*)&bobsleighConeOffset, 0);
					fn_8019ED68(frame, &AxisY, object->cone.y, 2);
					fn_8019ED68(frame, &AxisX, object->cone.x, 2);
					fn_8019ED68(frame, &AxisZ, object->cone.z, 2);
					fn_8019EB94(frame, &object->shadow, 2);
					if (bobSignalShadeMaterial != NULL) {
						RwRGBA* color;

						if (object->lamp == bobsleighTexture6) {
							color = &bobsleighConeColors[0];
						} else {
							color = &bobsleighConeColors[1];
						}
						bobSignalShadeMaterial->color = *color;
					}
					fn_8014FF2C(bobSignalShadeClump);
					fn_80194234(0x14, cull);
					fn_80194234(0xA, src);
					fn_80194234(0xB, dst);
				}
			}
		}
	}
}
