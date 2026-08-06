#include "types.h"

// The record that registers S03 DOOR with the editor.
//
// The claim is .text 0x7A3FC to 0x7A494 and the .ctors word that names it.
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
extern "C" void s03DoorLoad(void);
extern "C" void s03DoorUnload(void);
extern "C" void s03DoorCreate(void);
extern "C" ObjectEntry s03DoorEntry;
extern "C" char s03DoorDisplayName[];

extern "C" void s03DoorRegister(void)
{
	s03DoorEntry.flags = 0;
	s03DoorEntry.unk18 = 0;

	s03DoorEntry.name   = s03DoorDisplayName;
	s03DoorEntry.load   = s03DoorLoad;
	s03DoorEntry.unload = s03DoorUnload;
	s03DoorEntry.create = s03DoorCreate;
	s03DoorEntry.reset  = NULL;

	s03DoorEntry.flags = 0x20000;
	s03DoorEntry.unk18 = 0;
	s03DoorEntry.unk20 = 0x14;
	s03DoorEntry.unk1C = 0x303;
	s03DoorEntry.unk1E = 2;
	s03DoorEntry.unk21 = 0;

	s03DoorEntry.fieldTypes = NULL;
	s03DoorEntry.fieldNames = NULL;

	if (s03DoorEntry.fieldTypes != NULL) {
		s03DoorEntry.flags |= 8;
	} else {
		s03DoorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03DoorCtorEntry)(void) = s03DoorRegister;
