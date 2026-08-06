#include "types.h"

// The record that registers S13D BIGFAN with the editor.
//
// The claim is .text 0x8729C to 0x87344 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
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
extern "C" void s13dBigfanLoad(void);
extern "C" void s13dBigfanUnload(void);
extern "C" void s13dBigfanCreate(void);
extern "C" ObjectEntry s13dBigfanEntry;
extern "C" char s13dBigfanDisplayName[];
extern "C" char s13dBigfanFieldTypes[];
extern "C" const char* s13dBigfanFieldNames[];

extern "C" void s13dBigfanRegister(void)
{
	s13dBigfanEntry.flags = 0;
	s13dBigfanEntry.unk18 = 0;

	s13dBigfanEntry.name   = s13dBigfanDisplayName;
	s13dBigfanEntry.load   = s13dBigfanLoad;
	s13dBigfanEntry.unload = s13dBigfanUnload;
	s13dBigfanEntry.create = s13dBigfanCreate;
	s13dBigfanEntry.reset  = NULL;

	s13dBigfanEntry.flags = 0x20000;
	s13dBigfanEntry.unk18 = 0;
	s13dBigfanEntry.unk20 = 0x14;
	s13dBigfanEntry.unk1C = 0x1380;
	s13dBigfanEntry.unk1E = 2;
	s13dBigfanEntry.unk21 = 0;

	s13dBigfanEntry.fieldTypes = s13dBigfanFieldTypes;
	s13dBigfanEntry.fieldNames = s13dBigfanFieldNames;

	if (s13dBigfanFieldTypes != NULL) {
		s13dBigfanEntry.flags |= 8;
	} else {
		s13dBigfanEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dBigfanCtorEntry)(void) = s13dBigfanRegister;
