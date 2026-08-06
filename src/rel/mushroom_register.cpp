#include "types.h"

// The record that registers MUSHROOM with the editor.
//
// The claim is .text 0x7BEE8 to 0x7BF98 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void mushroomLoad(void);
extern "C" void mushroomUnload(void);
extern "C" void mushroomCreate(void);
extern "C" void mushroomReset(void);
extern "C" ObjectEntry mushroomEntry;
extern "C" char mushroomDisplayName[];
extern "C" char mushroomFieldTypes[];
extern "C" const char* mushroomFieldNames[];

extern "C" void mushroomRegister(void)
{
	mushroomEntry.flags = 0;
	mushroomEntry.unk18 = 0;

	mushroomEntry.name   = mushroomDisplayName;
	mushroomEntry.load   = mushroomLoad;
	mushroomEntry.unload = mushroomUnload;
	mushroomEntry.create = mushroomCreate;
	mushroomEntry.reset  = mushroomReset;

	mushroomEntry.flags = 0x1000;
	mushroomEntry.unk18 = 0;
	mushroomEntry.unk20 = 0xa;
	mushroomEntry.unk1C = 0x982;
	mushroomEntry.unk1E = 2;
	mushroomEntry.unk21 = 0;

	mushroomEntry.fieldTypes = mushroomFieldTypes;
	mushroomEntry.fieldNames = mushroomFieldNames;

	if (mushroomFieldTypes != NULL) {
		mushroomEntry.flags |= 8;
	} else {
		mushroomEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const mushroomCtorEntry)(void) = mushroomRegister;
