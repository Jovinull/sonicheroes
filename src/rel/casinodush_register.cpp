#include "types.h"

// The record that registers CASINODUSH with the editor.
//
// The claim is .text 0xA2C78 to 0xA2D28 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void casinodushLoad(void);
extern "C" void casinodushUnload(void);
extern "C" void casinodushCreate(void);
extern "C" void casinodushReset(void);
extern "C" ObjectEntry casinodushEntry;
extern "C" char casinodushDisplayName[];
extern "C" char casinodushFieldTypes[];
extern "C" const char* casinodushFieldNames[];

extern "C" void casinodushRegister(void)
{
	casinodushEntry.flags = 0;
	casinodushEntry.unk18 = 0;

	casinodushEntry.name   = casinodushDisplayName;
	casinodushEntry.load   = casinodushLoad;
	casinodushEntry.unload = casinodushUnload;
	casinodushEntry.create = casinodushCreate;
	casinodushEntry.reset  = casinodushReset;

	casinodushEntry.flags = 0x20000;
	casinodushEntry.unk18 = 0;
	casinodushEntry.unk20 = 0xf;
	casinodushEntry.unk1C = 0x510;
	casinodushEntry.unk1E = 2;
	casinodushEntry.unk21 = 0;

	casinodushEntry.fieldTypes = casinodushFieldTypes;
	casinodushEntry.fieldNames = casinodushFieldNames;

	if (casinodushFieldTypes != NULL) {
		casinodushEntry.flags |= 8;
	} else {
		casinodushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const casinodushCtorEntry)(void) = casinodushRegister;
