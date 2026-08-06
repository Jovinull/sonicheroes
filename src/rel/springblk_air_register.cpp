#include "types.h"

// The record that registers SPRINGBLK_AIR with the editor.
//
// The claim is .text 0x9BACC to 0x9BB7C and the .ctors word that names it.
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
extern "C" void springblkAirLoad(void);
extern "C" void springblkAirUnload(void);
extern "C" void springblkAirCreate(void);
extern "C" void springblkAirReset(void);
extern "C" ObjectEntry springblkAirEntry;
extern "C" char springblkAirDisplayName[];
extern "C" char springblkAirFieldTypes[];
extern "C" const char* springblkAirFieldNames[];

extern "C" void springblkAirRegister(void)
{
	springblkAirEntry.flags = 0;
	springblkAirEntry.unk18 = 0;

	springblkAirEntry.name   = springblkAirDisplayName;
	springblkAirEntry.load   = springblkAirLoad;
	springblkAirEntry.unload = springblkAirUnload;
	springblkAirEntry.create = springblkAirCreate;
	springblkAirEntry.reset  = springblkAirReset;

	springblkAirEntry.flags = 0x20000;
	springblkAirEntry.unk18 = 0;
	springblkAirEntry.unk20 = 0xf;
	springblkAirEntry.unk1C = 0x505;
	springblkAirEntry.unk1E = 2;
	springblkAirEntry.unk21 = 0;

	springblkAirEntry.fieldTypes = springblkAirFieldTypes;
	springblkAirEntry.fieldNames = springblkAirFieldNames;

	if (springblkAirFieldTypes != NULL) {
		springblkAirEntry.flags |= 8;
	} else {
		springblkAirEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const springblkAirCtorEntry)(void) = springblkAirRegister;
