#include "types.h"

// The record that registers SPRING_MUSH with the editor.
//
// The claim is .text 0x8CD4C to 0x8CDFC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FC" is the field type string: one character per parameter the
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
extern "C" void springMushLoad(void);
extern "C" void springMushUnload(void);
extern "C" void springMushCreate(void);
extern "C" void springMushReset(void);
extern "C" ObjectEntry springMushEntry;
extern "C" char springMushDisplayName[];
extern "C" char springMushFieldTypes[];
extern "C" const char* springMushFieldNames[];

extern "C" void springMushRegister(void)
{
	springMushEntry.flags = 0;
	springMushEntry.unk18 = 0;

	springMushEntry.name   = springMushDisplayName;
	springMushEntry.load   = springMushLoad;
	springMushEntry.unload = springMushUnload;
	springMushEntry.create = springMushCreate;
	springMushEntry.reset  = springMushReset;

	springMushEntry.flags = 0x20000;
	springMushEntry.unk18 = 0;
	springMushEntry.unk20 = 0xa;
	springMushEntry.unk1C = 0x909;
	springMushEntry.unk1E = 2;
	springMushEntry.unk21 = 0;

	springMushEntry.fieldTypes = springMushFieldTypes;
	springMushEntry.fieldNames = springMushFieldNames;

	if (springMushFieldTypes != NULL) {
		springMushEntry.flags |= 8;
	} else {
		springMushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const springMushCtorEntry)(void) = springMushRegister;
