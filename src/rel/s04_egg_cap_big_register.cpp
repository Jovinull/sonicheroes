#include "types.h"

// The record that registers S04 EggCapBig with the editor.
//
// The claim is .text 0x8EDE4 to 0x8EE7C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage03D carries this run.

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
extern "C" void s04EggCapBigLoad(void);
extern "C" void s04EggCapBigUnload(void);
extern "C" void s04EggCapBigCreate(void);
extern "C" ObjectEntry s04EggCapBigEntry;
extern "C" char s04EggCapBigDisplayName[];

extern "C" void s04EggCapBigRegister(void)
{
	s04EggCapBigEntry.flags = 0;
	s04EggCapBigEntry.unk18 = 0;

	s04EggCapBigEntry.name   = s04EggCapBigDisplayName;
	s04EggCapBigEntry.load   = s04EggCapBigLoad;
	s04EggCapBigEntry.unload = s04EggCapBigUnload;
	s04EggCapBigEntry.create = s04EggCapBigCreate;
	s04EggCapBigEntry.reset  = NULL;

	s04EggCapBigEntry.flags = 0x20000;
	s04EggCapBigEntry.unk18 = 0;
	s04EggCapBigEntry.unk20 = 0xa;
	s04EggCapBigEntry.unk1C = 0x404;
	s04EggCapBigEntry.unk1E = 2;
	s04EggCapBigEntry.unk21 = 0;

	s04EggCapBigEntry.fieldTypes = NULL;
	s04EggCapBigEntry.fieldNames = NULL;

	if (s04EggCapBigEntry.fieldTypes != NULL) {
		s04EggCapBigEntry.flags |= 8;
	} else {
		s04EggCapBigEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04EggCapBigCtorEntry)(void) = s04EggCapBigRegister;
