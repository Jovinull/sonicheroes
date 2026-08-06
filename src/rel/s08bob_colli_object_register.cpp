#include "types.h"

// The record that registers S08BOB COLLI_OBJECT with the editor.
//
// The claim is .text 0xF4F08 to 0xF4FA8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void s08bobColliObjectCreate(void);
extern "C" void s08bobColliObjectReset(void);
extern "C" ObjectEntry s08bobColliObjectEntry;
extern "C" char s08bobColliObjectDisplayName[];
extern "C" char s08bobColliObjectFieldTypes[];
extern "C" const char* s08bobColliObjectFieldNames[];

extern "C" void s08bobColliObjectRegister(void)
{
	s08bobColliObjectEntry.flags = 0;
	s08bobColliObjectEntry.unk18 = 0;

	s08bobColliObjectEntry.name   = s08bobColliObjectDisplayName;
	s08bobColliObjectEntry.load   = NULL;
	s08bobColliObjectEntry.unload = NULL;
	s08bobColliObjectEntry.create = s08bobColliObjectCreate;
	s08bobColliObjectEntry.reset  = s08bobColliObjectReset;

	s08bobColliObjectEntry.flags = 0x20000;
	s08bobColliObjectEntry.unk18 = 0;
	s08bobColliObjectEntry.unk20 = 0x1e;
	s08bobColliObjectEntry.unk1C = 0x743;
	s08bobColliObjectEntry.unk1E = 2;
	s08bobColliObjectEntry.unk21 = 0;

	s08bobColliObjectEntry.fieldTypes = s08bobColliObjectFieldTypes;
	s08bobColliObjectEntry.fieldNames = s08bobColliObjectFieldNames;

	if (s08bobColliObjectFieldTypes != NULL) {
		s08bobColliObjectEntry.flags |= 8;
	} else {
		s08bobColliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s08bobColliObjectCtorEntry)(void)
    = s08bobColliObjectRegister;
