#include "types.h"

// The record that registers S04 ENERGYPipeUp with the editor.
//
// The claim is .text 0x98D88 to 0x98E30 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cffff" is the field type string: one character per parameter the
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
extern "C" void s04ENERGYPipeUpLoad(void);
extern "C" void s04ENERGYPipeUpUnload(void);
extern "C" void s04ENERGYPipeUpCreate(void);
extern "C" ObjectEntry s04ENERGYPipeUpEntry;
extern "C" char s04ENERGYPipeUpDisplayName[];
extern "C" char s04ENERGYPipeUpFieldTypes[];
extern "C" const char* s04ENERGYPipeUpFieldNames[];

extern "C" void s04ENERGYPipeUpRegister(void)
{
	s04ENERGYPipeUpEntry.flags = 0;
	s04ENERGYPipeUpEntry.unk18 = 0;

	s04ENERGYPipeUpEntry.name   = s04ENERGYPipeUpDisplayName;
	s04ENERGYPipeUpEntry.load   = s04ENERGYPipeUpLoad;
	s04ENERGYPipeUpEntry.unload = s04ENERGYPipeUpUnload;
	s04ENERGYPipeUpEntry.create = s04ENERGYPipeUpCreate;
	s04ENERGYPipeUpEntry.reset  = NULL;

	s04ENERGYPipeUpEntry.flags = 0x20000;
	s04ENERGYPipeUpEntry.unk18 = 0;
	s04ENERGYPipeUpEntry.unk20 = 0x14;
	s04ENERGYPipeUpEntry.unk1C = 0x400;
	s04ENERGYPipeUpEntry.unk1E = 2;
	s04ENERGYPipeUpEntry.unk21 = 0;

	s04ENERGYPipeUpEntry.fieldTypes = s04ENERGYPipeUpFieldTypes;
	s04ENERGYPipeUpEntry.fieldNames = s04ENERGYPipeUpFieldNames;

	if (s04ENERGYPipeUpFieldTypes != NULL) {
		s04ENERGYPipeUpEntry.flags |= 8;
	} else {
		s04ENERGYPipeUpEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04ENERGYPipeUpCtorEntry)(void) = s04ENERGYPipeUpRegister;
