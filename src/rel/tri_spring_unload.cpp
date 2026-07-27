#include "types.h"

// TObj3Spring's unload hook. It clears the four model, draw and material
// slots populated by the loader.
//
// The claim is .text 0x2CD0 to 0x2D20 and nothing else. The three arrays stay
// in each module's data section and are renamed to the shared names below.
// The code is identical in all thirteen stage modules that share the engine
// core; stage40D is a different revision and is left out.

extern "C" void* triSpringModels[4];
extern "C" void* triSpringDraws[4];
extern "C" void* triSpringMaterials[4];

extern "C" void triSpringUnload(void)
{
	triSpringModels[0]    = NULL;
	triSpringDraws[0]     = NULL;
	triSpringMaterials[0] = NULL;

	triSpringModels[1]    = NULL;
	triSpringDraws[1]     = NULL;
	triSpringMaterials[1] = NULL;

	triSpringModels[2]    = NULL;
	triSpringDraws[2]     = NULL;
	triSpringMaterials[2] = NULL;

	triSpringModels[3]    = NULL;
	triSpringDraws[3]     = NULL;
	triSpringMaterials[3] = NULL;
}
