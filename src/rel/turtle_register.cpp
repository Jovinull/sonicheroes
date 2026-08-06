#include "types.h"

// The record that registers TURTLE OBJECT with the editor.
//
// The claim is .text 0xC266C to 0xC274C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccfffif" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in four of the fourteen stage modules: 03D, 05D, 09D and 11D.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void);     // 0x10
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
extern "C" {
void* fn_80113C7C(void*);
void fn_80113C2C(void*, s16);
void __register_global_object(void*, void*, void*);
}

extern "C" void turtleObjectLoad(void);
extern "C" void turtleObjectUnload(void);
extern "C" void turtleObjectCreate(void);
extern "C" u8 turtleObjectGlobalA[];
extern "C" u8 turtleObjectGlobalAChain[];
extern "C" ObjectEntry turtleObjectEntry;
extern "C" char turtleObjectDisplayName[];
extern "C" char turtleObjectFieldTypes[];
extern "C" const char* turtleObjectFieldNames[];

extern "C" void turtleObjectRegister(void)
{
	void* a = fn_80113C7C(turtleObjectGlobalA);
	__register_global_object(a, (void*)fn_80113C2C, turtleObjectGlobalAChain);

	turtleObjectEntry.flags = 0;
	turtleObjectEntry.unk18 = 0;

	turtleObjectEntry.name   = turtleObjectDisplayName;
	turtleObjectEntry.load   = turtleObjectLoad;
	turtleObjectEntry.unload = turtleObjectUnload;
	turtleObjectEntry.create = turtleObjectCreate;
	turtleObjectEntry.reset  = NULL;

	turtleObjectEntry.flags = 0x20000;
	turtleObjectEntry.unk18 = 0;
	turtleObjectEntry.unk20 = 0x1e;
	turtleObjectEntry.unk1C = 0x1570;
	turtleObjectEntry.unk1E = 4;
	turtleObjectEntry.unk21 = 0;

	turtleObjectEntry.fieldTypes = turtleObjectFieldTypes;
	turtleObjectEntry.fieldNames = turtleObjectFieldNames;

	if (turtleObjectFieldTypes != NULL) {
		turtleObjectEntry.flags |= 8;
	} else {
		turtleObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const turtleObjectCtorEntry)(void) = turtleObjectRegister;
