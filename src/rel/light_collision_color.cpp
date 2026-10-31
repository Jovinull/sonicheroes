#include "types.h"

// Two of the light collision's material helpers, the same in the thirteen
// stage modules that share the engine core (nothing in them calls either):
// putting back the colour of the material rel/light_collision_find.cpp found
// and forgetting what was found, and finding the light's atomic, geometry and
// material and keeping the material's colour. The tint between them
// (fn_N_4E0A4 in stage01D) stays assembly: its first two colour bytes are
// computed and truncated before the material is loaded, which no form here
// reproduces. The compiler emits a unit's functions last first, so the setup
// is written before the reset it follows in the module.

typedef struct RwRGBA {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
} RwRGBA;

typedef struct RpMaterial {
	u8 unk0[0x4];
	RwRGBA color; // 0x4
} RpMaterial;

typedef struct RpGeometry {
	u8 unk0[0x8];
	u32 flags; // 0x8
} RpGeometry;

typedef struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
} RpAtomic;

typedef struct RpClump {
	u8 unk0[0x4];
	void* frame; // 0x4
} RpClump;

extern "C" RpClump* lightCollisionClump;
extern "C" RpAtomic* lightCollisionAtomic;
extern "C" RpGeometry* lightCollisionGeometry;
extern "C" RpMaterial* lightCollisionMaterial;
extern "C" void* lightCollisionFrame;
extern "C" RwRGBA lightCollisionColor;

extern "C" RpAtomic* lightCollisionFindAtomic(RpAtomic* atomic, void* data);
extern "C" RpMaterial* lightCollisionFindMaterial(RpMaterial* material, void* data);
extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_801527A4(
    RpGeometry* geometry, RpMaterial* (*callback)(RpMaterial*, void*), void* data);

extern "C" void lightCollisionSetupColor(void)
{
	lightCollisionClump  = NULL;
	lightCollisionAtomic = NULL;
	fn_8014FFBC(lightCollisionClump, lightCollisionFindAtomic, NULL);
	lightCollisionGeometry = lightCollisionAtomic->geometry;
	lightCollisionGeometry->flags |= 0x40;
	lightCollisionMaterial = NULL;
	fn_801527A4(lightCollisionGeometry, lightCollisionFindMaterial, NULL);
	lightCollisionFrame = lightCollisionClump->frame;
	lightCollisionColor = lightCollisionMaterial->color;
}

extern "C" void lightCollisionResetColor(void)
{
	lightCollisionMaterial->color = lightCollisionColor;
	lightCollisionMaterial        = NULL;
	lightCollisionGeometry        = NULL;
	lightCollisionAtomic          = NULL;
	lightCollisionClump           = NULL;
}
