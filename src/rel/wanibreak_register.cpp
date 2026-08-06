#include "types.h"

// The record that registers WANIBREAK with the editor.
//
// The claim is .text 0xAA464 to 0xAA514 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cc" is the field type string: one character per parameter the
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
extern "C" void wanibreakLoad(void);
extern "C" void wanibreakUnload(void);
extern "C" void wanibreakCreate(void);
extern "C" void wanibreakReset(void);
extern "C" ObjectEntry wanibreakEntry;
extern "C" char wanibreakDisplayName[];
extern "C" char wanibreakFieldTypes[];
extern "C" const char* wanibreakFieldNames[];

extern "C" void wanibreakRegister(void)
{
	wanibreakEntry.flags = 0;
	wanibreakEntry.unk18 = 0;

	wanibreakEntry.name   = wanibreakDisplayName;
	wanibreakEntry.load   = wanibreakLoad;
	wanibreakEntry.unload = wanibreakUnload;
	wanibreakEntry.create = wanibreakCreate;
	wanibreakEntry.reset  = wanibreakReset;

	wanibreakEntry.flags = 0x1000;
	wanibreakEntry.unk18 = 0;
	wanibreakEntry.unk20 = 0xf;
	wanibreakEntry.unk1C = 0x99a;
	wanibreakEntry.unk1E = 2;
	wanibreakEntry.unk21 = 0;

	wanibreakEntry.fieldTypes = wanibreakFieldTypes;
	wanibreakEntry.fieldNames = wanibreakFieldNames;

	if (wanibreakFieldTypes != NULL) {
		wanibreakEntry.flags |= 8;
	} else {
		wanibreakEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const wanibreakCtorEntry)(void) = wanibreakRegister;
