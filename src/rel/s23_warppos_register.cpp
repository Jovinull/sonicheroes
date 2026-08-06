#include "types.h"

// The record that registers S23 WARPPOS with the editor.
//
// The claim is .text 0xF54AC to 0xF5558 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
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
extern "C" void s23WarpposLoad(void);
extern "C" void s23WarpposUnload(void);
extern "C" void s23WarpposCreate(void);
extern "C" void s23WarpposReset(void);
extern "C" ObjectEntry s23WarpposEntry;
extern "C" char s23WarpposDisplayName[];
extern "C" char s23WarpposFieldTypes[];
extern "C" const char* s23WarpposFieldNames[];

extern "C" void s23WarpposRegister(void)
{
	s23WarpposEntry.flags = 0;
	s23WarpposEntry.unk18 = 0;

	s23WarpposEntry.name   = s23WarpposDisplayName;
	s23WarpposEntry.load   = s23WarpposLoad;
	s23WarpposEntry.unload = s23WarpposUnload;
	s23WarpposEntry.create = s23WarpposCreate;
	s23WarpposEntry.reset  = s23WarpposReset;

	s23WarpposEntry.flags = 0x0;
	s23WarpposEntry.unk18 = 0;
	s23WarpposEntry.unk20 = 0x32;
	s23WarpposEntry.unk1C = 0x2300;
	s23WarpposEntry.unk1E = 2;
	s23WarpposEntry.unk21 = 0;

	s23WarpposEntry.fieldTypes = s23WarpposFieldTypes;
	s23WarpposEntry.fieldNames = s23WarpposFieldNames;

	if (s23WarpposFieldTypes != NULL) {
		s23WarpposEntry.flags |= 8;
	} else {
		s23WarpposEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s23WarpposCtorEntry)(void) = s23WarpposRegister;
