#include "types.h"

// The record that registers DFAN with the editor.
//
// The claim is .text 0x79E08 to 0x79EB8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void dfanLoad(void);
extern "C" void dfanUnload(void);
extern "C" void dfanCreate(void);
extern "C" void dfanReset(void);
extern "C" ObjectEntry dfanEntry;
extern "C" char dfanDisplayName[];
extern "C" char dfanFieldTypes[];
extern "C" const char* dfanFieldNames[];

extern "C" void dfanRegister(void)
{
	dfanEntry.flags = 0;
	dfanEntry.unk18 = 0;

	dfanEntry.name   = dfanDisplayName;
	dfanEntry.load   = dfanLoad;
	dfanEntry.unload = dfanUnload;
	dfanEntry.create = dfanCreate;
	dfanEntry.reset  = dfanReset;

	dfanEntry.flags = 0x1000;
	dfanEntry.unk18 = 0;
	dfanEntry.unk20 = 0xf;
	dfanEntry.unk1C = 0x780;
	dfanEntry.unk1E = 2;
	dfanEntry.unk21 = 0;

	dfanEntry.fieldTypes = dfanFieldTypes;
	dfanEntry.fieldNames = dfanFieldNames;

	if (dfanFieldTypes != NULL) {
		dfanEntry.flags |= 8;
	} else {
		dfanEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const dfanCtorEntry)(void) = dfanRegister;
