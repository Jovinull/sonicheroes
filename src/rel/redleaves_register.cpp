#include "types.h"

// The record that registers REDLEAVES with the editor.
//
// The claim is .text 0x98EF8 to 0x98FA8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void redleavesLoad(void);
extern "C" void redleavesUnload(void);
extern "C" void redleavesCreate(void);
extern "C" void redleavesReset(void);
extern "C" ObjectEntry redleavesEntry;
extern "C" char redleavesDisplayName[];
extern "C" char redleavesFieldTypes[];
extern "C" const char* redleavesFieldNames[];

extern "C" void redleavesRegister(void)
{
	redleavesEntry.flags = 0;
	redleavesEntry.unk18 = 0;

	redleavesEntry.name   = redleavesDisplayName;
	redleavesEntry.load   = redleavesLoad;
	redleavesEntry.unload = redleavesUnload;
	redleavesEntry.create = redleavesCreate;
	redleavesEntry.reset  = redleavesReset;

	redleavesEntry.flags = 0x20000;
	redleavesEntry.unk18 = 0;
	redleavesEntry.unk20 = 0xa;
	redleavesEntry.unk1C = 0x990;
	redleavesEntry.unk1E = 2;
	redleavesEntry.unk21 = 0;

	redleavesEntry.fieldTypes = redleavesFieldTypes;
	redleavesEntry.fieldNames = redleavesFieldNames;

	if (redleavesFieldTypes != NULL) {
		redleavesEntry.flags |= 8;
	} else {
		redleavesEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const redleavesCtorEntry)(void) = redleavesRegister;
