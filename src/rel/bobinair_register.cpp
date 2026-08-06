#include "types.h"

// The record that registers BOBINAIR with the editor.
//
// The claim is .text 0x89E4C to 0x89EFC and the .ctors word that names it.
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
extern "C" void bobinairLoad(void);
extern "C" void bobinairUnload(void);
extern "C" void bobinairCreate(void);
extern "C" void bobinairReset(void);
extern "C" ObjectEntry bobinairEntry;
extern "C" char bobinairDisplayName[];
extern "C" char bobinairFieldTypes[];
extern "C" const char* bobinairFieldNames[];

extern "C" void bobinairRegister(void)
{
	bobinairEntry.flags = 0;
	bobinairEntry.unk18 = 0;

	bobinairEntry.name   = bobinairDisplayName;
	bobinairEntry.load   = bobinairLoad;
	bobinairEntry.unload = bobinairUnload;
	bobinairEntry.create = bobinairCreate;
	bobinairEntry.reset  = bobinairReset;

	bobinairEntry.flags = 0x20000;
	bobinairEntry.unk18 = 0;
	bobinairEntry.unk20 = 0xf;
	bobinairEntry.unk1C = 0x501;
	bobinairEntry.unk1E = 2;
	bobinairEntry.unk21 = 0;

	bobinairEntry.fieldTypes = bobinairFieldTypes;
	bobinairEntry.fieldNames = bobinairFieldNames;

	if (bobinairFieldTypes != NULL) {
		bobinairEntry.flags |= 8;
	} else {
		bobinairEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bobinairCtorEntry)(void) = bobinairRegister;
