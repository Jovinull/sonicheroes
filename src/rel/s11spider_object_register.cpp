#include "types.h"

// The record that registers S11SPIDER OBJECT with the editor.
//
// The claim is .text 0xC3738 to 0xC37E0 and the .ctors word that names it.
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
extern "C" void s11spiderObjectLoad(void);
extern "C" void s11spiderObjectUnload(void);
extern "C" void s11spiderObjectCreate(void);
extern "C" ObjectEntry s11spiderObjectEntry;
extern "C" char s11spiderObjectDisplayName[];
extern "C" char s11spiderObjectFieldTypes[];
extern "C" const char* s11spiderObjectFieldNames[];

extern "C" void s11spiderObjectRegister(void)
{
	s11spiderObjectEntry.flags = 0;
	s11spiderObjectEntry.unk18 = 0;

	s11spiderObjectEntry.name   = s11spiderObjectDisplayName;
	s11spiderObjectEntry.load   = s11spiderObjectLoad;
	s11spiderObjectEntry.unload = s11spiderObjectUnload;
	s11spiderObjectEntry.create = s11spiderObjectCreate;
	s11spiderObjectEntry.reset  = NULL;

	s11spiderObjectEntry.flags = 0x20000;
	s11spiderObjectEntry.unk18 = 0;
	s11spiderObjectEntry.unk20 = 0x1e;
	s11spiderObjectEntry.unk1C = 0x1189;
	s11spiderObjectEntry.unk1E = 2;
	s11spiderObjectEntry.unk21 = 0;

	s11spiderObjectEntry.fieldTypes = s11spiderObjectFieldTypes;
	s11spiderObjectEntry.fieldNames = s11spiderObjectFieldNames;

	if (s11spiderObjectFieldTypes != NULL) {
		s11spiderObjectEntry.flags |= 8;
	} else {
		s11spiderObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11spiderObjectCtorEntry)(void) = s11spiderObjectRegister;
