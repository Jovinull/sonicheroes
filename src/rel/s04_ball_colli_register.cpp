#include "types.h"

// The record that registers S04 BallColli with the editor.
//
// The claim is .text 0xB6CD4 to 0xB6D70 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
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
extern "C" void s04BallColliCreate(void);
extern "C" ObjectEntry s04BallColliEntry;
extern "C" char s04BallColliDisplayName[];
extern "C" char s04BallColliFieldTypes[];
extern "C" const char* s04BallColliFieldNames[];

extern "C" void s04BallColliRegister(void)
{
	s04BallColliEntry.flags = 0;
	s04BallColliEntry.unk18 = 0;

	s04BallColliEntry.name   = s04BallColliDisplayName;
	s04BallColliEntry.load   = NULL;
	s04BallColliEntry.unload = NULL;
	s04BallColliEntry.create = s04BallColliCreate;
	s04BallColliEntry.reset  = NULL;

	s04BallColliEntry.flags = 0x21000;
	s04BallColliEntry.unk18 = 0;
	s04BallColliEntry.unk20 = 0x32;
	s04BallColliEntry.unk1C = 0x414;
	s04BallColliEntry.unk1E = 2;
	s04BallColliEntry.unk21 = 0;

	s04BallColliEntry.fieldTypes = s04BallColliFieldTypes;
	s04BallColliEntry.fieldNames = s04BallColliFieldNames;

	if (s04BallColliFieldTypes != NULL) {
		s04BallColliEntry.flags |= 8;
	} else {
		s04BallColliEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04BallColliCtorEntry)(void) = s04BallColliRegister;
