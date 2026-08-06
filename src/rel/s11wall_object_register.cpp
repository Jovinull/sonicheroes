#include "types.h"

// The record that registers S11WALL OBJECT with the editor.
//
// The claim is .text 0x91DB4 to 0x91E5C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ic" is the field type string: one character per parameter the
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
extern "C" void s11wallObjectLoad(void);
extern "C" void s11wallObjectUnload(void);
extern "C" void s11wallObjectCreate(void);
extern "C" ObjectEntry s11wallObjectEntry;
extern "C" char s11wallObjectDisplayName[];
extern "C" char s11wallObjectFieldTypes[];
extern "C" const char* s11wallObjectFieldNames[];

extern "C" void s11wallObjectRegister(void)
{
	s11wallObjectEntry.flags = 0;
	s11wallObjectEntry.unk18 = 0;

	s11wallObjectEntry.name   = s11wallObjectDisplayName;
	s11wallObjectEntry.load   = s11wallObjectLoad;
	s11wallObjectEntry.unload = s11wallObjectUnload;
	s11wallObjectEntry.create = s11wallObjectCreate;
	s11wallObjectEntry.reset  = NULL;

	s11wallObjectEntry.flags = 0x20000;
	s11wallObjectEntry.unk18 = 0;
	s11wallObjectEntry.unk20 = 0x1e;
	s11wallObjectEntry.unk1C = 0x1102;
	s11wallObjectEntry.unk1E = 2;
	s11wallObjectEntry.unk21 = 0;

	s11wallObjectEntry.fieldTypes = s11wallObjectFieldTypes;
	s11wallObjectEntry.fieldNames = s11wallObjectFieldNames;

	if (s11wallObjectFieldTypes != NULL) {
		s11wallObjectEntry.flags |= 8;
	} else {
		s11wallObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11wallObjectCtorEntry)(void) = s11wallObjectRegister;
