#include "types.h"

// The record that registers S03 Aircar with the editor.
//
// The claim is .text 0x73650 to 0x736FC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccssfff" is the field type string: one character per parameter the
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
extern "C" void s03AircarLoad(void);
extern "C" void s03AircarUnload(void);
extern "C" void s03AircarCreate(void);
extern "C" ObjectEntry s03AircarEntry;
extern "C" char s03AircarDisplayName[];
extern "C" char s03AircarFieldTypes[];
extern "C" const char* s03AircarFieldNames[];

extern "C" void s03AircarRegister(void)
{
	s03AircarEntry.flags = 0;
	s03AircarEntry.unk18 = 0;

	s03AircarEntry.name   = s03AircarDisplayName;
	s03AircarEntry.load   = s03AircarLoad;
	s03AircarEntry.unload = s03AircarUnload;
	s03AircarEntry.create = s03AircarCreate;
	s03AircarEntry.reset  = NULL;

	s03AircarEntry.flags = 0x21000;
	s03AircarEntry.unk18 = 0;
	s03AircarEntry.unk20 = 0x32;
	s03AircarEntry.unk1C = 0x306;
	s03AircarEntry.unk1E = 2;
	s03AircarEntry.unk21 = 0;

	s03AircarEntry.fieldTypes = s03AircarFieldTypes;
	s03AircarEntry.fieldNames = s03AircarFieldNames;

	if (s03AircarFieldTypes != NULL) {
		s03AircarEntry.flags |= 8;
	} else {
		s03AircarEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03AircarCtorEntry)(void) = s03AircarRegister;
