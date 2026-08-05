#include "types.h"

// The record that registers S01 TRUCK PATH with the editor.
//
// The claim is .text 0x9261C to 0x926B4 and the .ctors word at 0xFC that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It installs no load or unload hook, only a create one, so those two
// slots take NULL.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void s01TruckPathCreate(void);
extern "C" ObjectEntry s01TruckPathEntry;
extern "C" char s01TruckPathDisplayName[];
extern "C" char s01TruckPathFieldTypes[];
extern "C" const char* s01TruckPathFieldNames[];

extern "C" void s01TruckPathRegister(void)
{
	s01TruckPathEntry.flags = 0;
	s01TruckPathEntry.unk18 = 0;

	s01TruckPathEntry.name   = s01TruckPathDisplayName;
	s01TruckPathEntry.load   = NULL;
	s01TruckPathEntry.unload = NULL;
	s01TruckPathEntry.create = s01TruckPathCreate;
	s01TruckPathEntry.unk10  = NULL;

	s01TruckPathEntry.flags = 0x20000;
	s01TruckPathEntry.unk18 = 0;
	s01TruckPathEntry.unk20 = 100;
	s01TruckPathEntry.unk1C = 259;
	s01TruckPathEntry.unk1E = 2;
	s01TruckPathEntry.unk21 = 0;

	s01TruckPathEntry.fieldTypes = s01TruckPathFieldTypes;
	s01TruckPathEntry.fieldNames = s01TruckPathFieldNames;

	if (s01TruckPathEntry.fieldTypes != NULL) {
		s01TruckPathEntry.flags |= 8;
	} else {
		s01TruckPathEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s01TruckPathCtorEntry)(void) = s01TruckPathRegister;
