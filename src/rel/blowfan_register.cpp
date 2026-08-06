#include "types.h"

// The record that registers BLOWFAN with the editor.
//
// The claim is .text 0xC733C to 0xC73EC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void blowfanLoad(void);
extern "C" void blowfanUnload(void);
extern "C" void blowfanCreate(void);
extern "C" void blowfanReset(void);
extern "C" ObjectEntry blowfanEntry;
extern "C" char blowfanDisplayName[];
extern "C" char blowfanFieldTypes[];
extern "C" const char* blowfanFieldNames[];

extern "C" void blowfanRegister(void)
{
	blowfanEntry.flags = 0;
	blowfanEntry.unk18 = 0;

	blowfanEntry.name   = blowfanDisplayName;
	blowfanEntry.load   = blowfanLoad;
	blowfanEntry.unload = blowfanUnload;
	blowfanEntry.create = blowfanCreate;
	blowfanEntry.reset  = blowfanReset;

	blowfanEntry.flags = 0x20000;
	blowfanEntry.unk18 = 0;
	blowfanEntry.unk20 = 0x14;
	blowfanEntry.unk1C = 0x800;
	blowfanEntry.unk1E = 2;
	blowfanEntry.unk21 = 0;

	blowfanEntry.fieldTypes = blowfanFieldTypes;
	blowfanEntry.fieldNames = blowfanFieldNames;

	if (blowfanFieldTypes != NULL) {
		blowfanEntry.flags |= 8;
	} else {
		blowfanEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const blowfanCtorEntry)(void) = blowfanRegister;
