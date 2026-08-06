#include "types.h"

// The record that registers S11LIGHT OBJECT with the editor.
//
// The claim is .text 0x8D6C4 to 0x8D76C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "if" is the field type string: one character per parameter the
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
extern "C" void s11lightObjectLoad(void);
extern "C" void s11lightObjectUnload(void);
extern "C" void s11lightObjectCreate(void);
extern "C" ObjectEntry s11lightObjectEntry;
extern "C" char s11lightObjectDisplayName[];
extern "C" char s11lightObjectFieldTypes[];
extern "C" const char* s11lightObjectFieldNames[];

extern "C" void s11lightObjectRegister(void)
{
	s11lightObjectEntry.flags = 0;
	s11lightObjectEntry.unk18 = 0;

	s11lightObjectEntry.name   = s11lightObjectDisplayName;
	s11lightObjectEntry.load   = s11lightObjectLoad;
	s11lightObjectEntry.unload = s11lightObjectUnload;
	s11lightObjectEntry.create = s11lightObjectCreate;
	s11lightObjectEntry.reset  = NULL;

	s11lightObjectEntry.flags = 0x20000;
	s11lightObjectEntry.unk18 = 0;
	s11lightObjectEntry.unk20 = 0x1e;
	s11lightObjectEntry.unk1C = 0x1180;
	s11lightObjectEntry.unk1E = 2;
	s11lightObjectEntry.unk21 = 0;

	s11lightObjectEntry.fieldTypes = s11lightObjectFieldTypes;
	s11lightObjectEntry.fieldNames = s11lightObjectFieldNames;

	if (s11lightObjectFieldTypes != NULL) {
		s11lightObjectEntry.flags |= 8;
	} else {
		s11lightObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11lightObjectCtorEntry)(void) = s11lightObjectRegister;
