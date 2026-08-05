#include "types.h"

// The record that registers WARP with the editor.
//
// The claim is .text 0xBE134 to 0xBE1E0 and the .ctors word at 0x148 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here, and each hook is named from the entry offset it
// is stored into.
//
// It carries editor fields, so the type and label slots are filled. The flags word is 0x0; its width is what sets this run's length apart
// from others of the same shape.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void warpLoad(void);
extern "C" void warpUnload(void);
extern "C" void warpCreate(void);
extern "C" void warpReset(void);
extern "C" ObjectEntry warpEntry;
extern "C" char warpDisplayName[];
extern "C" char warpFieldTypes[];
extern "C" const char* warpFieldNames[];

extern "C" void warpRegister(void)
{
	warpEntry.flags = 0;
	warpEntry.unk18 = 0;

	warpEntry.name   = warpDisplayName;
	warpEntry.load   = warpLoad;
	warpEntry.unload = warpUnload;
	warpEntry.create = warpCreate;
	warpEntry.reset  = warpReset;

	warpEntry.flags = 0x0;
	warpEntry.unk18 = 0;
	warpEntry.unk20 = 30;
	warpEntry.unk1C = 128;
	warpEntry.unk1E = 2;
	warpEntry.unk21 = 0;

	warpEntry.fieldTypes = warpFieldTypes;
	warpEntry.fieldNames = warpFieldNames;

	if (warpEntry.fieldTypes != NULL) {
		warpEntry.flags |= 8;
	} else {
		warpEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const warpCtorEntry)(void) = warpRegister;
