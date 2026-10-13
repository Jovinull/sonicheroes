#include "types.h"

// TObjBobsleighSignal::Disp (the PS2 build's name). With the game not paused,
// the leader near enough and the signal in the camera's view, it lights it with
// set 4 and the regular light, shows its own lamp texture on the sign effect's
// first layer and one of the arrow textures by the stage timer (four frames) on
// the second (or puts the lamp on the sign material when there is no effect),
// gives the glow material the texture picked from the timer (a sine wave over
// three frames) and draws the signal.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct BobsleighSignal {
	u8 unk00[0xB0];
	RwV3d pos; // 0xB0
	u8 unkBC[0x1C];
	RpClump* clump; // 0xD8
	u8 unkDC[0x18];
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
extern "C" RpMaterial* bobSignalMaterial;
extern "C" RpMaterial* bobSignalFirstMaterial;
extern "C" RwTexture* bobsleighTexture0;
extern "C" RwTexture* bobsleighTexture1;
extern "C" RwTexture* bobsleighTexture2;
extern "C" RwTexture* bobsleighTexture3;
extern "C" RwTexture* bobsleighTexture4;
extern "C" RwTexture* bobsleighTexture5;
extern "C" const f32 bobsleighSignalViewRadius[1];
extern "C" const f32 bobsleighSignalBlinkScale[1];

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void* fn_80146BC8(RpMaterial* material, s32 kind);
extern "C" void fn_80146920(void* effect, s32 layer, RwTexture* texture);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void Disp__19TObjBobsleighSignalFv(BobsleighSignal* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		if (Distance2P2P(&object->pos, lbl_8042C208)
		    > bobsleighSignalReach * bobsleighSignalReach) {
			return;
		}

		s32 timer = *(s32*)(lbl_8042C180 + 0x30);
		RwSphere sphere;

		sphere.center = object->pos;
		sphere.radius = bobsleighSignalViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			RwTexture* texture;
			void* effect;

			lbl_802D5E80.SetCurrentNum(4);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			effect = fn_80146BC8(bobSignalMaterial, 6);
			if (effect != NULL) {
				fn_80146920(effect, 1, object->lamp);
				switch (*(s32*)(lbl_8042C180 + 0x30) & 3) {
					case 0:
						texture = bobsleighTexture3;
						break;
					case 2:
						texture = bobsleighTexture4;
						break;
					case 1:
					case 3:
						texture = bobsleighTexture5;
						break;
				}
				fn_80146920(effect, 0, texture);
			} else {
				fn_8015498C(bobSignalMaterial, object->lamp);
			}

			f32 wave  = fn_800D7B00((timer << 11) % 0x10000);
			u32 frame = bobsleighSignalBlinkScale[0] + bobsleighSignalBlinkScale[0] * wave;

			switch ((s32)(frame >> 1)) {
				case 0:
					texture = bobsleighTexture0;
					break;
				case 1:
					texture = bobsleighTexture2;
					break;
				default:
					texture = bobsleighTexture1;
					break;
			}
			fn_8015498C(bobSignalFirstMaterial, texture);
			fn_8014FF2C(object->clump);
		}
	}
}
