#include "types.h"

// The record that registers S04 EggCap2 with the editor.
//
// The claim is .text 0x8C6CC to 0x8C774 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s04EggCap2Load(void);
extern "C" void s04EggCap2Unload(void);
extern "C" void s04EggCap2Create(void);
extern "C" ObjectEntry s04EggCap2Entry;
extern "C" char s04EggCap2DisplayName[];
extern "C" char s04EggCap2FieldTypes[];
extern "C" const char* s04EggCap2FieldNames[];

extern "C" void s04EggCap2Register(void)
{
	s04EggCap2Entry.flags = 0;
	s04EggCap2Entry.unk18 = 0;

	s04EggCap2Entry.name   = s04EggCap2DisplayName;
	s04EggCap2Entry.load   = s04EggCap2Load;
	s04EggCap2Entry.unload = s04EggCap2Unload;
	s04EggCap2Entry.create = s04EggCap2Create;
	s04EggCap2Entry.reset  = NULL;

	s04EggCap2Entry.flags = 0x20000;
	s04EggCap2Entry.unk18 = 0;
	s04EggCap2Entry.unk20 = 0x14;
	s04EggCap2Entry.unk1C = 0x408;
	s04EggCap2Entry.unk1E = 2;
	s04EggCap2Entry.unk21 = 0;

	s04EggCap2Entry.fieldTypes = s04EggCap2FieldTypes;
	s04EggCap2Entry.fieldNames = s04EggCap2FieldNames;

	if (s04EggCap2FieldTypes != NULL) {
		s04EggCap2Entry.flags |= 8;
	} else {
		s04EggCap2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04EggCap2CtorEntry)(void) = s04EggCap2Register;
