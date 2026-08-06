#include "types.h"

// The record that registers BIGCANNONTOP with the editor.
//
// The claim is .text 0xC675C to 0xC6810 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ci" is the field type string: one character per parameter the
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
extern "C" void bigcannontopLoad(void);
extern "C" void bigcannontopUnload(void);
extern "C" void bigcannontopCreate(void);
extern "C" void bigcannontopReset(void);
extern "C" ObjectEntry bigcannontopEntry;
extern "C" char bigcannontopDisplayName[];
extern "C" char bigcannontopFieldTypes[];
extern "C" const char* bigcannontopFieldNames[];

extern "C" void bigcannontopRegister(void)
{
	bigcannontopEntry.flags = 0;
	bigcannontopEntry.unk18 = 0;

	bigcannontopEntry.name   = bigcannontopDisplayName;
	bigcannontopEntry.load   = bigcannontopLoad;
	bigcannontopEntry.unload = bigcannontopUnload;
	bigcannontopEntry.create = bigcannontopCreate;
	bigcannontopEntry.reset  = bigcannontopReset;

	bigcannontopEntry.flags = 0x400;
	bigcannontopEntry.unk18 = 0;
	bigcannontopEntry.unk20 = 0x14;
	bigcannontopEntry.unk1C = 0x73f;
	bigcannontopEntry.unk1E = 2;
	bigcannontopEntry.unk21 = 0xfa;

	bigcannontopEntry.fieldTypes = bigcannontopFieldTypes;
	bigcannontopEntry.fieldNames = bigcannontopFieldNames;

	if (bigcannontopFieldTypes != NULL) {
		bigcannontopEntry.flags |= 8;
	} else {
		bigcannontopEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigcannontopCtorEntry)(void) = bigcannontopRegister;
