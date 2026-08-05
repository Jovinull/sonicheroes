#include "types.h"

// The record that registers S01 Kamome with the editor.
//
// The claim is .text 0x84518 to 0x845C4 and the .ctors word at 0xDC that names
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
extern "C" void kamomeLoad(void);
extern "C" void kamomeUnload(void);
extern "C" void kamomeCreate(void);
extern "C" ObjectEntry kamomeEntry;
extern "C" char kamomeDisplayName[];
extern "C" char kamomeFieldTypes[];
extern "C" const char* kamomeFieldNames[];

extern "C" void kamomeRegister(void)
{
	kamomeEntry.flags = 0;
	kamomeEntry.unk18 = 0;

	kamomeEntry.name   = kamomeDisplayName;
	kamomeEntry.load   = kamomeLoad;
	kamomeEntry.unload = kamomeUnload;
	kamomeEntry.create = kamomeCreate;
	kamomeEntry.unk10  = NULL;

	kamomeEntry.flags = 0x21000;
	kamomeEntry.unk18 = 0;
	kamomeEntry.unk20 = 100;
	kamomeEntry.unk1C = 387;
	kamomeEntry.unk1E = 2;
	kamomeEntry.unk21 = 0;

	kamomeEntry.fieldTypes = kamomeFieldTypes;
	kamomeEntry.fieldNames = kamomeFieldNames;

	if (kamomeFieldTypes != NULL) {
		kamomeEntry.flags |= 8;
	} else {
		kamomeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const kamomeCtorEntry)(void) = kamomeRegister;
