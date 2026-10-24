#include "types.h"

// TObjRing::TDisp (the PS2 build's name, by its place in the PS2 order;
// ringTDisp here): the rings' shadows. While the game is neither paused nor in
// a demo, each ring neither taken (state 5) nor hidden (flags 3), with a ground
// under it and within 300 of the camera, gets a shadow on the ground where the
// camera sees it (a sphere of radius 5 there), turned like the ring, smaller
// the higher the ring and fading with the distance; drawn without z writes.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center;
	f32 radius;
} RwSphere;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct RingSubstance {
	u8 unk00[0x90];
	RwV3d pos;      // 0x90
	u8 unk9C[0x2C]; // 0x9C
	s8 state;       // 0xC8
	u8 unkC9[0x1];  // 0xC9
	s16 flags;      // 0xCA
	f32 spin;       // 0xCC
	s16 angX;       // 0xD0
	s16 angY;       // 0xD2
	u8 unkD4[0x8];  // 0xD4
	f32 ground;     // 0xDC
	s16 tiltX;      // 0xE0
	s16 tiltZ;      // 0xE2
	u8 unkE4[0x4];  // 0xE4
} RingSubstance;    // 0xE8

typedef struct Ring {
	u8 unk00[0x28];
	s8 numRings;          // 0x28
	u8 unk29[0x23];       // 0x29
	RingSubstance* rings; // 0x4C
} Ring;

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" RwV3d* lbl_8042C208;
extern "C" const RwV3d ringShadowScale;
extern "C" const f32 ringShadowRadius[1];
extern "C" const f32 ringNoGround[1];
extern "C" const f32 ringShadowRange[1];
extern "C" const f32 ringAngleScale[1];
extern "C" const f32 ringOne[1];
extern "C" const f32 ringShadowShrink[1];
extern "C" const f32 ringShadowFade[1];

extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B7820(void);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" s32 fn_80194234(s32 state, void* value);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void fn_800B7584(RwV3d* pos, sAngle* ang, RwV3d* scale, f32 size);

extern "C" void ringTDisp(Ring* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && *(s32*)(lbl_8042C180 + 0x40) < 0) {
		RingSubstance* ring = object->rings;
		void* camera        = *lbl_8042C9A4;
		RwV3d eye           = *lbl_8042C208;
		void* zwrite;

		fn_800B7864(0);
		fn_80194294(0xE, &zwrite);
		fn_80194234(0xE, NULL);
		RwV3d scale = ringShadowScale;
		RwSphere sphere;
		sAngle ang;

		sphere.radius = ringShadowRadius[0];
		if (ring != NULL) {
			for (s32 i = 0; i < object->numRings; i++, ring++) {
				if (ring->state == 5 || (ring->flags & 3) == 3 || ringNoGround[0] == ring->ground) {
					continue;
				}
				f32 dx       = ring->pos.x - eye.x;
				f32 dy       = ring->pos.y - eye.y;
				f32 dz       = ring->pos.z - eye.z;
				f32 zz       = dz * dz;
				f32 xx       = dx * dx;
				f32 yy       = dy * dy;
				f32 distance = zz + (xx + yy);
				if (distance > ringShadowRange[0]) {
					continue;
				}
				sphere.center.x = ring->pos.x;
				sphere.center.y = ring->ground;
				sphere.center.z = ring->pos.z;
				if (fn_8019CE34(camera, &sphere) == 0) {
					continue;
				}
				ang.x    = ring->tiltX;
				ang.y    = ring->angY + (s32)(ringAngleScale[0] * ring->spin);
				ang.z    = ring->tiltZ;
				f32 drop = ringShadowShrink[0] * (ring->pos.y - ring->ground);
				f32 size = ringOne[0] - drop;
				f32 fade = ringShadowFade[0] * (ringShadowRange[0] - distance);
				if (fade < ringOne[0]) {
					size *= fade;
				}
				fn_800B7584(&sphere.center, &ang, &scale, size);
			}
		}
		fn_80194234(0xE, zwrite);
		fn_800B7820();
	}
}
