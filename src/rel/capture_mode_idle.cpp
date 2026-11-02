#include "types.h"

// One of the capture enemy's mode hooks (captureModeIdle here), the same in
// the seven stage modules that carry the capture. Phase 0 starts the mode with
// motion 0 and a 120-frame timer; phase 1, while active, plays sound 0x4011 at
// the enemy each time the timer runs out; phases 2 and 3 do nothing.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Capture {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0x154];
	s32 timer; // 0x2A0
	u8 unk2A4[0x2D0];
	s32 active; // 0x574
} Capture;

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void captureModeIdle(Capture* object, s32 phase)
{
	switch (phase) {
		case 0:
			object->motion = 0;
			object->timer  = 0x78;
			return;
		case 1:
			if (object->active != 0) {
				if (--object->timer < 0) {
					object->timer = 0x78;
					if (lbl_8042C388 != NULL) {
						fn_800B4A38(lbl_8042C388, 0x4011, &object->pos, NULL, 1, 0, 0);
					}
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}
