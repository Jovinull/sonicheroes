#include "types.h"

// TObjSwitch's asset loader. It registers the six state names against the
// resource heap, loads the switch model, then walks the same six names until it
// finds the one this stage's model actually carries, and finally picks up the
// panel's own draw and material.
//
// The claim is .text 0x4C90 to 0x4E50. The strings, the six-entry name table
// and the eleven bss words stay in each module's data and are renamed to the
// shared names below. The code is identical in the thirteen stage modules that
// share the engine core; stage40D is a different revision and is left out.
//
// The six words the first block fills are never read back in this unit or in
// the unload hook, so "handle" is a descriptive guess: what is established is
// that fn_801A4BBC takes the resource heap and one of the six state names and
// that its result is kept per state. The state names themselves are the
// evidence for the on/off numbering.
//
// The search loop is a while, not a do-while: the compiler jumps to the test
// before the first iteration. It also reads each name once into a register and
// uses it for both lookups, and reloads switchModel from memory for each call
// rather than keeping it live.

extern "C" void* fn_8005EC0C(void);
extern "C" void* fn_801A4BBC(void* heap, const char* name);
extern "C" void* fn_8005E1DC(void* model, s32 index, const char* name);
extern "C" void* fn_8005E410(void* model, s32 index, const char* name);
extern "C" void* fn_8005EA04(const char* name);

extern "C" const char* switchStateNames[6];
extern "C" char switchPanelNodeName[];
extern "C" char switchPanelMaterialName[];
extern "C" char switchModelName[];

extern "C" void* switchModel;
extern "C" void* switchPanelDraw;
extern "C" void* switchStateDraw;
extern "C" void* switchStateMaterial;
extern "C" void* switchPanelMaterial;

extern "C" void* switchOnHandle;
extern "C" void* switchOn2Handle;
extern "C" void* switchOn3Handle;
extern "C" void* switchOffHandle;
extern "C" void* switchOff2Handle;
extern "C" void* switchOff3Handle;

extern "C" void switchLoad(void)
{
	void* heap = fn_8005EC0C();

	switchOnHandle   = fn_801A4BBC(heap, switchStateNames[0]);
	switchOn2Handle  = fn_801A4BBC(heap, switchStateNames[1]);
	switchOn3Handle  = fn_801A4BBC(heap, switchStateNames[2]);
	switchOffHandle  = fn_801A4BBC(heap, switchStateNames[3]);
	switchOff2Handle = fn_801A4BBC(heap, switchStateNames[4]);
	switchOff3Handle = fn_801A4BBC(heap, switchStateNames[5]);

	switchModel         = fn_8005EA04(switchModelName);
	switchStateMaterial = NULL;

	if (switchModel != NULL) {
		for (s32 i = 0; switchStateMaterial == NULL; i++) {
			const char* name = switchStateNames[i];

			switchStateDraw     = fn_8005E1DC(switchModel, 0, name);
			switchStateMaterial = fn_8005E410(switchModel, 0, name);
		}

		switchPanelDraw     = fn_8005E1DC(switchModel, 0, switchPanelNodeName);
		switchPanelMaterial = fn_8005E410(switchModel, 0, switchPanelMaterialName);
	}
}
