#include "types.h"

// The record that registers TUTAETC with the editor.
//
// The claim is .text 0xA80D4 to 0xA8174 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage09D carries this run.

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
extern "C" void tutaetcLoad(void);
extern "C" void tutaetcUnload(void);
extern "C" void tutaetcCreate(void);
extern "C" void tutaetcReset(void);
extern "C" ObjectEntry tutaetcEntry;
extern "C" char tutaetcDisplayName[];

extern "C" void tutaetcRegister(void)
{
	tutaetcEntry.flags = 0;
	tutaetcEntry.unk18 = 0;

	tutaetcEntry.name   = tutaetcDisplayName;
	tutaetcEntry.load   = tutaetcLoad;
	tutaetcEntry.unload = tutaetcUnload;
	tutaetcEntry.create = tutaetcCreate;
	tutaetcEntry.reset  = tutaetcReset;

	tutaetcEntry.flags = 0x400;
	tutaetcEntry.unk18 = 0;
	tutaetcEntry.unk20 = 0x28;
	tutaetcEntry.unk1C = 0x912;
	tutaetcEntry.unk1E = 2;
	tutaetcEntry.unk21 = 0;

	tutaetcEntry.fieldTypes = NULL;
	tutaetcEntry.fieldNames = NULL;

	if (tutaetcEntry.fieldTypes != NULL) {
		tutaetcEntry.flags |= 8;
	} else {
		tutaetcEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const tutaetcCtorEntry)(void) = tutaetcRegister;
