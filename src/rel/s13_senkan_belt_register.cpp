#include "types.h"

// The record that registers S13 SENKAN BELT with the editor.
//
// The claim is .text 0x85E00 to 0x85EA8 and the .ctors word that names it.
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
extern "C" void s13SenkanBeltLoad(void);
extern "C" void s13SenkanBeltUnload(void);
extern "C" void s13SenkanBeltCreate(void);
extern "C" ObjectEntry s13SenkanBeltEntry;
extern "C" char s13SenkanBeltDisplayName[];
extern "C" char s13SenkanBeltFieldTypes[];
extern "C" const char* s13SenkanBeltFieldNames[];

extern "C" void s13SenkanBeltRegister(void)
{
	s13SenkanBeltEntry.flags = 0;
	s13SenkanBeltEntry.unk18 = 0;

	s13SenkanBeltEntry.name   = s13SenkanBeltDisplayName;
	s13SenkanBeltEntry.load   = s13SenkanBeltLoad;
	s13SenkanBeltEntry.unload = s13SenkanBeltUnload;
	s13SenkanBeltEntry.create = s13SenkanBeltCreate;
	s13SenkanBeltEntry.reset  = NULL;

	s13SenkanBeltEntry.flags = 0x20000;
	s13SenkanBeltEntry.unk18 = 0;
	s13SenkanBeltEntry.unk20 = 0x14;
	s13SenkanBeltEntry.unk1C = 0x1308;
	s13SenkanBeltEntry.unk1E = 2;
	s13SenkanBeltEntry.unk21 = 0;

	s13SenkanBeltEntry.fieldTypes = s13SenkanBeltFieldTypes;
	s13SenkanBeltEntry.fieldNames = s13SenkanBeltFieldNames;

	if (s13SenkanBeltFieldTypes != NULL) {
		s13SenkanBeltEntry.flags |= 8;
	} else {
		s13SenkanBeltEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13SenkanBeltCtorEntry)(void) = s13SenkanBeltRegister;
