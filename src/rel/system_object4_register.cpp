#include "types.h"

// The record that registers SYSTEM OBJECT4 with the editor.
//
// The claim is .text 0x4E000 to 0x4E0A4 and the .ctors word that names it. Only the
// record is taken: the four hooks it point at stay assembly and are reached by
// the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// The four system objects are the same record with a different index: their
// counts run 0xFFF0 through 0xFFF3, which is what the shift and subtract at the
// halfword store builds. None of them expose a parameter to the editor, so the
// type string and the label array are null, and the test at the end reads the
// type pointer back out of the record: from a local the compiler would fold the
// branch away.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void);     // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	u16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
} ObjectEntry;               // 0x2C

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void systemObject4Load(void);
extern "C" void systemObject4Unload(void);
extern "C" void systemObject4Create(void);
extern "C" void systemObject4Reset(void);
extern "C" ObjectEntry systemObject4Entry;
extern "C" char systemObject4DisplayName[];

extern "C" void systemObject4Register(void)
{
	systemObject4Entry.flags = 0;
	systemObject4Entry.unk18 = 0;

	systemObject4Entry.name   = systemObject4DisplayName;
	systemObject4Entry.load   = systemObject4Load;
	systemObject4Entry.unload = systemObject4Unload;
	systemObject4Entry.create = systemObject4Create;
	systemObject4Entry.reset  = systemObject4Reset;

	systemObject4Entry.flags = 0x80;
	systemObject4Entry.unk18 = 0;
	systemObject4Entry.unk20 = 0x1E;
	systemObject4Entry.unk1C = 0xFFF3;
	systemObject4Entry.unk1E = 2;
	systemObject4Entry.unk21 = 0;

	systemObject4Entry.fieldTypes = NULL;
	systemObject4Entry.fieldNames = NULL;

	if (systemObject4Entry.fieldTypes != NULL) {
		systemObject4Entry.flags |= 8;
	} else {
		systemObject4Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const systemObject4CtorEntry)(void) = systemObject4Register;
