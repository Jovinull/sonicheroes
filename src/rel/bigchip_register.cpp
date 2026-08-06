#include "types.h"

// The record that registers BIGCHIP with the editor.
//
// The claim is .text 0x842DC to 0x8438C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fii" is the field type string: one character per parameter the
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
extern "C" void bigchipLoad(void);
extern "C" void bigchipUnload(void);
extern "C" void bigchipCreate(void);
extern "C" void bigchipReset(void);
extern "C" ObjectEntry bigchipEntry;
extern "C" char bigchipDisplayName[];
extern "C" char bigchipFieldTypes[];
extern "C" const char* bigchipFieldNames[];

extern "C" void bigchipRegister(void)
{
	bigchipEntry.flags = 0;
	bigchipEntry.unk18 = 0;

	bigchipEntry.name   = bigchipDisplayName;
	bigchipEntry.load   = bigchipLoad;
	bigchipEntry.unload = bigchipUnload;
	bigchipEntry.create = bigchipCreate;
	bigchipEntry.reset  = bigchipReset;

	bigchipEntry.flags = 0x1000;
	bigchipEntry.unk18 = 0;
	bigchipEntry.unk20 = 0xf;
	bigchipEntry.unk1C = 0x587;
	bigchipEntry.unk1E = 2;
	bigchipEntry.unk21 = 0;

	bigchipEntry.fieldTypes = bigchipFieldTypes;
	bigchipEntry.fieldNames = bigchipFieldNames;

	if (bigchipFieldTypes != NULL) {
		bigchipEntry.flags |= 8;
	} else {
		bigchipEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigchipCtorEntry)(void) = bigchipRegister;
