#include "types.h"

// TObjEnemyPawn::DispShadow (the PS2 build's name, by its member order): drops
// the pawn's three shadows (body and both feet; the module's two shadow sizes),
// fading with the height above the shadow point.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct Pawn {
	u8 unk000[0x144];
	f32 height; // 0x144
	u8 unk148[0x148];
	RwV3d shadow;  // 0x290
	RwV3d shadowL; // 0x29C
	RwV3d shadowR; // 0x2A8
	sAngle cone;   // 0x2B4
	sAngle coneL;  // 0x2C0
	sAngle coneR;  // 0x2CC
} Pawn;

extern "C" const RwV3d pawnShadowSize;
extern "C" const RwV3d pawnFootShadowSize;
extern "C" const f32 pawnOne[1];
extern "C" const f32 pawnShadowFade[1];

extern "C" void fn_800B7864(s32 kind);
extern "C" void fn_800B7514(RwV3d* pos, sAngle* angle, RwV3d* size, f32 strength);
extern "C" void fn_800B7820(void);

extern "C" void DispShadow__13TObjEnemyPawnFv(Pawn* pawn)
{
	fn_800B7864(0);
	RwV3d size   = pawnShadowSize;
	f32 strength = pawnOne[0] - pawnShadowFade[0] * (pawn->height - pawn->shadow.y);

	fn_800B7514(&pawn->shadow, &pawn->cone, &size, strength);
	RwV3d footSize = pawnFootShadowSize;

	fn_800B7514(&pawn->shadowL, &pawn->coneL, &footSize, strength);
	fn_800B7514(&pawn->shadowR, &pawn->coneR, &footSize, strength);
	fn_800B7820();
}
