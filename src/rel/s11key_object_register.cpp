#include "types.h"

// The record that registers S11KEY OBJECT with the editor.
//
// The claim is .text 0xCBB18 to 0xCBBB0 and the .ctors word that names it.
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
extern "C" void s11keyObjectLoad(void);
extern "C" void s11keyObjectUnload(void);
extern "C" void s11keyObjectCreate(void);
extern "C" ObjectEntry s11keyObjectEntry;
extern "C" char s11keyObjectDisplayName[];

extern "C" void s11keyObjectRegister(void)
{
	s11keyObjectEntry.flags = 0;
	s11keyObjectEntry.unk18 = 0;

	s11keyObjectEntry.name   = s11keyObjectDisplayName;
	s11keyObjectEntry.load   = s11keyObjectLoad;
	s11keyObjectEntry.unload = s11keyObjectUnload;
	s11keyObjectEntry.create = s11keyObjectCreate;
	s11keyObjectEntry.reset  = NULL;

	s11keyObjectEntry.flags = 0x20000;
	s11keyObjectEntry.unk18 = 0;
	s11keyObjectEntry.unk20 = 0x1e;
	s11keyObjectEntry.unk1C = 0x1109;
	s11keyObjectEntry.unk1E = 2;
	s11keyObjectEntry.unk21 = 0;

	s11keyObjectEntry.fieldTypes = NULL;
	s11keyObjectEntry.fieldNames = NULL;

	if (s11keyObjectEntry.fieldTypes != NULL) {
		s11keyObjectEntry.flags |= 8;
	} else {
		s11keyObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11keyObjectCtorEntry)(void) = s11keyObjectRegister;
