#include "types.h"

// The record that registers ROLLDOOR OBJECT with the editor.
//
// The claim is .text 0x44148 to 0x441F0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ffs" is the field type string: one character per parameter the
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
extern "C" void rollDoorLoad(void);
extern "C" void rollDoorUnload(void);
extern "C" void rollDoorCreate(void);
extern "C" ObjectEntry rollDoorEntry;
extern "C" char rollDoorDisplayName[];
extern "C" char rollDoorFieldTypes[];
extern "C" const char* rollDoorFieldNames[];

extern "C" void rollDoorRegister(void)
{
	rollDoorEntry.flags = 0;
	rollDoorEntry.unk18 = 0;

	rollDoorEntry.name   = rollDoorDisplayName;
	rollDoorEntry.load   = rollDoorLoad;
	rollDoorEntry.unload = rollDoorUnload;
	rollDoorEntry.create = rollDoorCreate;
	rollDoorEntry.reset  = NULL;

	rollDoorEntry.flags = 0x20000;
	rollDoorEntry.unk18 = 0;
	rollDoorEntry.unk20 = 0x1e;
	rollDoorEntry.unk1C = 0x2c;
	rollDoorEntry.unk1E = 2;
	rollDoorEntry.unk21 = 0;

	rollDoorEntry.fieldTypes = rollDoorFieldTypes;
	rollDoorEntry.fieldNames = rollDoorFieldNames;

	if (rollDoorFieldTypes != NULL) {
		rollDoorEntry.flags |= 8;
	} else {
		rollDoorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rollDoorCtorEntry)(void) = rollDoorRegister;
