#include "types.h"

// The record that registers 456DICE with the editor.
//
// The claim is .text 0x8E8A4 to 0x8E954 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFFsss" is the field type string: one character per parameter the
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
extern "C" void obj456diceLoad(void);
extern "C" void obj456diceUnload(void);
extern "C" void obj456diceCreate(void);
extern "C" void obj456diceReset(void);
extern "C" ObjectEntry obj456diceEntry;
extern "C" char obj456diceDisplayName[];
extern "C" char obj456diceFieldTypes[];
extern "C" const char* obj456diceFieldNames[];

extern "C" void obj456diceRegister(void)
{
	obj456diceEntry.flags = 0;
	obj456diceEntry.unk18 = 0;

	obj456diceEntry.name   = obj456diceDisplayName;
	obj456diceEntry.load   = obj456diceLoad;
	obj456diceEntry.unload = obj456diceUnload;
	obj456diceEntry.create = obj456diceCreate;
	obj456diceEntry.reset  = obj456diceReset;

	obj456diceEntry.flags = 0x20000;
	obj456diceEntry.unk18 = 0;
	obj456diceEntry.unk20 = 0xf;
	obj456diceEntry.unk1C = 0x50a;
	obj456diceEntry.unk1E = 2;
	obj456diceEntry.unk21 = 0;

	obj456diceEntry.fieldTypes = obj456diceFieldTypes;
	obj456diceEntry.fieldNames = obj456diceFieldNames;

	if (obj456diceFieldTypes != NULL) {
		obj456diceEntry.flags |= 8;
	} else {
		obj456diceEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const obj456diceCtorEntry)(void) = obj456diceRegister;
