#include "types.h"

// TObjSwitch's unload hook. It clears the model and the four draw and material
// slots the loader fills in.
//
// The claim is .text 0x4C4C to 0x4C90 and nothing else. The five words stay in
// each module's bss and are renamed to the shared names below. The six state
// handles the loader also writes are not cleared here, which is why they are
// not named in this unit.
//
// The code is identical in the thirteen stage modules that share the engine
// core; stage40D is a different revision and is left out, as everywhere else.

extern "C" void* switchModel;
extern "C" void* switchPanelDraw;
extern "C" void* switchStateDraw;
extern "C" void* switchStateMaterial;
extern "C" void* switchPanelMaterial;

extern "C" void switchUnload(void)
{
	switchModel         = NULL;
	switchPanelDraw     = NULL;
	switchStateDraw     = NULL;
	switchStateMaterial = NULL;
	switchPanelMaterial = NULL;
}
