#include "types.h"

// The record that registers S13 HOUDAI L with the editor.
//
// The claim is .text 0x81700 to 0x817A8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "SXXfCC" is the field type string: one character per parameter the
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
extern "C" void s13HoudaiLLoad(void);
extern "C" void s13HoudaiLUnload(void);
extern "C" void s13HoudaiLCreate(void);
extern "C" ObjectEntry s13HoudaiLEntry;
extern "C" char s13HoudaiLDisplayName[];
extern "C" char s13HoudaiLFieldTypes[];
extern "C" const char* s13HoudaiLFieldNames[];

extern "C" void s13HoudaiLRegister(void)
{
	s13HoudaiLEntry.flags = 0;
	s13HoudaiLEntry.unk18 = 0;

	s13HoudaiLEntry.name   = s13HoudaiLDisplayName;
	s13HoudaiLEntry.load   = s13HoudaiLLoad;
	s13HoudaiLEntry.unload = s13HoudaiLUnload;
	s13HoudaiLEntry.create = s13HoudaiLCreate;
	s13HoudaiLEntry.reset  = NULL;

	s13HoudaiLEntry.flags = 0x20000;
	s13HoudaiLEntry.unk18 = 0;
	s13HoudaiLEntry.unk20 = 0x14;
	s13HoudaiLEntry.unk1C = 0x1301;
	s13HoudaiLEntry.unk1E = 2;
	s13HoudaiLEntry.unk21 = 0;

	s13HoudaiLEntry.fieldTypes = s13HoudaiLFieldTypes;
	s13HoudaiLEntry.fieldNames = s13HoudaiLFieldNames;

	if (s13HoudaiLFieldTypes != NULL) {
		s13HoudaiLEntry.flags |= 8;
	} else {
		s13HoudaiLEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13HoudaiLCtorEntry)(void) = s13HoudaiLRegister;
