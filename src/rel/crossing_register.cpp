#include "types.h"

// The record that registers CROSSING with the editor.
//
// The claim is .text 0x77A88 to 0x77B38 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fi" is the field type string: one character per parameter the
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
extern "C" void crossingLoad(void);
extern "C" void crossingUnload(void);
extern "C" void crossingCreate(void);
extern "C" void crossingReset(void);
extern "C" ObjectEntry crossingEntry;
extern "C" char crossingDisplayName[];
extern "C" char crossingFieldTypes[];
extern "C" const char* crossingFieldNames[];

extern "C" void crossingRegister(void)
{
	crossingEntry.flags = 0;
	crossingEntry.unk18 = 0;

	crossingEntry.name   = crossingDisplayName;
	crossingEntry.load   = crossingLoad;
	crossingEntry.unload = crossingUnload;
	crossingEntry.create = crossingCreate;
	crossingEntry.reset  = crossingReset;

	crossingEntry.flags = 0x20000;
	crossingEntry.unk18 = 0;
	crossingEntry.unk20 = 0xf;
	crossingEntry.unk1C = 0x704;
	crossingEntry.unk1E = 2;
	crossingEntry.unk21 = 0;

	crossingEntry.fieldTypes = crossingFieldTypes;
	crossingEntry.fieldNames = crossingFieldNames;

	if (crossingFieldTypes != NULL) {
		crossingEntry.flags |= 8;
	} else {
		crossingEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const crossingCtorEntry)(void) = crossingRegister;
