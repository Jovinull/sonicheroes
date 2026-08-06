#include "types.h"

// The record that registers XXXSIGN with the editor.
//
// The claim is .text 0x9EB2C to 0x9EBDC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void xxxsignLoad(void);
extern "C" void xxxsignUnload(void);
extern "C" void xxxsignCreate(void);
extern "C" void xxxsignReset(void);
extern "C" ObjectEntry xxxsignEntry;
extern "C" char xxxsignDisplayName[];
extern "C" char xxxsignFieldTypes[];
extern "C" const char* xxxsignFieldNames[];

extern "C" void xxxsignRegister(void)
{
	xxxsignEntry.flags = 0;
	xxxsignEntry.unk18 = 0;

	xxxsignEntry.name   = xxxsignDisplayName;
	xxxsignEntry.load   = xxxsignLoad;
	xxxsignEntry.unload = xxxsignUnload;
	xxxsignEntry.create = xxxsignCreate;
	xxxsignEntry.reset  = xxxsignReset;

	xxxsignEntry.flags = 0x20000;
	xxxsignEntry.unk18 = 0;
	xxxsignEntry.unk20 = 0xf;
	xxxsignEntry.unk1C = 0x580;
	xxxsignEntry.unk1E = 2;
	xxxsignEntry.unk21 = 0;

	xxxsignEntry.fieldTypes = xxxsignFieldTypes;
	xxxsignEntry.fieldNames = xxxsignFieldNames;

	if (xxxsignFieldTypes != NULL) {
		xxxsignEntry.flags |= 8;
	} else {
		xxxsignEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const xxxsignCtorEntry)(void) = xxxsignRegister;
