#include "types.h"

// The record that registers RAILCHANGERAIL with the editor.
//
// The claim is .text 0x8428C to 0x8432C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void railchangerailLoad(void);
extern "C" void railchangerailUnload(void);
extern "C" void railchangerailCreate(void);
extern "C" void railchangerailReset(void);
extern "C" ObjectEntry railchangerailEntry;
extern "C" char railchangerailDisplayName[];

extern "C" void railchangerailRegister(void)
{
	railchangerailEntry.flags = 0;
	railchangerailEntry.unk18 = 0;

	railchangerailEntry.name   = railchangerailDisplayName;
	railchangerailEntry.load   = railchangerailLoad;
	railchangerailEntry.unload = railchangerailUnload;
	railchangerailEntry.create = railchangerailCreate;
	railchangerailEntry.reset  = railchangerailReset;

	railchangerailEntry.flags = 0x1000;
	railchangerailEntry.unk18 = 0;
	railchangerailEntry.unk20 = 0xf;
	railchangerailEntry.unk1C = 0x783;
	railchangerailEntry.unk1E = 2;
	railchangerailEntry.unk21 = 0;

	railchangerailEntry.fieldTypes = NULL;
	railchangerailEntry.fieldNames = NULL;

	if (railchangerailEntry.fieldTypes != NULL) {
		railchangerailEntry.flags |= 8;
	} else {
		railchangerailEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railchangerailCtorEntry)(void) = railchangerailRegister;
