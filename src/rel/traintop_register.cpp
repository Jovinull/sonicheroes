#include "types.h"

// The record that registers TRAINTOP with the editor.
//
// The claim is .text 0x96040 to 0x960E0 and the .ctors word that names it.
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
extern "C" void traintopLoad(void);
extern "C" void traintopUnload(void);
extern "C" void traintopCreate(void);
extern "C" void traintopReset(void);
extern "C" ObjectEntry traintopEntry;
extern "C" char traintopDisplayName[];

extern "C" void traintopRegister(void)
{
	traintopEntry.flags = 0;
	traintopEntry.unk18 = 0;

	traintopEntry.name   = traintopDisplayName;
	traintopEntry.load   = traintopLoad;
	traintopEntry.unload = traintopUnload;
	traintopEntry.create = traintopCreate;
	traintopEntry.reset  = traintopReset;

	traintopEntry.flags = 0x1000;
	traintopEntry.unk18 = 0;
	traintopEntry.unk20 = 0xf;
	traintopEntry.unk1C = 0x798;
	traintopEntry.unk1E = 2;
	traintopEntry.unk21 = 0;

	traintopEntry.fieldTypes = NULL;
	traintopEntry.fieldNames = NULL;

	if (traintopEntry.fieldTypes != NULL) {
		traintopEntry.flags |= 8;
	} else {
		traintopEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const traintopCtorEntry)(void) = traintopRegister;
