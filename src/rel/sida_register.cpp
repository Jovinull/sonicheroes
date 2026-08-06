#include "types.h"

// The record that registers SIDA with the editor.
//
// The claim is .text 0x8BB30 to 0x8BBE0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void sidaLoad(void);
extern "C" void sidaUnload(void);
extern "C" void sidaCreate(void);
extern "C" void sidaReset(void);
extern "C" ObjectEntry sidaEntry;
extern "C" char sidaDisplayName[];
extern "C" char sidaFieldTypes[];
extern "C" const char* sidaFieldNames[];

extern "C" void sidaRegister(void)
{
	sidaEntry.flags = 0;
	sidaEntry.unk18 = 0;

	sidaEntry.name   = sidaDisplayName;
	sidaEntry.load   = sidaLoad;
	sidaEntry.unload = sidaUnload;
	sidaEntry.create = sidaCreate;
	sidaEntry.reset  = sidaReset;

	sidaEntry.flags = 0x1000;
	sidaEntry.unk18 = 0;
	sidaEntry.unk20 = 0xa;
	sidaEntry.unk1C = 0x985;
	sidaEntry.unk1E = 2;
	sidaEntry.unk21 = 0;

	sidaEntry.fieldTypes = sidaFieldTypes;
	sidaEntry.fieldNames = sidaFieldNames;

	if (sidaFieldTypes != NULL) {
		sidaEntry.flags |= 8;
	} else {
		sidaEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const sidaCtorEntry)(void) = sidaRegister;
