#include "types.h"

// The record that registers WALL OBJECT with the editor.
//
// The claim is .text 0xC13F8 to 0xC14D8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccffffiff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in three of the fourteen stage modules: 09D, 11D and 13D.

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

extern "C" void wallObjectLoad(void);
extern "C" void wallObjectUnload(void);
extern "C" void wallObjectCreate(void);
extern "C" u8 wallObjectGlobalA[];
extern "C" u8 wallObjectGlobalAChain[];
extern "C" ObjectEntry wallObjectEntry;
extern "C" char wallObjectDisplayName[];
extern "C" char wallObjectFieldTypes[];
extern "C" const char* wallObjectFieldNames[];

extern "C" void wallObjectRegister(void)
{
	void* a = fn_80113C7C(wallObjectGlobalA);
	__register_global_object(a, (void*)fn_80113C2C, wallObjectGlobalAChain);

	wallObjectEntry.flags = 0;
	wallObjectEntry.unk18 = 0;

	wallObjectEntry.name   = wallObjectDisplayName;
	wallObjectEntry.load   = wallObjectLoad;
	wallObjectEntry.unload = wallObjectUnload;
	wallObjectEntry.create = wallObjectCreate;
	wallObjectEntry.reset  = NULL;

	wallObjectEntry.flags = 0x20000;
	wallObjectEntry.unk18 = 0;
	wallObjectEntry.unk20 = 0x1e;
	wallObjectEntry.unk1C = 0x1540;
	wallObjectEntry.unk1E = 4;
	wallObjectEntry.unk21 = 0;

	wallObjectEntry.fieldTypes = wallObjectFieldTypes;
	wallObjectEntry.fieldNames = wallObjectFieldNames;

	if (wallObjectFieldTypes != NULL) {
		wallObjectEntry.flags |= 8;
	} else {
		wallObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const wallObjectCtorEntry)(void) = wallObjectRegister;
