#include "types.h"

// endObjBobsleigh_Sub (the PS2 build's name): the bobsleigh objects' shared
// unload. It forgets the stop and signal models, their materials and the eight
// textures the loader (initObjBobsleigh_Sub) found; the stage resource manager
// owns them.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;

extern "C" RpClump* bobStopClump;
extern "C" RpClump* bobSignalClump;
extern "C" RpMaterial* bobStopMaterial;
extern "C" RpMaterial* bobStopSignalMaterial;
extern "C" RpMaterial* bobSignalMaterial;
extern "C" RpMaterial* bobSignalFirstMaterial;
extern "C" RpMaterial* bobSignalShadeMaterial;
extern "C" RwTexture* bobsleighTexture0;
extern "C" RwTexture* bobsleighTexture1;
extern "C" RwTexture* bobsleighTexture2;
extern "C" RwTexture* bobsleighTexture3;
extern "C" RwTexture* bobsleighTexture4;
extern "C" RwTexture* bobsleighTexture5;
extern "C" RwTexture* bobsleighTexture6;
extern "C" RwTexture* bobsleighTexture7;

void endObjBobsleigh_Sub()
{
	bobStopClump           = NULL;
	bobSignalClump         = NULL;
	bobStopMaterial        = NULL;
	bobStopSignalMaterial  = NULL;
	bobSignalMaterial      = NULL;
	bobSignalFirstMaterial = NULL;
	bobSignalShadeMaterial = NULL;
	bobsleighTexture0      = NULL;
	bobsleighTexture1      = NULL;
	bobsleighTexture2      = NULL;
	bobsleighTexture6      = NULL;
	bobsleighTexture7      = NULL;
	bobsleighTexture3      = NULL;
	bobsleighTexture4      = NULL;
	bobsleighTexture5      = NULL;
}
