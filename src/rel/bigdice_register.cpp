#include "types.h"

// The record that registers BIGDICE with the editor.
//
// The claim is .text 0x8530C to 0x853BC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iiFi" is the field type string: one character per parameter the
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
extern "C" void bigdiceLoad(void);
extern "C" void bigdiceUnload(void);
extern "C" void bigdiceCreate(void);
extern "C" void bigdiceReset(void);
extern "C" ObjectEntry bigdiceEntry;
extern "C" char bigdiceDisplayName[];
extern "C" char bigdiceFieldTypes[];
extern "C" const char* bigdiceFieldNames[];

extern "C" void bigdiceRegister(void)
{
	bigdiceEntry.flags = 0;
	bigdiceEntry.unk18 = 0;

	bigdiceEntry.name   = bigdiceDisplayName;
	bigdiceEntry.load   = bigdiceLoad;
	bigdiceEntry.unload = bigdiceUnload;
	bigdiceEntry.create = bigdiceCreate;
	bigdiceEntry.reset  = bigdiceReset;

	bigdiceEntry.flags = 0x1000;
	bigdiceEntry.unk18 = 0;
	bigdiceEntry.unk20 = 0xf;
	bigdiceEntry.unk1C = 0x584;
	bigdiceEntry.unk1E = 2;
	bigdiceEntry.unk21 = 0;

	bigdiceEntry.fieldTypes = bigdiceFieldTypes;
	bigdiceEntry.fieldNames = bigdiceFieldNames;

	if (bigdiceFieldTypes != NULL) {
		bigdiceEntry.flags |= 8;
	} else {
		bigdiceEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigdiceCtorEntry)(void) = bigdiceRegister;
