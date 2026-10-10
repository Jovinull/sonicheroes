// The unload hook rel/formgate_register.cpp puts in the formation gate's editor
// record, in the thirteen stage modules that share it: it forgets the models
// and materials the load (still assembly) reads; the stage resource manager
// owns them.

#include "types.h"

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" RpClump* formgateObjectModel;
extern "C" RpMaterial* formgateObjectMaterial;
extern "C" RpMaterial* formgateObjectMaterials[3];
extern "C" RpClump* formgateObjectShade;
extern "C" RpMaterial* formgateObjectShadeMaterial;
extern "C" RpClump* formgateObjectBeam;
extern "C" RpMaterial* formgateObjectBeamMaterial;
extern "C" RpClump* formgateObjectBeamUV;

extern "C" void formgateObjectUnload(void)
{
	formgateObjectModel         = NULL;
	formgateObjectShade         = NULL;
	formgateObjectBeam          = NULL;
	formgateObjectMaterial      = NULL;
	formgateObjectShadeMaterial = NULL;
	formgateObjectBeamMaterial  = NULL;
	formgateObjectMaterials[0]  = NULL;
	formgateObjectMaterials[1]  = NULL;
	formgateObjectMaterials[2]  = NULL;
	formgateObjectBeamUV        = NULL;
}
