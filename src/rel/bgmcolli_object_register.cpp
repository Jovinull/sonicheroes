#include "types.h"

// The record that registers BGMCOLLI OBJECT with the editor.
//
// The claim is .text 0xDCD80 to 0xDCE30 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "SIFFF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage11D carries this run.

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
extern "C" void bgmcolliObjectLoad(void);
extern "C" void bgmcolliObjectUnload(void);
extern "C" void bgmcolliObjectCreate(void);
extern "C" void bgmcolliObjectReset(void);
extern "C" ObjectEntry bgmcolliObjectEntry;
extern "C" char bgmcolliObjectDisplayName[];
extern "C" char bgmcolliObjectFieldTypes[];
extern "C" const char* bgmcolliObjectFieldNames[];

extern "C" void bgmcolliObjectRegister(void)
{
	bgmcolliObjectEntry.flags = 0;
	bgmcolliObjectEntry.unk18 = 0;

	bgmcolliObjectEntry.name   = bgmcolliObjectDisplayName;
	bgmcolliObjectEntry.load   = bgmcolliObjectLoad;
	bgmcolliObjectEntry.unload = bgmcolliObjectUnload;
	bgmcolliObjectEntry.create = bgmcolliObjectCreate;
	bgmcolliObjectEntry.reset  = bgmcolliObjectReset;

	bgmcolliObjectEntry.flags = 0x20000;
	bgmcolliObjectEntry.unk18 = 0;
	bgmcolliObjectEntry.unk20 = 0x1e;
	bgmcolliObjectEntry.unk1C = 0x110c;
	bgmcolliObjectEntry.unk1E = 2;
	bgmcolliObjectEntry.unk21 = 0;

	bgmcolliObjectEntry.fieldTypes = bgmcolliObjectFieldTypes;
	bgmcolliObjectEntry.fieldNames = bgmcolliObjectFieldNames;

	if (bgmcolliObjectFieldTypes != NULL) {
		bgmcolliObjectEntry.flags |= 8;
	} else {
		bgmcolliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bgmcolliObjectCtorEntry)(void) = bgmcolliObjectRegister;
