#include "types.h"

// The record that registers S03 BigBridge2 with the editor.
//
// The claim is .text 0x7763C to 0x776E4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ffff" is the field type string: one character per parameter the
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
extern "C" void s03BigBridge2Load(void);
extern "C" void s03BigBridge2Unload(void);
extern "C" void s03BigBridge2Create(void);
extern "C" ObjectEntry s03BigBridge2Entry;
extern "C" char s03BigBridge2DisplayName[];
extern "C" char s03BigBridge2FieldTypes[];
extern "C" const char* s03BigBridge2FieldNames[];

extern "C" void s03BigBridge2Register(void)
{
	s03BigBridge2Entry.flags = 0;
	s03BigBridge2Entry.unk18 = 0;

	s03BigBridge2Entry.name   = s03BigBridge2DisplayName;
	s03BigBridge2Entry.load   = s03BigBridge2Load;
	s03BigBridge2Entry.unload = s03BigBridge2Unload;
	s03BigBridge2Entry.create = s03BigBridge2Create;
	s03BigBridge2Entry.reset  = NULL;

	s03BigBridge2Entry.flags = 0x20000;
	s03BigBridge2Entry.unk18 = 0;
	s03BigBridge2Entry.unk20 = 0x64;
	s03BigBridge2Entry.unk1C = 0x305;
	s03BigBridge2Entry.unk1E = 2;
	s03BigBridge2Entry.unk21 = 0;

	s03BigBridge2Entry.fieldTypes = s03BigBridge2FieldTypes;
	s03BigBridge2Entry.fieldNames = s03BigBridge2FieldNames;

	if (s03BigBridge2FieldTypes != NULL) {
		s03BigBridge2Entry.flags |= 8;
	} else {
		s03BigBridge2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03BigBridge2CtorEntry)(void) = s03BigBridge2Register;
