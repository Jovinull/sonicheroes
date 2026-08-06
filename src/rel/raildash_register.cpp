#include "types.h"

// The record that registers RAILDASH with the editor.
//
// The claim is .text 0x86074 to 0x86124 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void raildashLoad(void);
extern "C" void raildashUnload(void);
extern "C" void raildashCreate(void);
extern "C" void raildashReset(void);
extern "C" ObjectEntry raildashEntry;
extern "C" char raildashDisplayName[];
extern "C" char raildashFieldTypes[];
extern "C" const char* raildashFieldNames[];

extern "C" void raildashRegister(void)
{
	raildashEntry.flags = 0;
	raildashEntry.unk18 = 0;

	raildashEntry.name   = raildashDisplayName;
	raildashEntry.load   = raildashLoad;
	raildashEntry.unload = raildashUnload;
	raildashEntry.create = raildashCreate;
	raildashEntry.reset  = raildashReset;

	raildashEntry.flags = 0x20000;
	raildashEntry.unk18 = 0;
	raildashEntry.unk20 = 0xf;
	raildashEntry.unk1C = 0x703;
	raildashEntry.unk1E = 2;
	raildashEntry.unk21 = 0;

	raildashEntry.fieldTypes = raildashFieldTypes;
	raildashEntry.fieldNames = raildashFieldNames;

	if (raildashFieldTypes != NULL) {
		raildashEntry.flags |= 8;
	} else {
		raildashEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const raildashCtorEntry)(void) = raildashRegister;
