#include "types.h"

// The record that registers RAINCOLLISION with the editor.
//
// The claim is .text 0xB4098 to 0xB4148 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FCCCCCCCCCCCCCCCC" is the field type string: one character per parameter the
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
extern "C" void raincollisionLoad(void);
extern "C" void raincollisionUnload(void);
extern "C" void raincollisionCreate(void);
extern "C" void raincollisionReset(void);
extern "C" ObjectEntry raincollisionEntry;
extern "C" char raincollisionDisplayName[];
extern "C" char raincollisionFieldTypes[];
extern "C" const char* raincollisionFieldNames[];

extern "C" void raincollisionRegister(void)
{
	raincollisionEntry.flags = 0;
	raincollisionEntry.unk18 = 0;

	raincollisionEntry.name   = raincollisionDisplayName;
	raincollisionEntry.load   = raincollisionLoad;
	raincollisionEntry.unload = raincollisionUnload;
	raincollisionEntry.create = raincollisionCreate;
	raincollisionEntry.reset  = raincollisionReset;

	raincollisionEntry.flags = 0x20000;
	raincollisionEntry.unk18 = 0;
	raincollisionEntry.unk20 = 0xf;
	raincollisionEntry.unk1C = 0x913;
	raincollisionEntry.unk1E = 2;
	raincollisionEntry.unk21 = 0;

	raincollisionEntry.fieldTypes = raincollisionFieldTypes;
	raincollisionEntry.fieldNames = raincollisionFieldNames;

	if (raincollisionFieldTypes != NULL) {
		raincollisionEntry.flags |= 8;
	} else {
		raincollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const raincollisionCtorEntry)(void) = raincollisionRegister;
