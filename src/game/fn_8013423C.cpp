// Classifies how visible the two players are (HYPOTHESIS; names inferred): tests a sphere at each
// player's position against the camera frustum, first with the inner radius (0x98 of
// lbl_8042C7A8, or lbl_8042BBB8 below lbl_8042EFA8) and then with the outer one (0x94, or
// lbl_8042BBBC); stores 2 in lbl_8042C7AC (0x8) when a player is outside or on the edge of the
// outer sphere test, 0 when both are fully inside the inner one too, and 1 otherwise.
// NonMatching: retail keeps the two test results in a stack array; this draft keeps them in
// registers (array, struct and loop forms tried).
#include "game/object.h"

struct RwCamera;

struct Player8013423C {
	u8 pad0[0x40];
	RwV3d position; // 0x40
};

struct Context8013423C {
	u8 pad0[0x28];
	RwCamera* camera; // 0x28
};

struct Radii8013423C {
	u8 pad0[0x94];
	f32 outer; // 0x94
	f32 inner; // 0x98
};

struct Result8013423C {
	u8 pad0[0x8];
	s32 visibility; // 0x8
};

extern "C" {
extern Player8013423C* lbl_80303DC8[];
extern Context8013423C* lbl_8042C1F8;
extern Radii8013423C* lbl_8042C7A8;
extern Result8013423C* lbl_8042C7AC;
extern f32 lbl_8042BBB8;
extern f32 lbl_8042BBBC;
extern const f32 lbl_8042EFA8;
// HYPOTHESIS: RwCameraFrustumTestSphere (0 outside, 1 on the boundary, 2 inside).
s32 fn_8019CE34(RwCamera* camera, RwSphere* sphere);
}

// Combines the tests of both players: 1 when either is on the boundary, else 0 when either is
// outside, else 2.
static inline s32 combine(const s32* test)
{
	s32 result = 2;

	if (test[0] == 1 || test[1] == 1) {
		result = 1;
	} else if (test[0] == 0 || test[1] == 0) {
		result = 0;
	}
	return result;
}

extern "C" void fn_8013423C(void)
{
	s32 test[2];
	RwSphere sphere;
	s32 inner;
	s32 outer;

	sphere.center = lbl_80303DC8[0]->position;
	if (lbl_8042C7A8->inner < lbl_8042EFA8) {
		sphere.radius = lbl_8042BBB8;
	} else {
		sphere.radius = lbl_8042C7A8->inner;
	}
	test[0]       = fn_8019CE34(lbl_8042C1F8->camera, &sphere);
	sphere.center = lbl_80303DC8[1]->position;
	test[1]       = fn_8019CE34(lbl_8042C1F8->camera, &sphere);
	inner         = combine(test);

	sphere.center = lbl_80303DC8[0]->position;
	if (lbl_8042C7A8->outer < lbl_8042EFA8) {
		sphere.radius = lbl_8042BBBC;
	} else {
		sphere.radius = lbl_8042C7A8->outer;
	}
	test[0]       = fn_8019CE34(lbl_8042C1F8->camera, &sphere);
	sphere.center = lbl_80303DC8[1]->position;
	test[1]       = fn_8019CE34(lbl_8042C1F8->camera, &sphere);
	outer         = combine(test);

	if (outer != 2) {
		lbl_8042C7AC->visibility = 2;
	} else if (inner == 2) {
		lbl_8042C7AC->visibility = 0;
	} else {
		lbl_8042C7AC->visibility = 1;
	}
}
