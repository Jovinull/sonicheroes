#include "types.h"

// The record that registers DESTRUCTRAIL with the editor.
//
// The claim is .text 0x78F78 to 0x79018 and the .ctors word that names it.
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
extern "C" void destructrailLoad(void);
extern "C" void destructrailUnload(void);
extern "C" void destructrailCreate(void);
extern "C" void destructrailReset(void);
extern "C" ObjectEntry destructrailEntry;
extern "C" char destructrailDisplayName[];

extern "C" void destructrailRegister(void)
{
	destructrailEntry.flags = 0;
	destructrailEntry.unk18 = 0;

	destructrailEntry.name   = destructrailDisplayName;
	destructrailEntry.load   = destructrailLoad;
	destructrailEntry.unload = destructrailUnload;
	destructrailEntry.create = destructrailCreate;
	destructrailEntry.reset  = destructrailReset;

	destructrailEntry.flags = 0x80;
	destructrailEntry.unk18 = 0;
	destructrailEntry.unk20 = 0xf;
	destructrailEntry.unk1C = 0x70a;
	destructrailEntry.unk1E = 2;
	destructrailEntry.unk21 = 0;

	destructrailEntry.fieldTypes = NULL;
	destructrailEntry.fieldNames = NULL;

	if (destructrailEntry.fieldTypes != NULL) {
		destructrailEntry.flags |= 8;
	} else {
		destructrailEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const destructrailCtorEntry)(void) = destructrailRegister;
