#include "types.h"

// The record that registers WATERPLANT with the editor.
//
// The claim is .text 0x9C85C to 0x9C90C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void waterplantLoad(void);
extern "C" void waterplantUnload(void);
extern "C" void waterplantCreate(void);
extern "C" void waterplantReset(void);
extern "C" ObjectEntry waterplantEntry;
extern "C" char waterplantDisplayName[];
extern "C" char waterplantFieldTypes[];
extern "C" const char* waterplantFieldNames[];

extern "C" void waterplantRegister(void)
{
	waterplantEntry.flags = 0;
	waterplantEntry.unk18 = 0;

	waterplantEntry.name   = waterplantDisplayName;
	waterplantEntry.load   = waterplantLoad;
	waterplantEntry.unload = waterplantUnload;
	waterplantEntry.create = waterplantCreate;
	waterplantEntry.reset  = waterplantReset;

	waterplantEntry.flags = 0x1000;
	waterplantEntry.unk18 = 0;
	waterplantEntry.unk20 = 0xa;
	waterplantEntry.unk1C = 0x98c;
	waterplantEntry.unk1E = 2;
	waterplantEntry.unk21 = 0;

	waterplantEntry.fieldTypes = waterplantFieldTypes;
	waterplantEntry.fieldNames = waterplantFieldNames;

	if (waterplantFieldTypes != NULL) {
		waterplantEntry.flags |= 8;
	} else {
		waterplantEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const waterplantCtorEntry)(void) = waterplantRegister;
