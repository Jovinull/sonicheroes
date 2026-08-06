#include "types.h"

// The record that registers S03 Bridge with the editor.
//
// The claim is .text 0x79208 to 0x792A0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage03D carries this run.

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
extern "C" void s03BridgeLoad(void);
extern "C" void s03BridgeUnload(void);
extern "C" void s03BridgeCreate(void);
extern "C" ObjectEntry s03BridgeEntry;
extern "C" char s03BridgeDisplayName[];

extern "C" void s03BridgeRegister(void)
{
	s03BridgeEntry.flags = 0;
	s03BridgeEntry.unk18 = 0;

	s03BridgeEntry.name   = s03BridgeDisplayName;
	s03BridgeEntry.load   = s03BridgeLoad;
	s03BridgeEntry.unload = s03BridgeUnload;
	s03BridgeEntry.create = s03BridgeCreate;
	s03BridgeEntry.reset  = NULL;

	s03BridgeEntry.flags = 0x20000;
	s03BridgeEntry.unk18 = 0;
	s03BridgeEntry.unk20 = 0x14;
	s03BridgeEntry.unk1C = 0x304;
	s03BridgeEntry.unk1E = 2;
	s03BridgeEntry.unk21 = 0;

	s03BridgeEntry.fieldTypes = NULL;
	s03BridgeEntry.fieldNames = NULL;

	if (s03BridgeEntry.fieldTypes != NULL) {
		s03BridgeEntry.flags |= 8;
	} else {
		s03BridgeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03BridgeCtorEntry)(void) = s03BridgeRegister;
