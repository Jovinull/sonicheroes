#include "types.h"

// The record that registers BOBIN with the editor.
//
// The claim is .text 0x88C54 to 0x88D04 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FF" is the field type string: one character per parameter the
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
extern "C" void bobinLoad(void);
extern "C" void bobinUnload(void);
extern "C" void bobinCreate(void);
extern "C" void bobinReset(void);
extern "C" ObjectEntry bobinEntry;
extern "C" char bobinDisplayName[];
extern "C" char bobinFieldTypes[];
extern "C" const char* bobinFieldNames[];

extern "C" void bobinRegister(void)
{
	bobinEntry.flags = 0;
	bobinEntry.unk18 = 0;

	bobinEntry.name   = bobinDisplayName;
	bobinEntry.load   = bobinLoad;
	bobinEntry.unload = bobinUnload;
	bobinEntry.create = bobinCreate;
	bobinEntry.reset  = bobinReset;

	bobinEntry.flags = 0x20000;
	bobinEntry.unk18 = 0;
	bobinEntry.unk20 = 0xf;
	bobinEntry.unk1C = 0x500;
	bobinEntry.unk1E = 2;
	bobinEntry.unk21 = 0;

	bobinEntry.fieldTypes = bobinFieldTypes;
	bobinEntry.fieldNames = bobinFieldNames;

	if (bobinFieldTypes != NULL) {
		bobinEntry.flags |= 8;
	} else {
		bobinEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bobinCtorEntry)(void) = bobinRegister;
