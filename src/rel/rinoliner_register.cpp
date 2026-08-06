#include "types.h"

// The record that registers RINOLINER OBJECT with the editor.
//
// The claim is .text 0xB23AC to 0xB2454 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccfifff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in three of the fourteen stage modules: 05D, 07D and 11D.

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
extern "C" void rinolinerObjectLoad(void);
extern "C" void rinolinerObjectUnload(void);
extern "C" void rinolinerObjectCreate(void);
extern "C" ObjectEntry rinolinerObjectEntry;
extern "C" char rinolinerObjectDisplayName[];
extern "C" char rinolinerObjectFieldTypes[];
extern "C" const char* rinolinerObjectFieldNames[];

extern "C" void rinolinerObjectRegister(void)
{
	rinolinerObjectEntry.flags = 0;
	rinolinerObjectEntry.unk18 = 0;

	rinolinerObjectEntry.name   = rinolinerObjectDisplayName;
	rinolinerObjectEntry.load   = rinolinerObjectLoad;
	rinolinerObjectEntry.unload = rinolinerObjectUnload;
	rinolinerObjectEntry.create = rinolinerObjectCreate;
	rinolinerObjectEntry.reset  = NULL;

	rinolinerObjectEntry.flags = 0x20000;
	rinolinerObjectEntry.unk18 = 0;
	rinolinerObjectEntry.unk20 = 0x1e;
	rinolinerObjectEntry.unk1C = 0x1590;
	rinolinerObjectEntry.unk1E = 4;
	rinolinerObjectEntry.unk21 = 0;

	rinolinerObjectEntry.fieldTypes = rinolinerObjectFieldTypes;
	rinolinerObjectEntry.fieldNames = rinolinerObjectFieldNames;

	if (rinolinerObjectFieldTypes != NULL) {
		rinolinerObjectEntry.flags |= 8;
	} else {
		rinolinerObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rinolinerObjectCtorEntry)(void) = rinolinerObjectRegister;
