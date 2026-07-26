#include "types.h"

// TObj3Spring's factory and the record that registers the class.
//
// The claim is .text 0x2ED4 to 0x2FC8 and the .ctors word that names the
// registration. It stops there rather than carrying on: what follows is the
// adjustor thunk into the parameter guard, and a tail call is not something the
// compiler emits from C.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// Like the switch, this class uses the fourth hook slot, and its label array is
// the one the parameter guard at 0x2BA8 keeps up to date. That guard is still
// assembly: one of the four limits it reads is shared with a function outside
// any cut that could take it, so the constants are not this unit's to claim.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void*);    // 0x10
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

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* triSpringCtor(void* object, void* owner);
extern "C" void triSpringLoad(void);
extern "C" void triSpringUnload(void);
extern "C" void triSpringReset(void* object);
extern "C" ObjectEntry triSpringEntry;
extern "C" char triSpringDisplayName[];
extern "C" char triSpringFieldTypes[];
extern "C" const char* triSpringLabels[];

extern "C" void triSpringCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0x110);

	if (memory != NULL) {
		triSpringCtor(memory, lbl_8042C110);
	}
}

extern "C" void triSpringRegister(void)
{
	triSpringEntry.flags = 0;
	triSpringEntry.unk18 = 0;

	triSpringEntry.name   = triSpringDisplayName;
	triSpringEntry.load   = triSpringLoad;
	triSpringEntry.unload = triSpringUnload;
	triSpringEntry.create = triSpringCreate;
	triSpringEntry.reset  = triSpringReset;

	triSpringEntry.flags = 0x8020000;
	triSpringEntry.unk18 = 0;
	triSpringEntry.unk20 = 0x1E;
	triSpringEntry.unk1C = 2;
	triSpringEntry.unk1E = 2;
	triSpringEntry.unk21 = 0;

	triSpringEntry.fieldTypes = triSpringFieldTypes;
	triSpringEntry.fieldNames = triSpringLabels;

	if (triSpringFieldTypes != NULL) {
		triSpringEntry.flags |= 8;
	} else {
		triSpringEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const triSpringCtorEntry)(void) = triSpringRegister;
