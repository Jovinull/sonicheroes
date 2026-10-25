#include "types.h"

// Two callbacks of the light collision setup, the same in the twelve stage
// modules that share the engine core: walking a model's materials and atomics,
// they keep the first one met (lightCollisionMaterial, lightCollisionAtomic)
// and hand each one back so the walk goes on.

typedef struct RpMaterial RpMaterial;
typedef struct RpAtomic RpAtomic;

extern "C" RpMaterial* lightCollisionMaterial;
extern "C" RpAtomic* lightCollisionAtomic;

extern "C" RpMaterial* lightCollisionFindMaterial(RpMaterial* material, void* data)
{
	if (lightCollisionMaterial == NULL) {
		lightCollisionMaterial = material;
	}
	return material;
}

extern "C" RpAtomic* lightCollisionFindAtomic(RpAtomic* atomic, void* data)
{
	if (lightCollisionAtomic == NULL) {
		lightCollisionAtomic = atomic;
	}
	return atomic;
}
