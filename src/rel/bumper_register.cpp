#include "types.h"

// The record that registers BUMPER with the editor.
//
// The claim is .text 0x8B5B8 to 0x8B668 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iif" is the field type string: one character per parameter the
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
extern "C" void bumperLoad(void);
extern "C" void bumperUnload(void);
extern "C" void bumperCreate(void);
extern "C" void bumperReset(void);
extern "C" ObjectEntry bumperEntry;
extern "C" char bumperDisplayName[];
extern "C" char bumperFieldTypes[];
extern "C" const char* bumperFieldNames[];

extern "C" void bumperRegister(void)
{
	bumperEntry.flags = 0;
	bumperEntry.unk18 = 0;

	bumperEntry.name   = bumperDisplayName;
	bumperEntry.load   = bumperLoad;
	bumperEntry.unload = bumperUnload;
	bumperEntry.create = bumperCreate;
	bumperEntry.reset  = bumperReset;

	bumperEntry.flags = 0x20000;
	bumperEntry.unk18 = 0;
	bumperEntry.unk20 = 0xf;
	bumperEntry.unk1C = 0x506;
	bumperEntry.unk1E = 2;
	bumperEntry.unk21 = 0;

	bumperEntry.fieldTypes = bumperFieldTypes;
	bumperEntry.fieldNames = bumperFieldNames;

	if (bumperFieldTypes != NULL) {
		bumperEntry.flags |= 8;
	} else {
		bumperEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bumperCtorEntry)(void) = bumperRegister;
