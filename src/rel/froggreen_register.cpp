#include "types.h"

// The record that registers FROGGREEN with the editor.
//
// The claim is .text 0x7717C to 0x7722C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFFFFFSSc" is the field type string: one character per parameter the
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
extern "C" void froggreenLoad(void);
extern "C" void froggreenUnload(void);
extern "C" void froggreenCreate(void);
extern "C" void froggreenReset(void);
extern "C" ObjectEntry froggreenEntry;
extern "C" char froggreenDisplayName[];
extern "C" char froggreenFieldTypes[];
extern "C" const char* froggreenFieldNames[];

extern "C" void froggreenRegister(void)
{
	froggreenEntry.flags = 0;
	froggreenEntry.unk18 = 0;

	froggreenEntry.name   = froggreenDisplayName;
	froggreenEntry.load   = froggreenLoad;
	froggreenEntry.unload = froggreenUnload;
	froggreenEntry.create = froggreenCreate;
	froggreenEntry.reset  = froggreenReset;

	froggreenEntry.flags = 0x20000;
	froggreenEntry.unk18 = 0;
	froggreenEntry.unk20 = 0xf;
	froggreenEntry.unk1C = 0x900;
	froggreenEntry.unk1E = 2;
	froggreenEntry.unk21 = 0;

	froggreenEntry.fieldTypes = froggreenFieldTypes;
	froggreenEntry.fieldNames = froggreenFieldNames;

	if (froggreenFieldTypes != NULL) {
		froggreenEntry.flags |= 8;
	} else {
		froggreenEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const froggreenCtorEntry)(void) = froggreenRegister;
