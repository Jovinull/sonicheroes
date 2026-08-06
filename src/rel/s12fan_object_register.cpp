#include "types.h"

// The record that registers S12FAN OBJECT with the editor.
//
// The claim is .text 0xC3F60 to 0xC3FF8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s12fanObjectLoad(void);
extern "C" void s12fanObjectUnload(void);
extern "C" void s12fanObjectCreate(void);
extern "C" ObjectEntry s12fanObjectEntry;
extern "C" char s12fanObjectDisplayName[];

extern "C" void s12fanObjectRegister(void)
{
	s12fanObjectEntry.flags = 0;
	s12fanObjectEntry.unk18 = 0;

	s12fanObjectEntry.name   = s12fanObjectDisplayName;
	s12fanObjectEntry.load   = s12fanObjectLoad;
	s12fanObjectEntry.unload = s12fanObjectUnload;
	s12fanObjectEntry.create = s12fanObjectCreate;
	s12fanObjectEntry.reset  = NULL;

	s12fanObjectEntry.flags = 0x20000;
	s12fanObjectEntry.unk18 = 0;
	s12fanObjectEntry.unk20 = 0x1e;
	s12fanObjectEntry.unk1C = 0x1187;
	s12fanObjectEntry.unk1E = 2;
	s12fanObjectEntry.unk21 = 0;

	s12fanObjectEntry.fieldTypes = NULL;
	s12fanObjectEntry.fieldNames = NULL;

	if (s12fanObjectEntry.fieldTypes != NULL) {
		s12fanObjectEntry.flags |= 8;
	} else {
		s12fanObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12fanObjectCtorEntry)(void) = s12fanObjectRegister;
