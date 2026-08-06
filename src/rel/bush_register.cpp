#include "types.h"

// The record that registers BUSH with the editor.
//
// The claim is .text 0x717F0 to 0x718A0 and the .ctors word that names it.
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
extern "C" void bushLoad(void);
extern "C" void bushUnload(void);
extern "C" void bushCreate(void);
extern "C" void bushReset(void);
extern "C" ObjectEntry bushEntry;
extern "C" char bushDisplayName[];
extern "C" char bushFieldTypes[];
extern "C" const char* bushFieldNames[];

extern "C" void bushRegister(void)
{
	bushEntry.flags = 0;
	bushEntry.unk18 = 0;

	bushEntry.name   = bushDisplayName;
	bushEntry.load   = bushLoad;
	bushEntry.unload = bushUnload;
	bushEntry.create = bushCreate;
	bushEntry.reset  = bushReset;

	bushEntry.flags = 0x1000;
	bushEntry.unk18 = 0;
	bushEntry.unk20 = 0xa;
	bushEntry.unk1C = 0x986;
	bushEntry.unk1E = 2;
	bushEntry.unk21 = 0;

	bushEntry.fieldTypes = bushFieldTypes;
	bushEntry.fieldNames = bushFieldNames;

	if (bushFieldTypes != NULL) {
		bushEntry.flags |= 8;
	} else {
		bushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bushCtorEntry)(void) = bushRegister;
