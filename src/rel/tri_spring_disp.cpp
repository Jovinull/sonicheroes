#include "types.h"

// TObjTriSpring::Disp (the PS2 build's name). With the game not paused and the
// spring in the camera's view, once the stage timer has moved on it sets the
// three spring materials' colour from the timer (a slow sine pulse on red,
// green and blue, alpha full).

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

typedef struct TriSpringMaterial {
	u8 unk00[0x4];
	RwRGBA color; // 0x04
} TriSpringMaterial;

typedef struct TriSpring {
	u8 unk00[0xC8];
	RwV3d pos; // 0xC8
} TriSpring;

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" s32 triSpringLastTimer;
extern "C" TriSpringMaterial* triSpringMaterials[3];
extern "C" const f32 triSpringViewRadius[1];
extern "C" const f32 triSpringPulseBase[1];
extern "C" const f32 triSpringPulseScale[1];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" f32 fn_800D7B00(s32 angle);

extern "C" void Disp__13TObjTriSpringFv(TriSpring* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		RwSphere sphere;

		sphere.center = object->pos;
		sphere.radius = triSpringViewRadius[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			s32 timer = *(s32*)(lbl_8042C180 + 0x30);

			if (triSpringLastTimer != timer) {
				f32 wave = fn_800D7B00(timer << 9);
				u8 value = triSpringPulseBase[0] + triSpringPulseScale[0] * wave;

				for (int i = 0; i < 3; i++) {
					RwRGBA color;

					color.red                    = value;
					color.green                  = value;
					color.blue                   = value;
					color.alpha                  = 0xFF;
					triSpringMaterials[i]->color = color;
				}
				triSpringLastTimer = timer;
			}
		}
	}
}
