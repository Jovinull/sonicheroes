#include "types.h"

// TEnemyGadgetBomb::CalcParameter (the PS2 build's name): the bomb's motion.
// Its speed eases off (and falls by gravity), it moves, and on reaching the
// ground while falling it lands there and bounces (dampened, sound 0x4002 for
// a hard bounce) and its fuse starts; the fuse and the life count down, and
// either running out sets it to explode (state 2).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct GadgetBomb {
	u8 unk00[0xB4];
	s32 landed; // 0xB4
	u8 unkB8[0x4];
	RwV3d pos;   // 0xBC
	RwV3d speed; // 0xC8
	u8 unkD4[0x10];
	f32 shadowY; // 0xE4
	s32 fuse;    // 0xE8
	s32 life;    // 0xEC
	s32 state;   // 0xF0
} GadgetBomb;

extern "C" void* lbl_8042C388;
extern "C" const f32 gadgetBombScaleXZ[1];
extern "C" const f32 gadgetBombDrag[1];
extern "C" const f32 gadgetBombDragY[1];
extern "C" const f32 gadgetBombGravity[1];
extern "C" const f32 gadgetBombBounce[1];
extern "C" const f32 gadgetBombBounceY[1];
extern "C" const f32 gadgetBombHardBounce[1];

extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);

extern "C" void CalcParameter__16TEnemyGadgetBombFv(GadgetBomb* object)
{
	const f32* limit;

	object->speed.x += gadgetBombDrag[0] * -object->speed.x;
	object->speed.y += gadgetBombDragY[0] * -object->speed.y - gadgetBombGravity[0];
	object->speed.z += gadgetBombDrag[0] * -object->speed.z;
	object->pos.x += object->speed.x;
	object->pos.y += object->speed.y;
	object->pos.z += object->speed.z;
	if (object->shadowY > object->pos.y && object->speed.y < *(limit = gadgetBombScaleXZ)) {
		object->pos.y = object->shadowY;
		object->speed.x *= gadgetBombBounce[0];
		object->speed.y *= gadgetBombBounceY[0];
		object->speed.z *= gadgetBombBounce[0];
		object->landed = 1;
		if ((f32)__fabs(object->speed.y) > *(limit = gadgetBombHardBounce)
		    && lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x4002, &object->pos, NULL, 1, 0, 0);
		}
	}
	if (object->landed != 0 && --object->fuse < 0) {
		object->state = 2;
	}
	if (--object->life < 0) {
		object->state = 2;
	}
}
