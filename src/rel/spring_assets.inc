#include "types.h"

// TObjSpring's asset hooks and its factory: load the model and the material the
// display pass tints, drop them again, and allocate one spring.
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else.
//
// The factory here is the shape sample2Create and the sample1 factory are not:
// it calls the constructor rather than having it inlined, so the allocator's
// result stays in one register and the whole thing falls out in four lines. The
// other two inline the constructor of a class with two bases, which spends an
// instruction on a register copy; see rel/sample1_create.cpp.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" u8* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    void* model, s32 index, const char* name);
extern "C" void* objPointerReadFromClumpAnim__FPc(const char* name);

// The record the module registers the class with. The editor reads the last two
// fields to lay out the class's parameters: one character per field saying what
// type it is, and one label each. "fsf" is a float, a halfword and a float,
// which is the power, the no control time and the guide line.
typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	s16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
} ObjectEntry;               // 0x2C

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* springCtor(void* object, void* owner);
extern "C" ObjectEntry springEntry;
extern "C" char springDisplayName[];
extern "C" char springFieldTypes[];
extern "C" const char* springFieldNames[];
extern "C" void* springModel;
extern "C" u8* springMaterial;
extern "C" char springModelName[];
extern "C" char springTextureName[];
extern "C" void springUnload(void);
extern "C" void springLoad(void);
extern "C" void springCreate(void);

// Fills the record in and hands it to the editor. The module's .ctors list
// names this, so it runs before the stage does.
extern "C" void springRegister(void)
{
	springEntry.flags = 0;
	springEntry.unk18 = 0;

	springEntry.name   = springDisplayName;
	springEntry.load   = springLoad;
	springEntry.unload = springUnload;
	springEntry.create = springCreate;
	springEntry.unk10  = NULL;

	springEntry.flags = 0x20000;
	springEntry.unk18 = 0;
	springEntry.unk20 = 0x1E;
	springEntry.unk1C = 1;
	springEntry.unk1E = 2;
	springEntry.unk21 = 0;

	springEntry.fieldTypes = springFieldTypes;
	springEntry.fieldNames = springFieldNames;

	if (springFieldTypes != NULL) {
		springEntry.flags |= 8;
	} else {
		springEntry.flags &= ~8;
	}
}

extern "C" void springCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		springCtor(memory, lbl_8042C110);
	}
}

extern "C" void springLoad(void)
{
	void* model = objPointerReadFromClumpAnim__FPc(springModelName);

	springModel = model;
	if (model != NULL) {
		springMaterial = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
		    model, 0, springTextureName);
	}
}

extern "C" void springUnload(void)
{
	springModel    = NULL;
	springMaterial = NULL;
}

// The .ctors word that names the function above. The compiler only emits one
// for a real static constructor, and a static constructor would be given a
// generated name the module cannot refer to, so the entry is placed by hand.
__declspec(section ".ctors") void (*const springCtorEntry)(void) = springRegister;
