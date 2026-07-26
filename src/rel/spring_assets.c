#include "types.h"

// TObjSpring's asset hooks and its factory: load the model and the material the
// display pass tints, drop them again, and allocate one spring.
//
// The claim is .text 0x1734 to 0x17F4 and nothing else. Everything these three
// touch is either a DOL symbol or one of the module's own blocks reached as an
// external, so there is no data to take: the two name strings and the model
// pointer are shared with the constructor at 0x1500, which is still assembly.
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else.
//
// The factory here is the shape sample2Create and the sample1 factory are not:
// it calls the constructor rather than having it inlined, so the allocator's
// result stays in one register and the whole thing falls out in four lines. The
// other two spend an instruction on a copy no source form reproduces, which is
// why they are still assembly.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);
extern "C" u8* fn_8005E410(void* model, s32 index, const char* name);
extern "C" void* fn_8005EA04(const char* name);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* springCtor(void* object, void* owner);
extern "C" void* springModel;
extern "C" u8* springMaterial;
extern "C" char springModelName[];
extern "C" char springTextureName[];

extern "C" void springUnload(void)
{
	springModel    = NULL;
	springMaterial = NULL;
}

extern "C" void springLoad(void)
{
	void* model = fn_8005EA04(springModelName);

	springModel = model;
	if (model != NULL) {
		springMaterial = fn_8005E410(model, 0, springTextureName);
	}
}

extern "C" void springCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		springCtor(memory, lbl_8042C110);
	}
}
