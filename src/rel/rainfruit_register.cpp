#include "types.h"

// The record that registers RAINFRUIT with the editor.
//
// The claim is .text 0x82ED4 to 0x82F84 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFsss" is the field type string: one character per parameter the
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
extern "C" void rainfruitLoad(void);
extern "C" void rainfruitUnload(void);
extern "C" void rainfruitCreate(void);
extern "C" void rainfruitReset(void);
extern "C" ObjectEntry rainfruitEntry;
extern "C" char rainfruitDisplayName[];
extern "C" char rainfruitFieldTypes[];
extern "C" const char* rainfruitFieldNames[];

extern "C" void rainfruitRegister(void)
{
	rainfruitEntry.flags = 0;
	rainfruitEntry.unk18 = 0;

	rainfruitEntry.name   = rainfruitDisplayName;
	rainfruitEntry.load   = rainfruitLoad;
	rainfruitEntry.unload = rainfruitUnload;
	rainfruitEntry.create = rainfruitCreate;
	rainfruitEntry.reset  = rainfruitReset;

	rainfruitEntry.flags = 0x20000;
	rainfruitEntry.unk18 = 0;
	rainfruitEntry.unk20 = 0xa;
	rainfruitEntry.unk1C = 0x908;
	rainfruitEntry.unk1E = 2;
	rainfruitEntry.unk21 = 0;

	rainfruitEntry.fieldTypes = rainfruitFieldTypes;
	rainfruitEntry.fieldNames = rainfruitFieldNames;

	if (rainfruitFieldTypes != NULL) {
		rainfruitEntry.flags |= 8;
	} else {
		rainfruitEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rainfruitCtorEntry)(void) = rainfruitRegister;
