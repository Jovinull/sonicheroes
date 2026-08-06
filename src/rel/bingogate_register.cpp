#include "types.h"

// The record that registers BINGOGATE with the editor.
//
// The claim is .text 0x80504 to 0x805B4 and the .ctors word that names it.
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
extern "C" void bingogateLoad(void);
extern "C" void bingogateUnload(void);
extern "C" void bingogateCreate(void);
extern "C" void bingogateReset(void);
extern "C" ObjectEntry bingogateEntry;
extern "C" char bingogateDisplayName[];
extern "C" char bingogateFieldTypes[];
extern "C" const char* bingogateFieldNames[];

extern "C" void bingogateRegister(void)
{
	bingogateEntry.flags = 0;
	bingogateEntry.unk18 = 0;

	bingogateEntry.name   = bingogateDisplayName;
	bingogateEntry.load   = bingogateLoad;
	bingogateEntry.unload = bingogateUnload;
	bingogateEntry.create = bingogateCreate;
	bingogateEntry.reset  = bingogateReset;

	bingogateEntry.flags = 0x20000;
	bingogateEntry.unk18 = 0;
	bingogateEntry.unk20 = 0xf;
	bingogateEntry.unk1C = 0x50e;
	bingogateEntry.unk1E = 2;
	bingogateEntry.unk21 = 0;

	bingogateEntry.fieldTypes = bingogateFieldTypes;
	bingogateEntry.fieldNames = bingogateFieldNames;

	if (bingogateFieldTypes != NULL) {
		bingogateEntry.flags |= 8;
	} else {
		bingogateEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bingogateCtorEntry)(void) = bingogateRegister;
