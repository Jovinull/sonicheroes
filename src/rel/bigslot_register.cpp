#include "types.h"

// The record that registers BIGSLOT with the editor.
//
// The claim is .text 0x87AC4 to 0x87B74 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
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
extern "C" void bigslotLoad(void);
extern "C" void bigslotUnload(void);
extern "C" void bigslotCreate(void);
extern "C" void bigslotReset(void);
extern "C" ObjectEntry bigslotEntry;
extern "C" char bigslotDisplayName[];
extern "C" char bigslotFieldTypes[];
extern "C" const char* bigslotFieldNames[];

extern "C" void bigslotRegister(void)
{
	bigslotEntry.flags = 0;
	bigslotEntry.unk18 = 0;

	bigslotEntry.name   = bigslotDisplayName;
	bigslotEntry.load   = bigslotLoad;
	bigslotEntry.unload = bigslotUnload;
	bigslotEntry.create = bigslotCreate;
	bigslotEntry.reset  = bigslotReset;

	bigslotEntry.flags = 0x1000;
	bigslotEntry.unk18 = 0;
	bigslotEntry.unk20 = 0xf;
	bigslotEntry.unk1C = 0x585;
	bigslotEntry.unk1E = 2;
	bigslotEntry.unk21 = 0;

	bigslotEntry.fieldTypes = bigslotFieldTypes;
	bigslotEntry.fieldNames = bigslotFieldNames;

	if (bigslotFieldTypes != NULL) {
		bigslotEntry.flags |= 8;
	} else {
		bigslotEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigslotCtorEntry)(void) = bigslotRegister;
