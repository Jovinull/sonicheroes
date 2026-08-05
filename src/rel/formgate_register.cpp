#include "types.h"

// The record that registers FORMGATE OBJECT with the editor.
//
// The claim is .text 0x61848 to 0x618F0 and the .ctors word at 0xB0 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The flags word is 0x20000, small enough for one instruction, which is the
// whole difference from rel/s66_star_register.cpp's two-instruction load.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void formgateObjectLoad(void);
extern "C" void formgateObjectUnload(void);
extern "C" void formgateObjectCreate(void);
extern "C" ObjectEntry formgateObjectEntry;
extern "C" char formgateObjectDisplayName[];
extern "C" char formgateObjectFieldTypes[];
extern "C" const char* formgateObjectFieldNames[];

extern "C" void formgateObjectRegister(void)
{
	formgateObjectEntry.flags = 0;
	formgateObjectEntry.unk18 = 0;

	formgateObjectEntry.name   = formgateObjectDisplayName;
	formgateObjectEntry.load   = formgateObjectLoad;
	formgateObjectEntry.unload = formgateObjectUnload;
	formgateObjectEntry.create = formgateObjectCreate;
	formgateObjectEntry.unk10  = NULL;

	formgateObjectEntry.flags = 0x20000;
	formgateObjectEntry.unk18 = 0;
	formgateObjectEntry.unk20 = 30;
	formgateObjectEntry.unk1C = 38;
	formgateObjectEntry.unk1E = 2;
	formgateObjectEntry.unk21 = 0;

	formgateObjectEntry.fieldTypes = formgateObjectFieldTypes;
	formgateObjectEntry.fieldNames = formgateObjectFieldNames;

	if (formgateObjectFieldTypes != NULL) {
		formgateObjectEntry.flags |= 8;
	} else {
		formgateObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const formgateObjectCtorEntry)(void) = formgateObjectRegister;
