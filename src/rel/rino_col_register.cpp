#include "types.h"

// The record that registers RINO COL OBJECT with the editor.
//
// The claim is .text 0xB4BE4 to 0xB4C8C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccffff" is the field type string: one character per parameter the
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
extern "C" void rinoColObjectLoad(void);
extern "C" void rinoColObjectUnload(void);
extern "C" void rinoColObjectCreate(void);
extern "C" ObjectEntry rinoColObjectEntry;
extern "C" char rinoColObjectDisplayName[];
extern "C" char rinoColObjectFieldTypes[];
extern "C" const char* rinoColObjectFieldNames[];

extern "C" void rinoColObjectRegister(void)
{
	rinoColObjectEntry.flags = 0;
	rinoColObjectEntry.unk18 = 0;

	rinoColObjectEntry.name   = rinoColObjectDisplayName;
	rinoColObjectEntry.load   = rinoColObjectLoad;
	rinoColObjectEntry.unload = rinoColObjectUnload;
	rinoColObjectEntry.create = rinoColObjectCreate;
	rinoColObjectEntry.reset  = NULL;

	rinoColObjectEntry.flags = 0x20000;
	rinoColObjectEntry.unk18 = 0;
	rinoColObjectEntry.unk20 = 0x1e;
	rinoColObjectEntry.unk1C = 0x60;
	rinoColObjectEntry.unk1E = 4;
	rinoColObjectEntry.unk21 = 0;

	rinoColObjectEntry.fieldTypes = rinoColObjectFieldTypes;
	rinoColObjectEntry.fieldNames = rinoColObjectFieldNames;

	if (rinoColObjectFieldTypes != NULL) {
		rinoColObjectEntry.flags |= 8;
	} else {
		rinoColObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rinoColObjectCtorEntry)(void) = rinoColObjectRegister;
