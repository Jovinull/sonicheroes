#include "types.h"

// The record that registers S04D ASHIBA with the editor.
//
// The claim is .text 0x97EA0 to 0x97F48 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s04dAshibaLoad(void);
extern "C" void s04dAshibaUnload(void);
extern "C" void s04dAshibaCreate(void);
extern "C" ObjectEntry s04dAshibaEntry;
extern "C" char s04dAshibaDisplayName[];
extern "C" char s04dAshibaFieldTypes[];
extern "C" const char* s04dAshibaFieldNames[];

extern "C" void s04dAshibaRegister(void)
{
	s04dAshibaEntry.flags = 0;
	s04dAshibaEntry.unk18 = 0;

	s04dAshibaEntry.name   = s04dAshibaDisplayName;
	s04dAshibaEntry.load   = s04dAshibaLoad;
	s04dAshibaEntry.unload = s04dAshibaUnload;
	s04dAshibaEntry.create = s04dAshibaCreate;
	s04dAshibaEntry.reset  = NULL;

	s04dAshibaEntry.flags = 0x20000;
	s04dAshibaEntry.unk18 = 0;
	s04dAshibaEntry.unk20 = 0x32;
	s04dAshibaEntry.unk1C = 0x403;
	s04dAshibaEntry.unk1E = 2;
	s04dAshibaEntry.unk21 = 0;

	s04dAshibaEntry.fieldTypes = s04dAshibaFieldTypes;
	s04dAshibaEntry.fieldNames = s04dAshibaFieldNames;

	if (s04dAshibaFieldTypes != NULL) {
		s04dAshibaEntry.flags |= 8;
	} else {
		s04dAshibaEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dAshibaCtorEntry)(void) = s04dAshibaRegister;
