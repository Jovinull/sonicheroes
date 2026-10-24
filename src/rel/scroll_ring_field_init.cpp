#include "types.h"

// TObjRingSubstance::Init (the PS2 build's name, by its place in the PS2
// order; scrollRingFieldInit here): the ring joins its group as the given
// number, still and unspun, and resets; a ring the storage records as taken
// stays taken (state 5), a scroll group's ring (kind 4) starts scrolling
// (state 4), any other shows (state 1). It gets its size and shade, its
// shadow on the ground under it (0.3 above it, tilted with the ground) if
// there is one, its collision radius, and a collision that ignores players
// unless it scrolls.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RingGroupData {
	u8 unk00[0x18];
};

// TObjRing (rel/ring_cdtor.cpp); its vtable pointer sits at 0x18
struct RingGroup : public RingGroupData {
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void vslot7();
	virtual void vslot8();
	virtual u32* GetStragePointer();
	u8 unk1C[0xD]; // 0x1C
	s8 kind;       // 0x29
};

struct RingSubstanceData {
	u8 unk00[0x8];
	u16 colliFlags;   // 0x08
	u8 unk0A[0x6E];   // 0x0A
	s32 colliRadius;  // 0x78
	u8 unk7C[0x14];   // 0x7C
	RwV3d pos;        // 0x90
	u8 unk9C[0xC];    // 0x9C
	RwV3d vel;        // 0xA8
	f32 size;         // 0xB4
	f32 shade;        // 0xB8
	u8 unkBC[0xC];    // 0xBC
	s8 state;         // 0xC8
	s8 number;        // 0xC9
	s16 flags;        // 0xCA
	f32 spin;         // 0xCC
	s16 angX;         // 0xD0
	u8 unkD2[0x2];    // 0xD2
	RingGroup* group; // 0xD4
};

// one ring; its vtable pointer sits at 0xD8 after the data
struct RingSubstance : public RingSubstanceData {
	virtual void Reset();
	f32 ground; // 0xDC
	s16 tiltX;  // 0xE0
	s16 tiltZ;  // 0xE2
};

extern "C" f32 scrollRingShade;
extern "C" const f32 scrollRingStopped[1];
extern "C" const f32 ringNoGround[1];
extern "C" const f32 ringSize[1];
extern "C" const f32 ringShadowLift[1];

f32 GetShadowPos(RwV3d* pos, sAngle* ang, int kind);

extern "C" void scrollRingFieldInit(RingSubstance* ring, RingGroup* group, s8 number)
{
	ring->group  = group;
	ring->number = number;
	ring->flags  = 0;
	ring->spin   = scrollRingStopped[0];
	ring->angX   = 0;
	ring->vel.x = ring->vel.y = ring->vel.z = scrollRingStopped[0];
	ring->Reset();
	u32* storage = group->GetStragePointer();
	if (storage != NULL && (storage[(number & 0x60) >> 5] & (1 << (number & 0x1F)))) {
		ring->state = 5;
	} else if (ring->group->kind == 4) {
		ring->state = 4;
	} else {
		ring->state = 1;
	}
	ring->size  = ringSize[0];
	ring->shade = scrollRingShade;
	sAngle ang;
	if (ringNoGround[0] != (ring->ground = GetShadowPos(&ring->pos, &ang, 1))) {
		ring->ground += ringShadowLift[0];
		ring->tiltX = ang.x;
		ring->tiltZ = ang.z;
	}
	ring->colliRadius = 11;
	if (ring->group->kind != 4) {
		ring->colliFlags |= 0x40;
	} else {
		ring->colliFlags &= ~0x40;
	}
}
