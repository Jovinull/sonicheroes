#include "types.h"

// The record that registers RAILWATERSUPPLY with the editor.
//
// The claim is .text 0x717BC to 0x7185C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void railwatersupplyLoad(void);
extern "C" void railwatersupplyUnload(void);
extern "C" void railwatersupplyCreate(void);
extern "C" void railwatersupplyReset(void);
extern "C" ObjectEntry railwatersupplyEntry;
extern "C" char railwatersupplyDisplayName[];

extern "C" void railwatersupplyRegister(void)
{
	railwatersupplyEntry.flags = 0;
	railwatersupplyEntry.unk18 = 0;

	railwatersupplyEntry.name   = railwatersupplyDisplayName;
	railwatersupplyEntry.load   = railwatersupplyLoad;
	railwatersupplyEntry.unload = railwatersupplyUnload;
	railwatersupplyEntry.create = railwatersupplyCreate;
	railwatersupplyEntry.reset  = railwatersupplyReset;

	railwatersupplyEntry.flags = 0x1000;
	railwatersupplyEntry.unk18 = 0;
	railwatersupplyEntry.unk20 = 0xf;
	railwatersupplyEntry.unk1C = 0x786;
	railwatersupplyEntry.unk1E = 2;
	railwatersupplyEntry.unk21 = 0;

	railwatersupplyEntry.fieldTypes = NULL;
	railwatersupplyEntry.fieldNames = NULL;

	if (railwatersupplyEntry.fieldTypes != NULL) {
		railwatersupplyEntry.flags |= 8;
	} else {
		railwatersupplyEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railwatersupplyCtorEntry)(void) = railwatersupplyRegister;
