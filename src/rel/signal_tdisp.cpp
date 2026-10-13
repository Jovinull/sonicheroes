#include "types.h"

// TObjSignal::TDisp (signalTDisp here). With the game not paused, the signal
// up (its height not at rest) and in the camera's view, it draws its shadow
// while it is high enough (the shadow's strength from its height), then the
// signal's light cone with light set 0x10 and render states 0xA, 0xB and 0x14
// set to 5, 2 and 1: placed at the shadow point, turned by the cone's angles,
// its material coloured by the signal's kind. Z writes (state 0xE) are off
// meanwhile; all four states are put back after.

#include "src/rel/signal_class.inc"

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

typedef struct SignalMaterial {
	u8 unk00[0x4];
	RwRGBA color; // 0x04
} SignalMaterial;

typedef struct SignalFull {
	Signal base;  // 0x00
	RwV3d shadow; // 0xE4
	RwV3d cone;   // 0xF0, angles
} SignalFull;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" CLIGHT lbl_802D5E80;
extern "C" SignalModel* lbl_8_bss_A64;
extern "C" SignalMaterial* lbl_8_bss_A70;
extern "C" const f32 lbl_8_rodata_BA8[1];
extern "C" const f32 signalViewRadius[1];
extern "C" const RwV3d signalShadowNormal;
extern "C" const f32 signalShadowScale[1];
extern "C" const f32 signalShadowMin[1];
extern "C" const RwV3d signalConeOffset;
extern "C" RwRGBA signalConeColors[3];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B7514(RwV3d* pos, RwV3d* angle, RwV3d* normal, f32 strength);
extern "C" void fn_800B7820(void);
extern "C" void fn_8019ED68(void* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8014FF2C(SignalModel* model);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void signalTDisp(SignalFull* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && lbl_8_rodata_BA8[0] != object->shadow.y) {
		RwSphere sphere;

		sphere.center = object->shadow;
		sphere.radius = signalViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			s32 zwrite;

			fn_80194294(0xE, &zwrite);
			fn_80194234(0xE, 0);
			RwV3d normal = signalShadowNormal;
			f32 strength = lbl_8_rodata_BB0[0]
			    - signalShadowScale[0] * (object->base.pos.y - object->shadow.y);
			if (strength > signalShadowMin[0]) {
				fn_800B7864(1);
				fn_800B7514(&object->shadow, &object->cone, &normal, strength);
				fn_800B7820();
			}
			lbl_802D5E80.SetCurrentNum(0x10);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			if (lbl_8_bss_A64 != NULL) {
				s32 src;
				s32 dst;
				s32 cull;
				void* frame;
				RwRGBA* color;

				fn_80194294(0xA, &src);
				fn_80194294(0xB, &dst);
				fn_80194294(0x14, &cull);
				fn_80194234(0xA, 5);
				fn_80194234(0xB, 2);
				fn_80194234(0x14, 1);
				frame = lbl_8_bss_A64->frame;
				fn_8019EB94(frame, (RwV3d*)&signalConeOffset, 0);
				fn_8019ED68(frame, &AxisY, object->cone.y, 2);
				fn_8019ED68(frame, &AxisX, object->cone.x, 2);
				fn_8019ED68(frame, &AxisZ, object->cone.z, 2);
				fn_8019EB94(frame, &object->shadow, 2);
				if (lbl_8_bss_A70 != NULL) {
					color = NULL;
					switch ((s8)object->base.kind) {
						case 0:
							color = &signalConeColors[0];
							break;
						case 1:
							color = &signalConeColors[1];
							break;
						case 2:
							color = &signalConeColors[2];
							break;
					}
					if (color != NULL) {
						lbl_8_bss_A70->color = *color;
					}
				}
				fn_8014FF2C(lbl_8_bss_A64);
				fn_80194234(0x14, cull);
				fn_80194234(0xA, src);
				fn_80194234(0xB, dst);
			}
			fn_80194234(0xE, zwrite);
		}
	}
}
