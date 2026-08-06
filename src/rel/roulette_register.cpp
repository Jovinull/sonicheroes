#include "types.h"

// The record that registers ROULETTE with the editor.
//
// The claim is .text 0x92F2C to 0x92FDC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fi" is the field type string: one character per parameter the
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
extern "C" void rouletteLoad(void);
extern "C" void rouletteUnload(void);
extern "C" void rouletteCreate(void);
extern "C" void rouletteReset(void);
extern "C" ObjectEntry rouletteEntry;
extern "C" char rouletteDisplayName[];
extern "C" char rouletteFieldTypes[];
extern "C" const char* rouletteFieldNames[];

extern "C" void rouletteRegister(void)
{
	rouletteEntry.flags = 0;
	rouletteEntry.unk18 = 0;

	rouletteEntry.name   = rouletteDisplayName;
	rouletteEntry.load   = rouletteLoad;
	rouletteEntry.unload = rouletteUnload;
	rouletteEntry.create = rouletteCreate;
	rouletteEntry.reset  = rouletteReset;

	rouletteEntry.flags = 0x1000;
	rouletteEntry.unk18 = 0;
	rouletteEntry.unk20 = 0xf;
	rouletteEntry.unk1C = 0x586;
	rouletteEntry.unk1E = 2;
	rouletteEntry.unk21 = 0;

	rouletteEntry.fieldTypes = rouletteFieldTypes;
	rouletteEntry.fieldNames = rouletteFieldNames;

	if (rouletteFieldTypes != NULL) {
		rouletteEntry.flags |= 8;
	} else {
		rouletteEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rouletteCtorEntry)(void) = rouletteRegister;
