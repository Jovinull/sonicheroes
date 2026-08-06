#include "types.h"

// The record that registers S03 EggCap with the editor.
//
// The claim is .text 0x7D48C to 0x7D534 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "css" is the field type string: one character per parameter the
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
extern "C" void s03EggCapLoad(void);
extern "C" void s03EggCapUnload(void);
extern "C" void s03EggCapCreate(void);
extern "C" ObjectEntry s03EggCapEntry;
extern "C" char s03EggCapDisplayName[];
extern "C" char s03EggCapFieldTypes[];
extern "C" const char* s03EggCapFieldNames[];

extern "C" void s03EggCapRegister(void)
{
	s03EggCapEntry.flags = 0;
	s03EggCapEntry.unk18 = 0;

	s03EggCapEntry.name   = s03EggCapDisplayName;
	s03EggCapEntry.load   = s03EggCapLoad;
	s03EggCapEntry.unload = s03EggCapUnload;
	s03EggCapEntry.create = s03EggCapCreate;
	s03EggCapEntry.reset  = NULL;

	s03EggCapEntry.flags = 0x20000;
	s03EggCapEntry.unk18 = 0;
	s03EggCapEntry.unk20 = 0x14;
	s03EggCapEntry.unk1C = 0x302;
	s03EggCapEntry.unk1E = 2;
	s03EggCapEntry.unk21 = 0;

	s03EggCapEntry.fieldTypes = s03EggCapFieldTypes;
	s03EggCapEntry.fieldNames = s03EggCapFieldNames;

	if (s03EggCapFieldTypes != NULL) {
		s03EggCapEntry.flags |= 8;
	} else {
		s03EggCapEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03EggCapCtorEntry)(void) = s03EggCapRegister;
