#include "types.h"

// The record that registers LASERFENCE OBJECT with the editor.
//
// The claim is .text 0x1C3E0 to 0x1C488 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iffi" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void laserfenceObjectLoad(void);
extern "C" void laserfenceObjectUnload(void);
extern "C" void laserfenceObjectCreate(void);
extern "C" ObjectEntry laserfenceObjectEntry;
extern "C" char laserfenceObjectDisplayName[];
extern "C" char laserfenceObjectFieldTypes[];
extern "C" const char* laserfenceObjectFieldNames[];

extern "C" void laserfenceObjectRegister(void)
{
	laserfenceObjectEntry.flags = 0;
	laserfenceObjectEntry.unk18 = 0;

	laserfenceObjectEntry.name   = laserfenceObjectDisplayName;
	laserfenceObjectEntry.load   = laserfenceObjectLoad;
	laserfenceObjectEntry.unload = laserfenceObjectUnload;
	laserfenceObjectEntry.create = laserfenceObjectCreate;
	laserfenceObjectEntry.reset  = NULL;

	laserfenceObjectEntry.flags = 0x20000;
	laserfenceObjectEntry.unk18 = 0;
	laserfenceObjectEntry.unk20 = 0x1e;
	laserfenceObjectEntry.unk1C = 0x16;
	laserfenceObjectEntry.unk1E = 2;
	laserfenceObjectEntry.unk21 = 0;

	laserfenceObjectEntry.fieldTypes = laserfenceObjectFieldTypes;
	laserfenceObjectEntry.fieldNames = laserfenceObjectFieldNames;

	if (laserfenceObjectFieldTypes != NULL) {
		laserfenceObjectEntry.flags |= 8;
	} else {
		laserfenceObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const laserfenceObjectCtorEntry)(void)
    = laserfenceObjectRegister;
