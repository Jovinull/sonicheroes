#include "types.h"

// The records that register S14 Thunder and S14 Thunder2 with the editor.
//
// The claim is .text 0xA12A0 to 0xA13F4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "SSSff" is S14 Thunder's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "SSSssff" is S14 Thunder2's field type string: one character per parameter the
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
extern "C" void s14ThunderLoad(void);
extern "C" void s14ThunderUnload(void);
extern "C" void s14ThunderCreate(void);
extern "C" ObjectEntry s14ThunderEntry;
extern "C" char s14ThunderDisplayName[];
extern "C" char s14ThunderFieldTypes[];
extern "C" const char* s14ThunderFieldNames[];

extern "C" void s14Thunder2Create(void);
extern "C" ObjectEntry s14Thunder2Entry;
extern "C" char s14Thunder2DisplayName[];
extern "C" char s14Thunder2FieldTypes[];
extern "C" const char* s14Thunder2FieldNames[];

extern "C" void s14ThunderRegister(void)
{
	s14ThunderEntry.flags = 0;
	s14ThunderEntry.unk18 = 0;

	s14ThunderEntry.name   = s14ThunderDisplayName;
	s14ThunderEntry.load   = s14ThunderLoad;
	s14ThunderEntry.unload = s14ThunderUnload;
	s14ThunderEntry.create = s14ThunderCreate;
	s14ThunderEntry.reset  = NULL;

	s14ThunderEntry.flags = 0x21000;
	s14ThunderEntry.unk18 = 0;
	s14ThunderEntry.unk20 = 0x32;
	s14ThunderEntry.unk1C = 0x1480;
	s14ThunderEntry.unk1E = 2;
	s14ThunderEntry.unk21 = 0x0;

	s14ThunderEntry.fieldTypes = s14ThunderFieldTypes;
	s14ThunderEntry.fieldNames = s14ThunderFieldNames;

	if (s14ThunderFieldTypes != NULL) {
		s14ThunderEntry.flags |= 8;
	} else {
		s14ThunderEntry.flags &= ~8;
	}

	s14Thunder2Entry.flags = 0;
	s14Thunder2Entry.unk18 = 0;

	s14Thunder2Entry.name   = s14Thunder2DisplayName;
	s14Thunder2Entry.load   = s14ThunderLoad;
	s14Thunder2Entry.unload = s14ThunderUnload;
	s14Thunder2Entry.create = s14Thunder2Create;
	s14Thunder2Entry.reset  = NULL;

	s14Thunder2Entry.flags = 0x21000;
	s14Thunder2Entry.unk18 = 0;
	s14Thunder2Entry.unk20 = 0x32;
	s14Thunder2Entry.unk1C = 0x1481;
	s14Thunder2Entry.unk1E = 2;
	s14Thunder2Entry.unk21 = 0x0;

	s14Thunder2Entry.fieldTypes = s14Thunder2FieldTypes;
	s14Thunder2Entry.fieldNames = s14Thunder2FieldNames;

	if (s14Thunder2FieldTypes != NULL) {
		s14Thunder2Entry.flags |= 8;
	} else {
		s14Thunder2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14ThunderCtorEntry)(void) = s14ThunderRegister;
