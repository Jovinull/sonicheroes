#include "types.h"

// The record that registers FLIPPER with the editor.
//
// The claim is .text 0x904B4 to 0x90564 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fCcCc" is the field type string: one character per parameter the
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
extern "C" void flipperLoad(void);
extern "C" void flipperUnload(void);
extern "C" void flipperCreate(void);
extern "C" void flipperReset(void);
extern "C" ObjectEntry flipperEntry;
extern "C" char flipperDisplayName[];
extern "C" char flipperFieldTypes[];
extern "C" const char* flipperFieldNames[];

extern "C" void flipperRegister(void)
{
	flipperEntry.flags = 0;
	flipperEntry.unk18 = 0;

	flipperEntry.name   = flipperDisplayName;
	flipperEntry.load   = flipperLoad;
	flipperEntry.unload = flipperUnload;
	flipperEntry.create = flipperCreate;
	flipperEntry.reset  = flipperReset;

	flipperEntry.flags = 0x20000;
	flipperEntry.unk18 = 0;
	flipperEntry.unk20 = 0xf;
	flipperEntry.unk1C = 0x502;
	flipperEntry.unk1E = 2;
	flipperEntry.unk21 = 0;

	flipperEntry.fieldTypes = flipperFieldTypes;
	flipperEntry.fieldNames = flipperFieldNames;

	if (flipperFieldTypes != NULL) {
		flipperEntry.flags |= 8;
	} else {
		flipperEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const flipperCtorEntry)(void) = flipperRegister;
