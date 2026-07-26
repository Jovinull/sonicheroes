#include "types.h"

// The record that registers SYSTEM OBJECT3 with the editor.
//
// The claim is .text 0x4DD78 to 0x4DE1C and the .ctors word that names it. Only the
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
extern "C" void systemObject3Load(void);
extern "C" void systemObject3Unload(void);
extern "C" void systemObject3Create(void);
extern "C" void systemObject3Reset(void);
extern "C" ObjectEntry systemObject3Entry;
extern "C" char systemObject3DisplayName[];

extern "C" void systemObject3Register(void)
{
	systemObject3Entry.flags = 0;
	systemObject3Entry.unk18 = 0;

	systemObject3Entry.name   = systemObject3DisplayName;
	systemObject3Entry.load   = systemObject3Load;
	systemObject3Entry.unload = systemObject3Unload;
	systemObject3Entry.create = systemObject3Create;
	systemObject3Entry.reset  = systemObject3Reset;

	systemObject3Entry.flags = 0x80;
	systemObject3Entry.unk18 = 0;
	systemObject3Entry.unk20 = 0x1E;
	systemObject3Entry.unk1C = 0xFFF2;
	systemObject3Entry.unk1E = 2;
	systemObject3Entry.unk21 = 0;

	systemObject3Entry.fieldTypes = NULL;
	systemObject3Entry.fieldNames = NULL;

	if (systemObject3Entry.fieldTypes != NULL) {
		systemObject3Entry.flags |= 8;
	} else {
		systemObject3Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const systemObject3CtorEntry)(void) = systemObject3Register;
