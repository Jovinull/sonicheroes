#include "types.h"

// The particle material that follows each module's cannon registration (built
// by rel/cannon_ptcl_ctor.cpp), asked for a new particle when it exists. The
// same in the thirteen stage modules that share the engine core.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

extern "C" void* cannonPtclMaterial;

extern "C" void* cannonPtclCreate(void* material, RwV3d* pos, RwV3d* speed, f32 spread, f32 floor);

extern "C" void* cannonPtclSpawn(RwV3d* pos, RwV3d* speed, f32 spread, f32 floor)
{
	if (cannonPtclMaterial == NULL) {
		return NULL;
	}
	return cannonPtclCreate(cannonPtclMaterial, pos, speed, spread, floor);
}
