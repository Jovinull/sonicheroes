#include "types.h"

// The record that registers REDWEED with the editor.
//
// The claim is .text 0x8B138 to 0x8B1F0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void redweedLoad(void);
extern "C" void redweedUnload(void);
extern "C" void redweedCreate(void);
extern "C" void redweedReset(void);
extern "C" ObjectEntry redweedEntry;
extern "C" char redweedDisplayName[];
extern "C" char redweedFieldTypes[];
extern "C" const char* redweedFieldNames[];

extern "C" void redweedRegister(void)
{
	redweedEntry.flags = 0;
	redweedEntry.unk18 = 0;

	redweedEntry.name   = redweedDisplayName;
	redweedEntry.load   = redweedLoad;
	redweedEntry.unload = redweedUnload;
	redweedEntry.create = redweedCreate;
	redweedEntry.reset  = redweedReset;

	redweedEntry.flags = 0x21000;
	redweedEntry.unk18 = 0;
	redweedEntry.unk20 = 0xa;
	redweedEntry.unk1C = 0x984;
	redweedEntry.unk1E = 2;
	redweedEntry.unk21 = 0x80;

	redweedEntry.fieldTypes = redweedFieldTypes;
	redweedEntry.fieldNames = redweedFieldNames;

	if (redweedFieldTypes != NULL) {
		redweedEntry.flags |= 8;
	} else {
		redweedEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const redweedCtorEntry)(void) = redweedRegister;
