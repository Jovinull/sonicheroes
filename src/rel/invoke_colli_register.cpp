#include "types.h"

// The record that registers INVOKE COLLI with the editor.
//
// The claim is .text 0x4FBE0 to 0x4FC74 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFFcC" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in four of the fourteen stage modules: 13D, 26D, 27D and 28D.

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
extern "C" void invokeColliCreate(void);
extern "C" ObjectEntry invokeColliEntry;
extern "C" char invokeColliDisplayName[];
extern "C" char invokeColliFieldTypes[];
extern "C" const char* invokeColliFieldNames[];

extern "C" void invokeColliRegister(void)
{
	invokeColliEntry.flags = 0;
	invokeColliEntry.unk18 = 0;

	invokeColliEntry.name   = invokeColliDisplayName;
	invokeColliEntry.load   = NULL;
	invokeColliEntry.unload = NULL;
	invokeColliEntry.create = invokeColliCreate;
	invokeColliEntry.reset  = NULL;

	invokeColliEntry.flags = 0x0;
	invokeColliEntry.unk18 = 0;
	invokeColliEntry.unk20 = 0x32;
	invokeColliEntry.unk1C = 0x20b;
	invokeColliEntry.unk1E = 2;
	invokeColliEntry.unk21 = 0;

	invokeColliEntry.fieldTypes = invokeColliFieldTypes;
	invokeColliEntry.fieldNames = invokeColliFieldNames;

	if (invokeColliFieldTypes != NULL) {
		invokeColliEntry.flags |= 8;
	} else {
		invokeColliEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const invokeColliCtorEntry)(void) = invokeColliRegister;
