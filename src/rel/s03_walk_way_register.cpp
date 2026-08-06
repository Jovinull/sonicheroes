#include "types.h"

// The record that registers S03 WalkWay with the editor.
//
// The claim is .text 0x87004 to 0x870AC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ffff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void s03WalkWayLoad(void);
extern "C" void s03WalkWayUnload(void);
extern "C" void s03WalkWayCreate(void);
extern "C" ObjectEntry s03WalkWayEntry;
extern "C" char s03WalkWayDisplayName[];
extern "C" char s03WalkWayFieldTypes[];
extern "C" const char* s03WalkWayFieldNames[];

extern "C" void s03WalkWayRegister(void)
{
	s03WalkWayEntry.flags = 0;
	s03WalkWayEntry.unk18 = 0;

	s03WalkWayEntry.name   = s03WalkWayDisplayName;
	s03WalkWayEntry.load   = s03WalkWayLoad;
	s03WalkWayEntry.unload = s03WalkWayUnload;
	s03WalkWayEntry.create = s03WalkWayCreate;
	s03WalkWayEntry.reset  = NULL;

	s03WalkWayEntry.flags = 0x20000;
	s03WalkWayEntry.unk18 = 0;
	s03WalkWayEntry.unk20 = 0x14;
	s03WalkWayEntry.unk1C = 0x308;
	s03WalkWayEntry.unk1E = 2;
	s03WalkWayEntry.unk21 = 0;

	s03WalkWayEntry.fieldTypes = s03WalkWayFieldTypes;
	s03WalkWayEntry.fieldNames = s03WalkWayFieldNames;

	if (s03WalkWayFieldTypes != NULL) {
		s03WalkWayEntry.flags |= 8;
	} else {
		s03WalkWayEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03WalkWayCtorEntry)(void) = s03WalkWayRegister;
