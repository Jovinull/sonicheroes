#include "types.h"

// The record that registers S12WALL OBJECT with the editor.
//
// The claim is .text 0x930BC to 0x93164 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage11D carries this run.

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
extern "C" void s12wallObjectLoad(void);
extern "C" void s12wallObjectUnload(void);
extern "C" void s12wallObjectCreate(void);
extern "C" ObjectEntry s12wallObjectEntry;
extern "C" char s12wallObjectDisplayName[];
extern "C" char s12wallObjectFieldTypes[];
extern "C" const char* s12wallObjectFieldNames[];

extern "C" void s12wallObjectRegister(void)
{
	s12wallObjectEntry.flags = 0;
	s12wallObjectEntry.unk18 = 0;

	s12wallObjectEntry.name   = s12wallObjectDisplayName;
	s12wallObjectEntry.load   = s12wallObjectLoad;
	s12wallObjectEntry.unload = s12wallObjectUnload;
	s12wallObjectEntry.create = s12wallObjectCreate;
	s12wallObjectEntry.reset  = NULL;

	s12wallObjectEntry.flags = 0x20000;
	s12wallObjectEntry.unk18 = 0;
	s12wallObjectEntry.unk20 = 0x1e;
	s12wallObjectEntry.unk1C = 0x1107;
	s12wallObjectEntry.unk1E = 2;
	s12wallObjectEntry.unk21 = 0;

	s12wallObjectEntry.fieldTypes = s12wallObjectFieldTypes;
	s12wallObjectEntry.fieldNames = s12wallObjectFieldNames;

	if (s12wallObjectFieldTypes != NULL) {
		s12wallObjectEntry.flags |= 8;
	} else {
		s12wallObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12wallObjectCtorEntry)(void) = s12wallObjectRegister;
