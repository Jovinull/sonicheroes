#include "types.h"

// The record that registers S11FIRE OBJECT with the editor.
//
// The claim is .text 0x87BB8 to 0x87C68 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iiffcccc" is the field type string: one character per parameter the
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
extern "C" void s11fireObjectLoad(void);
extern "C" void s11fireObjectUnload(void);
extern "C" void s11fireObjectCreate(void);
extern "C" void s11fireObjectReset(void);
extern "C" ObjectEntry s11fireObjectEntry;
extern "C" char s11fireObjectDisplayName[];
extern "C" char s11fireObjectFieldTypes[];
extern "C" const char* s11fireObjectFieldNames[];

extern "C" void s11fireObjectRegister(void)
{
	s11fireObjectEntry.flags = 0;
	s11fireObjectEntry.unk18 = 0;

	s11fireObjectEntry.name   = s11fireObjectDisplayName;
	s11fireObjectEntry.load   = s11fireObjectLoad;
	s11fireObjectEntry.unload = s11fireObjectUnload;
	s11fireObjectEntry.create = s11fireObjectCreate;
	s11fireObjectEntry.reset  = s11fireObjectReset;

	s11fireObjectEntry.flags = 0x8020000;
	s11fireObjectEntry.unk18 = 0;
	s11fireObjectEntry.unk20 = 0x1e;
	s11fireObjectEntry.unk1C = 0x1104;
	s11fireObjectEntry.unk1E = 2;
	s11fireObjectEntry.unk21 = 0;

	s11fireObjectEntry.fieldTypes = s11fireObjectFieldTypes;
	s11fireObjectEntry.fieldNames = s11fireObjectFieldNames;

	if (s11fireObjectFieldTypes != NULL) {
		s11fireObjectEntry.flags |= 8;
	} else {
		s11fireObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11fireObjectCtorEntry)(void) = s11fireObjectRegister;
