#include "types.h"

// The record that registers FAN OBJECT with the editor.
//
// The claim is .text 0x2583C to 0x258E4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ffffcCfc" is the field type string: one character per parameter the
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
extern "C" void fanObjectLoad(void);
extern "C" void fanObjectUnload(void);
extern "C" void fanObjectCreate(void);
extern "C" ObjectEntry fanObjectEntry;
extern "C" char fanObjectDisplayName[];
extern "C" char fanObjectFieldTypes[];
extern "C" const char* fanObjectFieldNames[];

extern "C" void fanObjectRegister(void)
{
	fanObjectEntry.flags = 0;
	fanObjectEntry.unk18 = 0;

	fanObjectEntry.name   = fanObjectDisplayName;
	fanObjectEntry.load   = fanObjectLoad;
	fanObjectEntry.unload = fanObjectUnload;
	fanObjectEntry.create = fanObjectCreate;
	fanObjectEntry.reset  = NULL;

	fanObjectEntry.flags = 0x20000;
	fanObjectEntry.unk18 = 0;
	fanObjectEntry.unk20 = 0x1e;
	fanObjectEntry.unk1C = 0x2e;
	fanObjectEntry.unk1E = 2;
	fanObjectEntry.unk21 = 0;

	fanObjectEntry.fieldTypes = fanObjectFieldTypes;
	fanObjectEntry.fieldNames = fanObjectFieldNames;

	if (fanObjectFieldTypes != NULL) {
		fanObjectEntry.flags |= 8;
	} else {
		fanObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const fanObjectCtorEntry)(void) = fanObjectRegister;
