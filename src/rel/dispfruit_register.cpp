#include "types.h"

// The record that registers DISPFRUIT with the editor.
//
// The claim is .text 0x95F84 to 0x96034 and the .ctors word that names it.
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
extern "C" void dispfruitLoad(void);
extern "C" void dispfruitUnload(void);
extern "C" void dispfruitCreate(void);
extern "C" void dispfruitReset(void);
extern "C" ObjectEntry dispfruitEntry;
extern "C" char dispfruitDisplayName[];
extern "C" char dispfruitFieldTypes[];
extern "C" const char* dispfruitFieldNames[];

extern "C" void dispfruitRegister(void)
{
	dispfruitEntry.flags = 0;
	dispfruitEntry.unk18 = 0;

	dispfruitEntry.name   = dispfruitDisplayName;
	dispfruitEntry.load   = dispfruitLoad;
	dispfruitEntry.unload = dispfruitUnload;
	dispfruitEntry.create = dispfruitCreate;
	dispfruitEntry.reset  = dispfruitReset;

	dispfruitEntry.flags = 0x1000;
	dispfruitEntry.unk18 = 0;
	dispfruitEntry.unk20 = 0xa;
	dispfruitEntry.unk1C = 0x991;
	dispfruitEntry.unk1E = 2;
	dispfruitEntry.unk21 = 0;

	dispfruitEntry.fieldTypes = dispfruitFieldTypes;
	dispfruitEntry.fieldNames = dispfruitFieldNames;

	if (dispfruitFieldTypes != NULL) {
		dispfruitEntry.flags |= 8;
	} else {
		dispfruitEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const dispfruitCtorEntry)(void) = dispfruitRegister;
