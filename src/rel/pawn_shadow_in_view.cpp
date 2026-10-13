#include "types.h"

// The TObjEnemyPawn member before DispShadow (pawnShadowInView here; the PS2
// build's CheckCameraFrustumTestForShadow takes a position and radius, this
// copy reads them itself): whether the shown pawn's shadow point (with the
// module's radius) is in the camera's view; never in state 0x5E or without a
// shadow height.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct Pawn {
	u8 unk000[0x19C];
	s32 state; // 0x19C
	u8 unk1A0[0xF0];
	RwV3d shadow; // 0x290
	u8 unk29C[0x50];
	s32 shown; // 0x2EC
} Pawn;

extern "C" void** lbl_8042C9A4;
extern "C" const f32 pawnNoHeight[1];
extern "C" const f32 pawnShadowRadius[1];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);

extern "C" int pawnShadowInView(Pawn* pawn)
{
	if (pawn->shown == 0) {
		return 0;
	}
	if (pawn->state == 0x5E) {
		return 0;
	}
	if (pawnNoHeight[0] != pawn->shadow.y) {
		RwSphere sphere;

		sphere.center = pawn->shadow;
		sphere.radius = pawnShadowRadius[0];
		return fn_8019CE34(*lbl_8042C9A4, &sphere) != 0;
	}
	return 0;
}
