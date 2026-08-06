#include "types.h"

// The record that registers EGGMASO with the editor.
//
// The claim is .text 0xC8130 to 0xC81CC and the .ctors word that names it.
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
extern "C" void eggmasoLoad(void);
extern "C" void eggmasoUnload(void);
extern "C" void eggmasoCreate(void);
extern "C" void eggmasoReset(void);
extern "C" ObjectEntry eggmasoEntry;
extern "C" char eggmasoDisplayName[];

extern "C" void eggmasoRegister(void)
{
	eggmasoEntry.flags = 0;
	eggmasoEntry.unk18 = 0;

	eggmasoEntry.name   = eggmasoDisplayName;
	eggmasoEntry.load   = eggmasoLoad;
	eggmasoEntry.unload = eggmasoUnload;
	eggmasoEntry.create = eggmasoCreate;
	eggmasoEntry.reset  = eggmasoReset;

	eggmasoEntry.flags = 0x14;
	eggmasoEntry.unk18 = 0;
	eggmasoEntry.unk20 = 0x14;
	eggmasoEntry.unk1C = 0x742;
	eggmasoEntry.unk1E = 2;
	eggmasoEntry.unk21 = 0;

	eggmasoEntry.fieldTypes = NULL;
	eggmasoEntry.fieldNames = NULL;

	if (eggmasoEntry.fieldTypes != NULL) {
		eggmasoEntry.flags |= 8;
	} else {
		eggmasoEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const eggmasoCtorEntry)(void) = eggmasoRegister;
