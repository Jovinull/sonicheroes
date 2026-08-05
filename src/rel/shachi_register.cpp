#include "types.h"

// The record that registers S01 SHACHI with the editor.
//
// The claim is .text 0x8A7A8 to 0x8A854 and the .ctors word at 0xEC that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The .ctors slot follows from the order being monotonic in .text address:
// rel/o_s01_iwamizu.cpp holds 0xD8 and rel/o_s01_shachicolli.cpp holds 0xF0,
// and this record's run sits between them.
//
// Only stage01D carries this run, like the other stage-01 object records around
// it.

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
extern "C" void shachiLoad(void);
extern "C" void shachiUnload(void);
extern "C" void shachiCreate(void);
extern "C" ObjectEntry shachiEntry;
extern "C" char shachiDisplayName[];
extern "C" char shachiFieldTypes[];
extern "C" const char* shachiFieldNames[];

extern "C" void shachiRegister(void)
{
	shachiEntry.flags = 0;
	shachiEntry.unk18 = 0;

	shachiEntry.name   = shachiDisplayName;
	shachiEntry.load   = shachiLoad;
	shachiEntry.unload = shachiUnload;
	shachiEntry.create = shachiCreate;
	shachiEntry.unk10  = NULL;

	shachiEntry.flags = 0x21000;
	shachiEntry.unk18 = 0;
	shachiEntry.unk20 = 50;
	shachiEntry.unk1C = 386;
	shachiEntry.unk1E = 2;
	shachiEntry.unk21 = 0;

	shachiEntry.fieldTypes = shachiFieldTypes;
	shachiEntry.fieldNames = shachiFieldNames;

	if (shachiFieldTypes != NULL) {
		shachiEntry.flags |= 8;
	} else {
		shachiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const shachiCtorEntry)(void) = shachiRegister;
