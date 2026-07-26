#include "types.h"

// The record that registers SYSTEM OBJECT1 with the editor.
//
// The claim is .text 0x4D818 to 0x4D8BC and the .ctors word that names it. Only the
// record is taken: the four hooks it point at stay assembly and are reached by
// the names each module's symbols.txt gives them.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are a different revision this far in, and stage40D everywhere.
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
extern "C" void systemObject1Load(void);
extern "C" void systemObject1Unload(void);
extern "C" void systemObject1Create(void);
extern "C" void systemObject1Reset(void);
extern "C" ObjectEntry systemObject1Entry;
extern "C" char systemObject1DisplayName[];

extern "C" void systemObject1Register(void)
{
	systemObject1Entry.flags = 0;
	systemObject1Entry.unk18 = 0;

	systemObject1Entry.name   = systemObject1DisplayName;
	systemObject1Entry.load   = systemObject1Load;
	systemObject1Entry.unload = systemObject1Unload;
	systemObject1Entry.create = systemObject1Create;
	systemObject1Entry.reset  = systemObject1Reset;

	systemObject1Entry.flags = 0x80;
	systemObject1Entry.unk18 = 0;
	systemObject1Entry.unk20 = 0x1E;
	systemObject1Entry.unk1C = 0xFFF0;
	systemObject1Entry.unk1E = 2;
	systemObject1Entry.unk21 = 0;

	systemObject1Entry.fieldTypes = NULL;
	systemObject1Entry.fieldNames = NULL;

	if (systemObject1Entry.fieldTypes != NULL) {
		systemObject1Entry.flags |= 8;
	} else {
		systemObject1Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const systemObject1CtorEntry)(void) = systemObject1Register;
