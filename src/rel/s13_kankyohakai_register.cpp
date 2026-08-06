#include "types.h"

// The record that registers S13 KANKYOHAKAI with the editor.
//
// The claim is .text 0x8AFA8 to 0x8B050 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void s13KankyohakaiLoad(void);
extern "C" void s13KankyohakaiUnload(void);
extern "C" void s13KankyohakaiCreate(void);
extern "C" ObjectEntry s13KankyohakaiEntry;
extern "C" char s13KankyohakaiDisplayName[];
extern "C" char s13KankyohakaiFieldTypes[];
extern "C" const char* s13KankyohakaiFieldNames[];

extern "C" void s13KankyohakaiRegister(void)
{
	s13KankyohakaiEntry.flags = 0;
	s13KankyohakaiEntry.unk18 = 0;

	s13KankyohakaiEntry.name   = s13KankyohakaiDisplayName;
	s13KankyohakaiEntry.load   = s13KankyohakaiLoad;
	s13KankyohakaiEntry.unload = s13KankyohakaiUnload;
	s13KankyohakaiEntry.create = s13KankyohakaiCreate;
	s13KankyohakaiEntry.reset  = NULL;

	s13KankyohakaiEntry.flags = 0x20000;
	s13KankyohakaiEntry.unk18 = 0;
	s13KankyohakaiEntry.unk20 = 0x32;
	s13KankyohakaiEntry.unk1C = 0x1320;
	s13KankyohakaiEntry.unk1E = 2;
	s13KankyohakaiEntry.unk21 = 0;

	s13KankyohakaiEntry.fieldTypes = s13KankyohakaiFieldTypes;
	s13KankyohakaiEntry.fieldNames = s13KankyohakaiFieldNames;

	if (s13KankyohakaiFieldTypes != NULL) {
		s13KankyohakaiEntry.flags |= 8;
	} else {
		s13KankyohakaiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13KankyohakaiCtorEntry)(void) = s13KankyohakaiRegister;
