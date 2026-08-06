#include "types.h"

// The records that register STG26 COLLI CC and STG26 COLLI CP with the editor.
//
// The claim is .text 0x756F4 to 0x75840 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fii" is STG26 COLLI CC's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "fii" is STG26 COLLI CP's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage26D carries this run.

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
extern "C" void stg26ColliCcLoad(void);
extern "C" void stg26ColliCcUnload(void);
extern "C" void stg26ColliCcCreate(void);
extern "C" ObjectEntry stg26ColliCcEntry;
extern "C" char stg26ColliCcDisplayName[];
extern "C" char stg26ColliCcFieldTypes[];
extern "C" const char* stg26ColliCcFieldNames[];

extern "C" void stg26ColliCpCreate(void);
extern "C" ObjectEntry stg26ColliCpEntry;
extern "C" char stg26ColliCpDisplayName[];

extern "C" void stg26ColliCcRegister(void)
{
	stg26ColliCcEntry.flags = 0;
	stg26ColliCcEntry.unk18 = 0;

	stg26ColliCcEntry.name   = stg26ColliCcDisplayName;
	stg26ColliCcEntry.load   = stg26ColliCcLoad;
	stg26ColliCcEntry.unload = stg26ColliCcUnload;
	stg26ColliCcEntry.create = stg26ColliCcCreate;
	stg26ColliCcEntry.reset  = NULL;

	stg26ColliCcEntry.flags = 0x400;
	stg26ColliCcEntry.unk18 = 0;
	stg26ColliCcEntry.unk20 = 0x7f;
	stg26ColliCcEntry.unk1C = 0x1600;
	stg26ColliCcEntry.unk1E = 2;
	stg26ColliCcEntry.unk21 = 0x0;

	stg26ColliCcEntry.fieldTypes = stg26ColliCcFieldTypes;
	stg26ColliCcEntry.fieldNames = stg26ColliCcFieldNames;

	if (stg26ColliCcFieldTypes != NULL) {
		stg26ColliCcEntry.flags |= 8;
	} else {
		stg26ColliCcEntry.flags &= ~8;
	}

	stg26ColliCpEntry.flags = 0;
	stg26ColliCpEntry.unk18 = 0;

	stg26ColliCpEntry.name   = stg26ColliCpDisplayName;
	stg26ColliCpEntry.load   = stg26ColliCcLoad;
	stg26ColliCpEntry.unload = stg26ColliCcUnload;
	stg26ColliCpEntry.create = stg26ColliCpCreate;
	stg26ColliCpEntry.reset  = NULL;

	stg26ColliCpEntry.flags = 0x400;
	stg26ColliCpEntry.unk18 = 0;
	stg26ColliCpEntry.unk20 = 0x7f;
	stg26ColliCpEntry.unk1C = 0x1601;
	stg26ColliCpEntry.unk1E = 2;
	stg26ColliCpEntry.unk21 = 0x0;

	stg26ColliCpEntry.fieldTypes = stg26ColliCcFieldTypes;
	stg26ColliCpEntry.fieldNames = stg26ColliCcFieldNames;

	if (stg26ColliCcFieldTypes != NULL) {
		stg26ColliCpEntry.flags |= 8;
	} else {
		stg26ColliCpEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const stg26ColliCcCtorEntry)(void) = stg26ColliCcRegister;
