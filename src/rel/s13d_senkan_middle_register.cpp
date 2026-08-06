#include "types.h"

// The records that register S13D SENKAN MIDDLE and S13D SENKAN MIDDLE with the editor.
//
// The claim is .text 0x90C6C to 0x90D98 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
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
extern "C" void s13dSenkanMiddle1Load(void);
extern "C" void s13dSenkanMiddle1Unload(void);
extern "C" void s13dSenkanMiddle1Create(void);
extern "C" ObjectEntry s13dSenkanMiddle1Entry;
extern "C" char s13dSenkanMiddle1DisplayName[];

extern "C" void s13dSenkanMiddle2Create(void);
extern "C" ObjectEntry s13dSenkanMiddle2Entry;

extern "C" void s13dSenkanMiddle1Register(void)
{
	s13dSenkanMiddle1Entry.flags = 0;
	s13dSenkanMiddle1Entry.unk18 = 0;

	s13dSenkanMiddle1Entry.name   = s13dSenkanMiddle1DisplayName;
	s13dSenkanMiddle1Entry.load   = s13dSenkanMiddle1Load;
	s13dSenkanMiddle1Entry.unload = s13dSenkanMiddle1Unload;
	s13dSenkanMiddle1Entry.create = s13dSenkanMiddle1Create;
	s13dSenkanMiddle1Entry.reset  = NULL;

	s13dSenkanMiddle1Entry.flags = 0x1000;
	s13dSenkanMiddle1Entry.unk18 = 0;
	s13dSenkanMiddle1Entry.unk20 = 0x64;
	s13dSenkanMiddle1Entry.unk1C = 0x1390;
	s13dSenkanMiddle1Entry.unk1E = 2;
	s13dSenkanMiddle1Entry.unk21 = 0x0;

	s13dSenkanMiddle1Entry.fieldTypes = NULL;
	s13dSenkanMiddle1Entry.fieldNames = NULL;

	if (s13dSenkanMiddle1Entry.fieldTypes != NULL) {
		s13dSenkanMiddle1Entry.flags |= 8;
	} else {
		s13dSenkanMiddle1Entry.flags &= ~8;
	}

	s13dSenkanMiddle2Entry.flags = 0;
	s13dSenkanMiddle2Entry.unk18 = 0;

	s13dSenkanMiddle2Entry.name   = s13dSenkanMiddle1DisplayName;
	s13dSenkanMiddle2Entry.load   = s13dSenkanMiddle1Load;
	s13dSenkanMiddle2Entry.unload = s13dSenkanMiddle1Unload;
	s13dSenkanMiddle2Entry.create = s13dSenkanMiddle2Create;
	s13dSenkanMiddle2Entry.reset  = NULL;

	s13dSenkanMiddle2Entry.flags = 0x1000;
	s13dSenkanMiddle2Entry.unk18 = 0;
	s13dSenkanMiddle2Entry.unk20 = 0x64;
	s13dSenkanMiddle2Entry.unk1C = 0x138f;
	s13dSenkanMiddle2Entry.unk1E = 2;
	s13dSenkanMiddle2Entry.unk21 = 0x0;

	s13dSenkanMiddle2Entry.fieldTypes = NULL;
	s13dSenkanMiddle2Entry.fieldNames = NULL;

	if (s13dSenkanMiddle2Entry.fieldTypes != NULL) {
		s13dSenkanMiddle2Entry.flags |= 8;
	} else {
		s13dSenkanMiddle2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dSenkanMiddle1CtorEntry)(void)
    = s13dSenkanMiddle1Register;
