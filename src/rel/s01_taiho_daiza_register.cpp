#include "types.h"

// The record that registers S01 TAIHO DAIZA with the editor.
//
// The claim is .text 0xC3E74 to 0xC3F1C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s01TaihoDaizaLoad(void);
extern "C" void s01TaihoDaizaUnload(void);
extern "C" void s01TaihoDaizaCreate(void);
extern "C" ObjectEntry s01TaihoDaizaEntry;
extern "C" char s01TaihoDaizaDisplayName[];
extern "C" char s01TaihoDaizaFieldTypes[];
extern "C" const char* s01TaihoDaizaFieldNames[];

extern "C" void s01TaihoDaizaRegister(void)
{
	s01TaihoDaizaEntry.flags = 0;
	s01TaihoDaizaEntry.unk18 = 0;

	s01TaihoDaizaEntry.name   = s01TaihoDaizaDisplayName;
	s01TaihoDaizaEntry.load   = s01TaihoDaizaLoad;
	s01TaihoDaizaEntry.unload = s01TaihoDaizaUnload;
	s01TaihoDaizaEntry.create = s01TaihoDaizaCreate;
	s01TaihoDaizaEntry.reset  = NULL;

	s01TaihoDaizaEntry.flags = 0x20000;
	s01TaihoDaizaEntry.unk18 = 0;
	s01TaihoDaizaEntry.unk20 = 0x14;
	s01TaihoDaizaEntry.unk1C = 0x188;
	s01TaihoDaizaEntry.unk1E = 2;
	s01TaihoDaizaEntry.unk21 = 0;

	s01TaihoDaizaEntry.fieldTypes = s01TaihoDaizaFieldTypes;
	s01TaihoDaizaEntry.fieldNames = s01TaihoDaizaFieldNames;

	if (s01TaihoDaizaFieldTypes != NULL) {
		s01TaihoDaizaEntry.flags |= 8;
	} else {
		s01TaihoDaizaEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s01TaihoDaizaCtorEntry)(void) = s01TaihoDaizaRegister;
