#include "types.h"

// The record that registers SIGNAL OBJECT with the editor.
//
// The claim is .text 0x46B54 to 0x46BFC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void signalLoad(void);
extern "C" void signalUnload(void);
extern "C" void signalCreate(void);
extern "C" ObjectEntry signalEntry;
extern "C" char signalDisplayName[];
extern "C" char signalFieldTypes[];
extern "C" const char* signalFieldNames[];

extern "C" void signalRegister(void)
{
	signalEntry.flags = 0;
	signalEntry.unk18 = 0;

	signalEntry.name   = signalDisplayName;
	signalEntry.load   = signalLoad;
	signalEntry.unload = signalUnload;
	signalEntry.create = signalCreate;
	signalEntry.reset  = NULL;

	signalEntry.flags = 0x20000;
	signalEntry.unk18 = 0;
	signalEntry.unk20 = 0x1e;
	signalEntry.unk1C = 0x25;
	signalEntry.unk1E = 2;
	signalEntry.unk21 = 0;

	signalEntry.fieldTypes = signalFieldTypes;
	signalEntry.fieldNames = signalFieldNames;

	if (signalFieldTypes != NULL) {
		signalEntry.flags |= 8;
	} else {
		signalEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const signalCtorEntry)(void) = signalRegister;
