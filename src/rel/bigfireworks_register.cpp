#include "types.h"

// The record that registers BIGFIREWORKS with the editor.
//
// The claim is .text 0x86484 to 0x86534 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iFFFFi" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void bigfireworksLoad(void);
extern "C" void bigfireworksUnload(void);
extern "C" void bigfireworksCreate(void);
extern "C" void bigfireworksReset(void);
extern "C" ObjectEntry bigfireworksEntry;
extern "C" char bigfireworksDisplayName[];
extern "C" char bigfireworksFieldTypes[];
extern "C" const char* bigfireworksFieldNames[];

extern "C" void bigfireworksRegister(void)
{
	bigfireworksEntry.flags = 0;
	bigfireworksEntry.unk18 = 0;

	bigfireworksEntry.name   = bigfireworksDisplayName;
	bigfireworksEntry.load   = bigfireworksLoad;
	bigfireworksEntry.unload = bigfireworksUnload;
	bigfireworksEntry.create = bigfireworksCreate;
	bigfireworksEntry.reset  = bigfireworksReset;

	bigfireworksEntry.flags = 0x1000;
	bigfireworksEntry.unk18 = 0;
	bigfireworksEntry.unk20 = 0xf;
	bigfireworksEntry.unk1C = 0x583;
	bigfireworksEntry.unk1E = 2;
	bigfireworksEntry.unk21 = 0;

	bigfireworksEntry.fieldTypes = bigfireworksFieldTypes;
	bigfireworksEntry.fieldNames = bigfireworksFieldNames;

	if (bigfireworksFieldTypes != NULL) {
		bigfireworksEntry.flags |= 8;
	} else {
		bigfireworksEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigfireworksCtorEntry)(void) = bigfireworksRegister;
