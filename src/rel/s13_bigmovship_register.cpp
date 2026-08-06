#include "types.h"

// The record that registers S13 BIGMOVSHIP with the editor.
//
// The claim is .text 0x92C78 to 0x92D20 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void s13BigmovshipLoad(void);
extern "C" void s13BigmovshipUnload(void);
extern "C" void s13BigmovshipCreate(void);
extern "C" ObjectEntry s13BigmovshipEntry;
extern "C" char s13BigmovshipDisplayName[];
extern "C" char s13BigmovshipFieldTypes[];
extern "C" const char* s13BigmovshipFieldNames[];

extern "C" void s13BigmovshipRegister(void)
{
	s13BigmovshipEntry.flags = 0;
	s13BigmovshipEntry.unk18 = 0;

	s13BigmovshipEntry.name   = s13BigmovshipDisplayName;
	s13BigmovshipEntry.load   = s13BigmovshipLoad;
	s13BigmovshipEntry.unload = s13BigmovshipUnload;
	s13BigmovshipEntry.create = s13BigmovshipCreate;
	s13BigmovshipEntry.reset  = NULL;

	s13BigmovshipEntry.flags = 0x20000;
	s13BigmovshipEntry.unk18 = 0;
	s13BigmovshipEntry.unk20 = 0x32;
	s13BigmovshipEntry.unk1C = 0x1314;
	s13BigmovshipEntry.unk1E = 2;
	s13BigmovshipEntry.unk21 = 0;

	s13BigmovshipEntry.fieldTypes = s13BigmovshipFieldTypes;
	s13BigmovshipEntry.fieldNames = s13BigmovshipFieldNames;

	if (s13BigmovshipFieldTypes != NULL) {
		s13BigmovshipEntry.flags |= 8;
	} else {
		s13BigmovshipEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13BigmovshipCtorEntry)(void) = s13BigmovshipRegister;
