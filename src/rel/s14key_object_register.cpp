#include "types.h"

// The record that registers S14KEY OBJECT with the editor.
//
// The claim is .text 0xD0C30 to 0xD0CC8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s14keyObjectLoad(void);
extern "C" void s14keyObjectUnload(void);
extern "C" void s14keyObjectCreate(void);
extern "C" ObjectEntry s14keyObjectEntry;
extern "C" char s14keyObjectDisplayName[];

extern "C" void s14keyObjectRegister(void)
{
	s14keyObjectEntry.flags = 0;
	s14keyObjectEntry.unk18 = 0;

	s14keyObjectEntry.name   = s14keyObjectDisplayName;
	s14keyObjectEntry.load   = s14keyObjectLoad;
	s14keyObjectEntry.unload = s14keyObjectUnload;
	s14keyObjectEntry.create = s14keyObjectCreate;
	s14keyObjectEntry.reset  = NULL;

	s14keyObjectEntry.flags = 0x20000;
	s14keyObjectEntry.unk18 = 0;
	s14keyObjectEntry.unk20 = 0x1e;
	s14keyObjectEntry.unk1C = 0x140a;
	s14keyObjectEntry.unk1E = 2;
	s14keyObjectEntry.unk21 = 0;

	s14keyObjectEntry.fieldTypes = NULL;
	s14keyObjectEntry.fieldNames = NULL;

	if (s14keyObjectEntry.fieldTypes != NULL) {
		s14keyObjectEntry.flags |= 8;
	} else {
		s14keyObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14keyObjectCtorEntry)(void) = s14keyObjectRegister;
