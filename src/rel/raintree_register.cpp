#include "types.h"

// The record that registers RAINTREE with the editor.
//
// The claim is .text 0x89E28 to 0x89ED4 and the .ctors word that names it.
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
extern "C" void raintreeLoad(void);
extern "C" void raintreeUnload(void);
extern "C" void raintreeCreate(void);
extern "C" void raintreeReset(void);
extern "C" ObjectEntry raintreeEntry;
extern "C" char raintreeDisplayName[];
extern "C" char raintreeFieldTypes[];
extern "C" const char* raintreeFieldNames[];

extern "C" void raintreeRegister(void)
{
	raintreeEntry.flags = 0;
	raintreeEntry.unk18 = 0;

	raintreeEntry.name   = raintreeDisplayName;
	raintreeEntry.load   = raintreeLoad;
	raintreeEntry.unload = raintreeUnload;
	raintreeEntry.create = raintreeCreate;
	raintreeEntry.reset  = raintreeReset;

	raintreeEntry.flags = 0x0;
	raintreeEntry.unk18 = 0;
	raintreeEntry.unk20 = 0xa;
	raintreeEntry.unk1C = 0x905;
	raintreeEntry.unk1E = 2;
	raintreeEntry.unk21 = 0;

	raintreeEntry.fieldTypes = raintreeFieldTypes;
	raintreeEntry.fieldNames = raintreeFieldNames;

	if (raintreeFieldTypes != NULL) {
		raintreeEntry.flags |= 8;
	} else {
		raintreeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const raintreeCtorEntry)(void) = raintreeRegister;
