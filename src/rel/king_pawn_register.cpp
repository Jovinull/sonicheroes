#include "types.h"

// The record that registers KING PAWN with the editor.
//
// The claim is .text 0x6B1F0 to 0x6B29C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage26D carries this run.

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
extern "C" void kingPawnLoad(void);
extern "C" void kingPawnUnload(void);
extern "C" void kingPawnCreate(void);
extern "C" ObjectEntry kingPawnEntry;
extern "C" char kingPawnDisplayName[];
extern "C" char kingPawnFieldTypes[];
extern "C" const char* kingPawnFieldNames[];

extern "C" void kingPawnRegister(void)
{
	kingPawnEntry.flags = 0;
	kingPawnEntry.unk18 = 0;

	kingPawnEntry.name   = kingPawnDisplayName;
	kingPawnEntry.load   = kingPawnLoad;
	kingPawnEntry.unload = kingPawnUnload;
	kingPawnEntry.create = kingPawnCreate;
	kingPawnEntry.reset  = NULL;

	kingPawnEntry.flags = 0x20400;
	kingPawnEntry.unk18 = 0;
	kingPawnEntry.unk20 = 0x14;
	kingPawnEntry.unk1C = 0x1602;
	kingPawnEntry.unk1E = 2;
	kingPawnEntry.unk21 = 0;

	kingPawnEntry.fieldTypes = kingPawnFieldTypes;
	kingPawnEntry.fieldNames = kingPawnFieldNames;

	if (kingPawnFieldTypes != NULL) {
		kingPawnEntry.flags |= 8;
	} else {
		kingPawnEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const kingPawnCtorEntry)(void) = kingPawnRegister;
