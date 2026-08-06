#include "types.h"

// The record that registers S14 FALL ASHIBA with the editor.
//
// The claim is .text 0x9807C to 0x98124 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void s14FallAshibaLoad(void);
extern "C" void s14FallAshibaUnload(void);
extern "C" void s14FallAshibaCreate(void);
extern "C" ObjectEntry s14FallAshibaEntry;
extern "C" char s14FallAshibaDisplayName[];
extern "C" char s14FallAshibaFieldTypes[];
extern "C" const char* s14FallAshibaFieldNames[];

extern "C" void s14FallAshibaRegister(void)
{
	s14FallAshibaEntry.flags = 0;
	s14FallAshibaEntry.unk18 = 0;

	s14FallAshibaEntry.name   = s14FallAshibaDisplayName;
	s14FallAshibaEntry.load   = s14FallAshibaLoad;
	s14FallAshibaEntry.unload = s14FallAshibaUnload;
	s14FallAshibaEntry.create = s14FallAshibaCreate;
	s14FallAshibaEntry.reset  = NULL;

	s14FallAshibaEntry.flags = 0x20000;
	s14FallAshibaEntry.unk18 = 0;
	s14FallAshibaEntry.unk20 = 0x32;
	s14FallAshibaEntry.unk1C = 0x1400;
	s14FallAshibaEntry.unk1E = 2;
	s14FallAshibaEntry.unk21 = 0;

	s14FallAshibaEntry.fieldTypes = s14FallAshibaFieldTypes;
	s14FallAshibaEntry.fieldNames = s14FallAshibaFieldNames;

	if (s14FallAshibaFieldTypes != NULL) {
		s14FallAshibaEntry.flags |= 8;
	} else {
		s14FallAshibaEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14FallAshibaCtorEntry)(void) = s14FallAshibaRegister;
