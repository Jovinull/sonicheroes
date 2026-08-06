#include "types.h"

// The record that registers RAILBUSH with the editor.
//
// The claim is .text 0x8212C to 0x821DC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void railbushLoad(void);
extern "C" void railbushUnload(void);
extern "C" void railbushCreate(void);
extern "C" void railbushReset(void);
extern "C" ObjectEntry railbushEntry;
extern "C" char railbushDisplayName[];
extern "C" char railbushFieldTypes[];
extern "C" const char* railbushFieldNames[];

extern "C" void railbushRegister(void)
{
	railbushEntry.flags = 0;
	railbushEntry.unk18 = 0;

	railbushEntry.name   = railbushDisplayName;
	railbushEntry.load   = railbushLoad;
	railbushEntry.unload = railbushUnload;
	railbushEntry.create = railbushCreate;
	railbushEntry.reset  = railbushReset;

	railbushEntry.flags = 0x1000;
	railbushEntry.unk18 = 0;
	railbushEntry.unk20 = 0xf;
	railbushEntry.unk1C = 0x781;
	railbushEntry.unk1E = 2;
	railbushEntry.unk21 = 0;

	railbushEntry.fieldTypes = railbushFieldTypes;
	railbushEntry.fieldNames = railbushFieldNames;

	if (railbushFieldTypes != NULL) {
		railbushEntry.flags |= 8;
	} else {
		railbushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railbushCtorEntry)(void) = railbushRegister;
