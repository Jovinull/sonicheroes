#include "types.h"

// The record that registers RAINMUSH with the editor.
//
// The claim is .text 0x88A58 to 0x88B08 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFCC" is the field type string: one character per parameter the
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
extern "C" void rainmushLoad(void);
extern "C" void rainmushUnload(void);
extern "C" void rainmushCreate(void);
extern "C" void rainmushReset(void);
extern "C" ObjectEntry rainmushEntry;
extern "C" char rainmushDisplayName[];
extern "C" char rainmushFieldTypes[];
extern "C" const char* rainmushFieldNames[];

extern "C" void rainmushRegister(void)
{
	rainmushEntry.flags = 0;
	rainmushEntry.unk18 = 0;

	rainmushEntry.name   = rainmushDisplayName;
	rainmushEntry.load   = rainmushLoad;
	rainmushEntry.unload = rainmushUnload;
	rainmushEntry.create = rainmushCreate;
	rainmushEntry.reset  = rainmushReset;

	rainmushEntry.flags = 0x20000;
	rainmushEntry.unk18 = 0;
	rainmushEntry.unk20 = 0xa;
	rainmushEntry.unk1C = 0x903;
	rainmushEntry.unk1E = 2;
	rainmushEntry.unk21 = 0;

	rainmushEntry.fieldTypes = rainmushFieldTypes;
	rainmushEntry.fieldNames = rainmushFieldNames;

	if (rainmushFieldTypes != NULL) {
		rainmushEntry.flags |= 8;
	} else {
		rainmushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rainmushCtorEntry)(void) = rainmushRegister;
