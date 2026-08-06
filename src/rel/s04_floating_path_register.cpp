#include "types.h"

// The record that registers S04 FLOATING PATH with the editor.
//
// The claim is .text 0xC3110 to 0xC31A8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fffff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s04FloatingPathCreate(void);
extern "C" ObjectEntry s04FloatingPathEntry;
extern "C" char s04FloatingPathDisplayName[];
extern "C" char s04FloatingPathFieldTypes[];
extern "C" const char* s04FloatingPathFieldNames[];

extern "C" void s04FloatingPathRegister(void)
{
	s04FloatingPathEntry.flags = 0;
	s04FloatingPathEntry.unk18 = 0;

	s04FloatingPathEntry.name   = s04FloatingPathDisplayName;
	s04FloatingPathEntry.load   = NULL;
	s04FloatingPathEntry.unload = NULL;
	s04FloatingPathEntry.create = s04FloatingPathCreate;
	s04FloatingPathEntry.reset  = NULL;

	s04FloatingPathEntry.flags = 0x20000;
	s04FloatingPathEntry.unk18 = 0;
	s04FloatingPathEntry.unk20 = 0x14;
	s04FloatingPathEntry.unk1C = 0x415;
	s04FloatingPathEntry.unk1E = 2;
	s04FloatingPathEntry.unk21 = 0;

	s04FloatingPathEntry.fieldTypes = s04FloatingPathFieldTypes;
	s04FloatingPathEntry.fieldNames = s04FloatingPathFieldNames;

	if (s04FloatingPathFieldTypes != NULL) {
		s04FloatingPathEntry.flags |= 8;
	} else {
		s04FloatingPathEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04FloatingPathCtorEntry)(void) = s04FloatingPathRegister;
