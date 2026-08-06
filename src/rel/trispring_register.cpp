#include "types.h"

// The record that registers TRISPRING with the editor.
//
// The claim is .text 0x9D78C to 0x9D83C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fccc" is the field type string: one character per parameter the
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
extern "C" void trispringLoad(void);
extern "C" void trispringUnload(void);
extern "C" void trispringCreate(void);
extern "C" void trispringReset(void);
extern "C" ObjectEntry trispringEntry;
extern "C" char trispringDisplayName[];
extern "C" char trispringFieldTypes[];
extern "C" const char* trispringFieldNames[];

extern "C" void trispringRegister(void)
{
	trispringEntry.flags = 0;
	trispringEntry.unk18 = 0;

	trispringEntry.name   = trispringDisplayName;
	trispringEntry.load   = trispringLoad;
	trispringEntry.unload = trispringUnload;
	trispringEntry.create = trispringCreate;
	trispringEntry.reset  = trispringReset;

	trispringEntry.flags = 0x20000;
	trispringEntry.unk18 = 0;
	trispringEntry.unk20 = 0xf;
	trispringEntry.unk1C = 0x503;
	trispringEntry.unk1E = 2;
	trispringEntry.unk21 = 0;

	trispringEntry.fieldTypes = trispringFieldTypes;
	trispringEntry.fieldNames = trispringFieldNames;

	if (trispringFieldTypes != NULL) {
		trispringEntry.flags |= 8;
	} else {
		trispringEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trispringCtorEntry)(void) = trispringRegister;
