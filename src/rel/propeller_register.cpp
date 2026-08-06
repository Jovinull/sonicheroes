#include "types.h"

// The record that registers PROPELLER with the editor.
//
// The claim is .text 0x49590 to 0x49630 and the .ctors word that names it. Only the
// record is taken: the hooks it points at stay assembly and are reached by the
// names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// This class exposes no parameter to the editor, so its type string and
// label array are null and the test at the end reads the type pointer back out
// of the record: from a local the compiler folds the branch away.

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
extern "C" void propellerLoad(void);
extern "C" void propellerUnload(void);
extern "C" void propellerCreate(void);
extern "C" void propellerReset(void);
extern "C" ObjectEntry propellerEntry;
extern "C" char propellerDisplayName[];

extern "C" void propellerRegister(void)
{
	propellerEntry.flags = 0;
	propellerEntry.unk18 = 0;

	propellerEntry.name   = propellerDisplayName;
	propellerEntry.load   = propellerLoad;
	propellerEntry.unload = propellerUnload;
	propellerEntry.create = propellerCreate;
	propellerEntry.reset  = propellerReset;

	propellerEntry.flags = 0x80;
	propellerEntry.unk18 = 0;
	propellerEntry.unk20 = 0x1E;
	propellerEntry.unk1C = 0x28;
	propellerEntry.unk1E = 8;
	propellerEntry.unk21 = 0;

	propellerEntry.fieldTypes = NULL;
	propellerEntry.fieldNames = NULL;

	if (propellerEntry.fieldTypes != NULL) {
		propellerEntry.flags |= 8;
	} else {
		propellerEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const propellerCtorEntry)(void) = propellerRegister;
