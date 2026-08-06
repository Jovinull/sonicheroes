#include "types.h"

// The record that registers S11DOOR OBJECT with the editor.
//
// The claim is .text 0x966B8 to 0x96760 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s11doorObjectLoad(void);
extern "C" void s11doorObjectUnload(void);
extern "C" void s11doorObjectCreate(void);
extern "C" ObjectEntry s11doorObjectEntry;
extern "C" char s11doorObjectDisplayName[];
extern "C" char s11doorObjectFieldTypes[];
extern "C" const char* s11doorObjectFieldNames[];

extern "C" void s11doorObjectRegister(void)
{
	s11doorObjectEntry.flags = 0;
	s11doorObjectEntry.unk18 = 0;

	s11doorObjectEntry.name   = s11doorObjectDisplayName;
	s11doorObjectEntry.load   = s11doorObjectLoad;
	s11doorObjectEntry.unload = s11doorObjectUnload;
	s11doorObjectEntry.create = s11doorObjectCreate;
	s11doorObjectEntry.reset  = NULL;

	s11doorObjectEntry.flags = 0x20000;
	s11doorObjectEntry.unk18 = 0;
	s11doorObjectEntry.unk20 = 0x1e;
	s11doorObjectEntry.unk1C = 0x1101;
	s11doorObjectEntry.unk1E = 2;
	s11doorObjectEntry.unk21 = 0;

	s11doorObjectEntry.fieldTypes = s11doorObjectFieldTypes;
	s11doorObjectEntry.fieldNames = s11doorObjectFieldNames;

	if (s11doorObjectFieldTypes != NULL) {
		s11doorObjectEntry.flags |= 8;
	} else {
		s11doorObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11doorObjectCtorEntry)(void) = s11doorObjectRegister;
