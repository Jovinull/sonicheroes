#include "types.h"

// The record that registers S03 BaloonWK with the editor.
//
// The claim is .text 0x75878 to 0x75920 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s03BaloonWKLoad(void);
extern "C" void s03BaloonWKUnload(void);
extern "C" void s03BaloonWKCreate(void);
extern "C" ObjectEntry s03BaloonWKEntry;
extern "C" char s03BaloonWKDisplayName[];
extern "C" char s03BaloonWKFieldTypes[];
extern "C" const char* s03BaloonWKFieldNames[];

extern "C" void s03BaloonWKRegister(void)
{
	s03BaloonWKEntry.flags = 0;
	s03BaloonWKEntry.unk18 = 0;

	s03BaloonWKEntry.name   = s03BaloonWKDisplayName;
	s03BaloonWKEntry.load   = s03BaloonWKLoad;
	s03BaloonWKEntry.unload = s03BaloonWKUnload;
	s03BaloonWKEntry.create = s03BaloonWKCreate;
	s03BaloonWKEntry.reset  = NULL;

	s03BaloonWKEntry.flags = 0x20000;
	s03BaloonWKEntry.unk18 = 0;
	s03BaloonWKEntry.unk20 = 0x14;
	s03BaloonWKEntry.unk1C = 0x307;
	s03BaloonWKEntry.unk1E = 2;
	s03BaloonWKEntry.unk21 = 0;

	s03BaloonWKEntry.fieldTypes = s03BaloonWKFieldTypes;
	s03BaloonWKEntry.fieldNames = s03BaloonWKFieldNames;

	if (s03BaloonWKFieldTypes != NULL) {
		s03BaloonWKEntry.flags |= 8;
	} else {
		s03BaloonWKEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03BaloonWKCtorEntry)(void) = s03BaloonWKRegister;
