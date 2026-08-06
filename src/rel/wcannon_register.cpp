#include "types.h"

// The record that registers WCANNON with the editor.
//
// The claim is .text 0xCC964 to 0xCCA14 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
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
extern "C" void wcannonLoad(void);
extern "C" void wcannonUnload(void);
extern "C" void wcannonCreate(void);
extern "C" void wcannonReset(void);
extern "C" ObjectEntry wcannonEntry;
extern "C" char wcannonDisplayName[];
extern "C" char wcannonFieldTypes[];
extern "C" const char* wcannonFieldNames[];

extern "C" void wcannonRegister(void)
{
	wcannonEntry.flags = 0;
	wcannonEntry.unk18 = 0;

	wcannonEntry.name   = wcannonDisplayName;
	wcannonEntry.load   = wcannonLoad;
	wcannonEntry.unload = wcannonUnload;
	wcannonEntry.create = wcannonCreate;
	wcannonEntry.reset  = wcannonReset;

	wcannonEntry.flags = 0x20000;
	wcannonEntry.unk18 = 0;
	wcannonEntry.unk20 = 0x14;
	wcannonEntry.unk1C = 0x804;
	wcannonEntry.unk1E = 2;
	wcannonEntry.unk21 = 0;

	wcannonEntry.fieldTypes = wcannonFieldTypes;
	wcannonEntry.fieldNames = wcannonFieldNames;

	if (wcannonFieldTypes != NULL) {
		wcannonEntry.flags |= 8;
	} else {
		wcannonEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const wcannonCtorEntry)(void) = wcannonRegister;
