#include "types.h"

// TObjSetRing::Disp (the PS2 build's name, by its place in the PS2 order;
// ringObjectDisp here): TObjRing::Disp (rel/ring_disp.cpp) for an active set
// ring or one being edited, under the light set its placement picks (4 plus
// bits 18 to 20 of its flags), and with the distance taken by Distance2P2P.

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

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

typedef struct SetRingFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} SetRingFrame;

typedef struct SetRing {
	u8 unk00[0x28];
	s8 numRings;          // 0x28
	u8 unk29[0x1];        // 0x29
	s8 active;            // 0x2A
	u8 unk2B[0x21];       // 0x2B
	RingSubstance* rings; // 0x4C
	SetRingFrame* frame;  // 0x50, the set object's (TObjSetObj)
} SetRing;

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
extern "C" RwV3d* lbl_8042C208;
extern "C" CLIGHT lbl_802D5E80;
extern "C" RpClump* ringModel;
extern "C" RpClump* ringLargeModel;
extern "C" const RwV3d AxisY;
extern "C" const f32 ringShadowRadius[1];
extern "C" const f32 ringLargeRange[1];
extern "C" const f32 ringAngleScale[1];
extern "C" const f32 ringOne[1];

extern "C" s32 OnEdit__10TObjSetObjFv(void* motion);
extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
f32 Distance2P2P(const RwV3d* a, const RwV3d* b);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void ringObjectDisp(SetRing* object)
{
	if (object->active == 1 || OnEdit__10TObjSetObjFv(&object->frame)) {
		if ((s8)lbl_8042C180[0x20] == 0 && *(s32*)(lbl_8042C180 + 0x40) < 0) {
			RwFrame* frame;
			RingSubstance* ring = object->rings;

			lbl_802D5E80.SetCurrentNum(((object->frame->flags & 0x1C0000) >> 18) + 4);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			void* camera = *lbl_8042C9A4;
			RwV3d eye    = *lbl_8042C208;
			RwSphere sphere;
			RpClump* model;

			sphere.radius = ringShadowRadius[0];
			for (s32 i = 0; i < object->numRings; i++, ring++) {
				if (ring == NULL || ring->state == 5 || (ring->flags & 3) == 3) {
					continue;
				}
				sphere.center = ring->pos;
				if (fn_8019CE34(camera, &sphere) == 0) {
					continue;
				}
				if (Distance2P2P(&ring->pos, &eye) > ringLargeRange[0]) {
					model = ringLargeModel;
				} else {
					model = ringModel;
				}
				frame = model->frame;
				fn_80195790(&frame->modelling, &AxisY,
				    ringOne[0] - fn_800D7AE4(ring->angY + (s32)(ringAngleScale[0] * ring->spin)),
				    fn_800D7B00(ring->angY + (s32)(ringAngleScale[0] * ring->spin)), 0);
				fn_8019EB94(frame, &ring->pos, 2);
				fn_8014FF2C(model);
			}
		}
	}
}
