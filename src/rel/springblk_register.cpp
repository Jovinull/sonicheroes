#include "types.h"

// The record that registers SPRINGBLK with the editor.
//
// The claim is .text 0x9A630 to 0x9A6E0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fi" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void springblkLoad(void);
extern "C" void springblkUnload(void);
extern "C" void springblkCreate(void);
extern "C" void springblkReset(void);
extern "C" ObjectEntry springblkEntry;
extern "C" char springblkDisplayName[];
extern "C" char springblkFieldTypes[];
extern "C" const char* springblkFieldNames[];

extern "C" void springblkRegister(void)
{
	springblkEntry.flags = 0;
	springblkEntry.unk18 = 0;

	springblkEntry.name   = springblkDisplayName;
	springblkEntry.load   = springblkLoad;
	springblkEntry.unload = springblkUnload;
	springblkEntry.create = springblkCreate;
	springblkEntry.reset  = springblkReset;

	springblkEntry.flags = 0x20000;
	springblkEntry.unk18 = 0;
	springblkEntry.unk20 = 0xf;
	springblkEntry.unk1C = 0x504;
	springblkEntry.unk1E = 2;
	springblkEntry.unk21 = 0;

	springblkEntry.fieldTypes = springblkFieldTypes;
	springblkEntry.fieldNames = springblkFieldNames;

	if (springblkFieldTypes != NULL) {
		springblkEntry.flags |= 8;
	} else {
		springblkEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const springblkCtorEntry)(void) = springblkRegister;
