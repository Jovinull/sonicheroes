#include "types.h"

// The record that registers S14 ROADLIGHT with the editor.
//
// The claim is .text 0xC8F3C to 0xC8FE4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ff" is the field type string: one character per parameter the
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
extern "C" void s14RoadlightLoad(void);
extern "C" void s14RoadlightUnload(void);
extern "C" void s14RoadlightCreate(void);
extern "C" ObjectEntry s14RoadlightEntry;
extern "C" char s14RoadlightDisplayName[];
extern "C" char s14RoadlightFieldTypes[];
extern "C" const char* s14RoadlightFieldNames[];

extern "C" void s14RoadlightRegister(void)
{
	s14RoadlightEntry.flags = 0;
	s14RoadlightEntry.unk18 = 0;

	s14RoadlightEntry.name   = s14RoadlightDisplayName;
	s14RoadlightEntry.load   = s14RoadlightLoad;
	s14RoadlightEntry.unload = s14RoadlightUnload;
	s14RoadlightEntry.create = s14RoadlightCreate;
	s14RoadlightEntry.reset  = NULL;

	s14RoadlightEntry.flags = 0x1000;
	s14RoadlightEntry.unk18 = 0;
	s14RoadlightEntry.unk20 = 0xa;
	s14RoadlightEntry.unk1C = 0x1487;
	s14RoadlightEntry.unk1E = 2;
	s14RoadlightEntry.unk21 = 0;

	s14RoadlightEntry.fieldTypes = s14RoadlightFieldTypes;
	s14RoadlightEntry.fieldNames = s14RoadlightFieldNames;

	if (s14RoadlightFieldTypes != NULL) {
		s14RoadlightEntry.flags |= 8;
	} else {
		s14RoadlightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14RoadlightCtorEntry)(void) = s14RoadlightRegister;
