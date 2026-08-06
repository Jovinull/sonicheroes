#include "types.h"

// The record that registers S04D Crane with the editor.
//
// The claim is .text 0xA97E4 to 0xA9890 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "x" is the field type string: one character per parameter the
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
extern "C" void s04dCraneLoad(void);
extern "C" void s04dCraneUnload(void);
extern "C" void s04dCraneCreate(void);
extern "C" ObjectEntry s04dCraneEntry;
extern "C" char s04dCraneDisplayName[];
extern "C" char s04dCraneFieldTypes[];
extern "C" const char* s04dCraneFieldNames[];

extern "C" void s04dCraneRegister(void)
{
	s04dCraneEntry.flags = 0;
	s04dCraneEntry.unk18 = 0;

	s04dCraneEntry.name   = s04dCraneDisplayName;
	s04dCraneEntry.load   = s04dCraneLoad;
	s04dCraneEntry.unload = s04dCraneUnload;
	s04dCraneEntry.create = s04dCraneCreate;
	s04dCraneEntry.reset  = NULL;

	s04dCraneEntry.flags = 0x21000;
	s04dCraneEntry.unk18 = 0;
	s04dCraneEntry.unk20 = 0xa;
	s04dCraneEntry.unk1C = 0x482;
	s04dCraneEntry.unk1E = 2;
	s04dCraneEntry.unk21 = 0;

	s04dCraneEntry.fieldTypes = s04dCraneFieldTypes;
	s04dCraneEntry.fieldNames = s04dCraneFieldNames;

	if (s04dCraneFieldTypes != NULL) {
		s04dCraneEntry.flags |= 8;
	} else {
		s04dCraneEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dCraneCtorEntry)(void) = s04dCraneRegister;
