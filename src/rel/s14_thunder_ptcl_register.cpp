#include "types.h"

// The record that registers S14 THUNDER PTCL with the editor.
//
// The claim is .text 0xCA4F8 to 0xCA594 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "SSSssff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in three of the fourteen stage modules: 13D, 27D and 28D.

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
extern "C" void s14ThunderPtclCreate(void);
extern "C" ObjectEntry s14ThunderPtclEntry;
extern "C" char s14ThunderPtclDisplayName[];
extern "C" char s14ThunderPtclFieldTypes[];
extern "C" const char* s14ThunderPtclFieldNames[];

extern "C" void s14ThunderPtclRegister(void)
{
	s14ThunderPtclEntry.flags = 0;
	s14ThunderPtclEntry.unk18 = 0;

	s14ThunderPtclEntry.name   = s14ThunderPtclDisplayName;
	s14ThunderPtclEntry.load   = NULL;
	s14ThunderPtclEntry.unload = NULL;
	s14ThunderPtclEntry.create = s14ThunderPtclCreate;
	s14ThunderPtclEntry.reset  = NULL;

	s14ThunderPtclEntry.flags = 0x21000;
	s14ThunderPtclEntry.unk18 = 0;
	s14ThunderPtclEntry.unk20 = 0x32;
	s14ThunderPtclEntry.unk1C = 0x1482;
	s14ThunderPtclEntry.unk1E = 2;
	s14ThunderPtclEntry.unk21 = 0;

	s14ThunderPtclEntry.fieldTypes = s14ThunderPtclFieldTypes;
	s14ThunderPtclEntry.fieldNames = s14ThunderPtclFieldNames;

	if (s14ThunderPtclFieldTypes != NULL) {
		s14ThunderPtclEntry.flags |= 8;
	} else {
		s14ThunderPtclEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14ThunderPtclCtorEntry)(void) = s14ThunderPtclRegister;
