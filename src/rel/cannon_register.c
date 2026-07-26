#include "types.h"

// The record that registers CANNON OBJECT with the editor.
//
// The claim is .text 0x1A9B4 to 0x1AA64 and the .ctors word that names it. Only
// the record is taken: the four hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere.
//
// This class uses the fourth hook slot, which most of the others leave null.
// Its field type string is twelve halfwords, the longest in the module: a
// cannon carries a target list rather than a handful of tuning values.

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
extern "C" void cannonLoad(void);
extern "C" void cannonUnload(void);
extern "C" void cannonCreate(void);
extern "C" void cannonReset(void);
extern "C" ObjectEntry cannonEntry;
extern "C" char cannonDisplayName[];
extern "C" char cannonFieldTypes[];
extern "C" const char* cannonFieldNames[];

extern "C" void cannonRegister(void)
{
	cannonEntry.flags = 0;
	cannonEntry.unk18 = 0;

	cannonEntry.name   = cannonDisplayName;
	cannonEntry.load   = cannonLoad;
	cannonEntry.unload = cannonUnload;
	cannonEntry.create = cannonCreate;
	cannonEntry.reset  = cannonReset;

	cannonEntry.flags = 0x20000;
	cannonEntry.unk18 = 0;
	cannonEntry.unk20 = 0x1E;
	cannonEntry.unk1C = 0x10;
	cannonEntry.unk1E = 2;
	cannonEntry.unk21 = 0;

	cannonEntry.fieldTypes = cannonFieldTypes;
	cannonEntry.fieldNames = cannonFieldNames;

	if (cannonFieldTypes != NULL) {
		cannonEntry.flags |= 8;
	} else {
		cannonEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const cannonCtorEntry)(void) = cannonRegister;
