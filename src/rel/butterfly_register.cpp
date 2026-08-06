#include "types.h"

// The record that registers BUTTERFLY with the editor.
//
// The claim is .text 0x72980 to 0x72A30 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFFi" is the field type string: one character per parameter the
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
extern "C" void butterflyLoad(void);
extern "C" void butterflyUnload(void);
extern "C" void butterflyCreate(void);
extern "C" void butterflyReset(void);
extern "C" ObjectEntry butterflyEntry;
extern "C" char butterflyDisplayName[];
extern "C" char butterflyFieldTypes[];
extern "C" const char* butterflyFieldNames[];

extern "C" void butterflyRegister(void)
{
	butterflyEntry.flags = 0;
	butterflyEntry.unk18 = 0;

	butterflyEntry.name   = butterflyDisplayName;
	butterflyEntry.load   = butterflyLoad;
	butterflyEntry.unload = butterflyUnload;
	butterflyEntry.create = butterflyCreate;
	butterflyEntry.reset  = butterflyReset;

	butterflyEntry.flags = 0x1000;
	butterflyEntry.unk18 = 0;
	butterflyEntry.unk20 = 0xa;
	butterflyEntry.unk1C = 0x980;
	butterflyEntry.unk1E = 2;
	butterflyEntry.unk21 = 0;

	butterflyEntry.fieldTypes = butterflyFieldTypes;
	butterflyEntry.fieldNames = butterflyFieldNames;

	if (butterflyFieldTypes != NULL) {
		butterflyEntry.flags |= 8;
	} else {
		butterflyEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const butterflyCtorEntry)(void) = butterflyRegister;
