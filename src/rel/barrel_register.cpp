#include "types.h"

// The record that registers BARREL with the editor.
//
// The claim is .text 0x726AC to 0x7274C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void barrelLoad(void);
extern "C" void barrelUnload(void);
extern "C" void barrelCreate(void);
extern "C" void barrelReset(void);
extern "C" ObjectEntry barrelEntry;
extern "C" char barrelDisplayName[];

extern "C" void barrelRegister(void)
{
	barrelEntry.flags = 0;
	barrelEntry.unk18 = 0;

	barrelEntry.name   = barrelDisplayName;
	barrelEntry.load   = barrelLoad;
	barrelEntry.unload = barrelUnload;
	barrelEntry.create = barrelCreate;
	barrelEntry.reset  = barrelReset;

	barrelEntry.flags = 0x1000;
	barrelEntry.unk18 = 0;
	barrelEntry.unk20 = 0xf;
	barrelEntry.unk1C = 0x792;
	barrelEntry.unk1E = 2;
	barrelEntry.unk21 = 0;

	barrelEntry.fieldTypes = NULL;
	barrelEntry.fieldNames = NULL;

	if (barrelEntry.fieldTypes != NULL) {
		barrelEntry.flags |= 8;
	} else {
		barrelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const barrelCtorEntry)(void) = barrelRegister;
