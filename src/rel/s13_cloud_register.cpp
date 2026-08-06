#include "types.h"

// The records that register S13 CLOUD1 and S13 Cloud2 with the editor.
//
// The claim is .text 0xC3C38 to 0xC3D74 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cssSSS" is S13 CLOUD1's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "cssSSSSs" is S13 Cloud2's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in three of the fourteen stage modules: 13D, 27D and 28D.

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
extern "C" void s13Cloud1Load(void);
extern "C" void s13Cloud1Create(void);
extern "C" ObjectEntry s13Cloud1Entry;
extern "C" char s13Cloud1DisplayName[];
extern "C" char s13Cloud1FieldTypes[];
extern "C" const char* s13Cloud1FieldNames[];

extern "C" void s13Cloud2Create(void);
extern "C" ObjectEntry s13Cloud2Entry;
extern "C" char s13Cloud2DisplayName[];
extern "C" char s13Cloud2FieldTypes[];
extern "C" const char* s13Cloud2FieldNames[];

extern "C" void s13Cloud1Register(void)
{
	s13Cloud1Entry.flags = 0;
	s13Cloud1Entry.unk18 = 0;

	s13Cloud1Entry.name   = s13Cloud1DisplayName;
	s13Cloud1Entry.load   = s13Cloud1Load;
	s13Cloud1Entry.unload = NULL;
	s13Cloud1Entry.create = s13Cloud1Create;
	s13Cloud1Entry.reset  = NULL;

	s13Cloud1Entry.flags = 0x1000;
	s13Cloud1Entry.unk18 = 0;
	s13Cloud1Entry.unk20 = 0x14;
	s13Cloud1Entry.unk1C = 0x1399;
	s13Cloud1Entry.unk1E = 2;
	s13Cloud1Entry.unk21 = 0;

	s13Cloud1Entry.fieldTypes = s13Cloud1FieldTypes;
	s13Cloud1Entry.fieldNames = s13Cloud1FieldNames;

	if (s13Cloud1FieldTypes != NULL) {
		s13Cloud1Entry.flags |= 8;
	} else {
		s13Cloud1Entry.flags &= ~8;
	}

	s13Cloud2Entry.flags = 0;
	s13Cloud2Entry.unk18 = 0;

	s13Cloud2Entry.name   = s13Cloud2DisplayName;
	s13Cloud2Entry.load   = s13Cloud1Load;
	s13Cloud2Entry.unload = NULL;
	s13Cloud2Entry.create = s13Cloud2Create;
	s13Cloud2Entry.reset  = NULL;

	s13Cloud2Entry.flags = 0x1000;
	s13Cloud2Entry.unk18 = 0;
	s13Cloud2Entry.unk20 = 0x14;
	s13Cloud2Entry.unk1C = 0x139a;
	s13Cloud2Entry.unk1E = 2;
	s13Cloud2Entry.unk21 = 0;

	s13Cloud2Entry.fieldTypes = s13Cloud2FieldTypes;
	s13Cloud2Entry.fieldNames = s13Cloud2FieldNames;

	if (s13Cloud2FieldTypes != NULL) {
		s13Cloud2Entry.flags |= 8;
	} else {
		s13Cloud2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13Cloud1CtorEntry)(void) = s13Cloud1Register;
