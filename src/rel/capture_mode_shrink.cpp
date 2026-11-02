#include "types.h"

// One of the capture enemy's mode hooks (captureModeShrink here), the same in
// the seven stage modules that carry the capture. Phase 0 forgets the held
// player (as captureDropPlayer does), sets full size with no shrink speed and
// motion 0; phase 1 speeds the shrink up by the module's step and shrinks,
// and once flat the placement is ended and the enemy asks to be killed;
// phases 2 and 3 do nothing.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

class TObjSetObj
{
public:
	void SetEnd();
};

typedef struct CapturePlayer {
	u8 unk000[0x6F0];
	s16 state; // 0x6F0
} CapturePlayer;

typedef struct Capture {
	u8 unk000[0x4];
	u16 signal; // 0x004
	u8 unk006[0xAA];
	TObjSetObj setObj; // 0x0B0
	u8 unk0B1[0x23];
	s32 motion; // 0x0D4
	u8 unk0D8[0x1A0];
	s32 player; // 0x278
	u8 unk27C[0x3C];
	RwV3d scale;  // 0x2B8
	RwV3d shrink; // 0x2C4
} Capture;

extern "C" CapturePlayer* lbl_802AD070[];
extern "C" const f32 captureOne;
extern "C" const f32 captureZero;
extern "C" const RwV3d captureShrinkStep;

extern "C" void fn_80043DEC(void);

extern "C" void captureModeShrink(Capture* object, s32 phase)
{
	switch (phase) {
		case 0: {
			s32 player = object->player;

			if (player != -1) {
				CapturePlayer* body = lbl_802AD070[player];

				if (body != NULL) {
					if (body->state == 0x26) {
						fn_80043DEC();
					}
					object->player = -1;
				}
			}
			object->scale.x = object->scale.y = object->scale.z = captureOne;
			object->shrink.x = object->shrink.y = object->shrink.z = captureZero;
			object->motion                                         = 0;
			return;
		}
		case 1:
			object->shrink.x += captureShrinkStep.x;
			object->shrink.y += captureShrinkStep.y;
			object->shrink.z += captureShrinkStep.z;
			object->scale.x += object->shrink.x;
			object->scale.y += object->shrink.y;
			object->scale.z += object->shrink.z;
			if (object->scale.x < captureZero) {
				object->setObj.SetEnd();
				object->signal |= 1;
			}
			return;
		case 2:
		case 3:
			break;
	}
}
