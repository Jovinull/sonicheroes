#include "types.h"

// The record that registers RAILMECHTYPEABC with the editor.
//
// The claim is .text 0x88724 to 0x887D4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void railmechtypeabcLoad(void);
extern "C" void railmechtypeabcUnload(void);
extern "C" void railmechtypeabcCreate(void);
extern "C" void railmechtypeabcReset(void);
extern "C" ObjectEntry railmechtypeabcEntry;
extern "C" char railmechtypeabcDisplayName[];
extern "C" char railmechtypeabcFieldTypes[];
extern "C" const char* railmechtypeabcFieldNames[];

extern "C" void railmechtypeabcRegister(void)
{
	railmechtypeabcEntry.flags = 0;
	railmechtypeabcEntry.unk18 = 0;

	railmechtypeabcEntry.name   = railmechtypeabcDisplayName;
	railmechtypeabcEntry.load   = railmechtypeabcLoad;
	railmechtypeabcEntry.unload = railmechtypeabcUnload;
	railmechtypeabcEntry.create = railmechtypeabcCreate;
	railmechtypeabcEntry.reset  = railmechtypeabcReset;

	railmechtypeabcEntry.flags = 0x1000;
	railmechtypeabcEntry.unk18 = 0;
	railmechtypeabcEntry.unk20 = 0xf;
	railmechtypeabcEntry.unk1C = 0x787;
	railmechtypeabcEntry.unk1E = 2;
	railmechtypeabcEntry.unk21 = 0;

	railmechtypeabcEntry.fieldTypes = railmechtypeabcFieldTypes;
	railmechtypeabcEntry.fieldNames = railmechtypeabcFieldNames;

	if (railmechtypeabcFieldTypes != NULL) {
		railmechtypeabcEntry.flags |= 8;
	} else {
		railmechtypeabcEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railmechtypeabcCtorEntry)(void) = railmechtypeabcRegister;
