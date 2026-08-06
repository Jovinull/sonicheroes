#include "types.h"

// The record that registers REAFREDGREEN with the editor.
//
// The claim is .text 0x97108 to 0x971B8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FI" is the field type string: one character per parameter the
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
extern "C" void reafredgreenLoad(void);
extern "C" void reafredgreenUnload(void);
extern "C" void reafredgreenCreate(void);
extern "C" void reafredgreenReset(void);
extern "C" ObjectEntry reafredgreenEntry;
extern "C" char reafredgreenDisplayName[];
extern "C" char reafredgreenFieldTypes[];
extern "C" const char* reafredgreenFieldNames[];

extern "C" void reafredgreenRegister(void)
{
	reafredgreenEntry.flags = 0;
	reafredgreenEntry.unk18 = 0;

	reafredgreenEntry.name   = reafredgreenDisplayName;
	reafredgreenEntry.load   = reafredgreenLoad;
	reafredgreenEntry.unload = reafredgreenUnload;
	reafredgreenEntry.create = reafredgreenCreate;
	reafredgreenEntry.reset  = reafredgreenReset;

	reafredgreenEntry.flags = 0x1000;
	reafredgreenEntry.unk18 = 0;
	reafredgreenEntry.unk20 = 0xa;
	reafredgreenEntry.unk1C = 0x997;
	reafredgreenEntry.unk1E = 2;
	reafredgreenEntry.unk21 = 0;

	reafredgreenEntry.fieldTypes = reafredgreenFieldTypes;
	reafredgreenEntry.fieldNames = reafredgreenFieldNames;

	if (reafredgreenFieldTypes != NULL) {
		reafredgreenEntry.flags |= 8;
	} else {
		reafredgreenEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const reafredgreenCtorEntry)(void) = reafredgreenRegister;
