#include "types.h"

// TObjSignal::Disp (signalDisp here). With the game not paused and the signal
// in the camera's view, it lights the model by the placement's light bits, shows
// the signal's lamp for its kind on the lamp effect's first layer and one of
// the arrow textures by the stage timer (four frames) on the second (or puts
// the lamp texture on the lamp material when there is no effect), picks the
// glow texture from the timer (a sine wave over three frames) and draws the
// model.

#include "src/rel/signal_class.inc"

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

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
extern "C" void* lbl_8_bss_A68;
extern "C" void* lbl_8_bss_A6C;
extern "C" void* lbl_8_bss_A74;
extern "C" void* lbl_8_bss_A78;
extern "C" void* lbl_8_bss_A7C;
extern "C" void* lbl_8_bss_A80;
extern "C" void* lbl_8_bss_A84;
extern "C" void* lbl_8_bss_A88;
extern "C" void* lbl_8_bss_A8C;
extern "C" void* lbl_8_bss_A90;
extern "C" void* lbl_8_bss_A94;
extern "C" const f32 signalViewRadius[1];
extern "C" const f32 signalBlinkScale[1];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void* fn_80146BC8(void* material, s32 kind);
extern "C" void fn_80146920(void* effect, s32 layer, void* texture);
extern "C" void fn_8015498C(void* material, void* texture);
extern "C" void fn_8014FF2C(SignalModel* model);

extern "C" void signalDisp(Signal* object)
{
	u8* game = lbl_8042C180;

	if ((s8)game[0x20] == 0) {
		s32 timer = *(s32*)(game + 0x30);
		RwSphere sphere;

		sphere.center = object->pos;
		sphere.radius = signalViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			void* texture;
			void* effect;

			lbl_802D5E80.SetCurrentNum(
			    ((*(u32*)((u8*)object->setdata + 0x18) & 0x1C0000) >> 18) + 4);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			switch ((s8)object->kind) {
				case 0:
					texture = lbl_8_bss_A74;
					break;
				case 1:
					texture = lbl_8_bss_A78;
					break;
				case 2:
				default:
					texture = lbl_8_bss_A7C;
					break;
			}
			effect = fn_80146BC8(lbl_8_bss_A68, 6);
			if (effect != NULL) {
				fn_80146920(effect, 1, texture);
				switch (*(s32*)(lbl_8042C180 + 0x30) & 3) {
					case 0:
						texture = lbl_8_bss_A80;
						break;
					case 2:
						texture = lbl_8_bss_A84;
						break;
					case 1:
					case 3:
						texture = lbl_8_bss_A88;
						break;
				}
				fn_80146920(effect, 0, texture);
			} else {
				fn_8015498C(lbl_8_bss_A68, texture);
			}

			void* glow;
			f32 wave  = fn_800D7B00((timer << 11) % 0x10000);
			u32 frame = signalBlinkScale[0] + signalBlinkScale[0] * wave;

			switch ((s32)(frame >> 1)) {
				case 0:
					glow = lbl_8_bss_A8C;
					break;
				case 1:
					glow = lbl_8_bss_A94;
					break;
				default:
					glow = lbl_8_bss_A90;
					break;
			}
			fn_8015498C(lbl_8_bss_A6C, glow);
			fn_8014FF2C(object->model);
		}
	}
}
