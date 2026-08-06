#include "types.h"

// The record that registers DUCT with the editor.
//
// The claim is .text 0x7ACFC to 0x7ADAC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void ductLoad(void);
extern "C" void ductUnload(void);
extern "C" void ductCreate(void);
extern "C" void ductReset(void);
extern "C" ObjectEntry ductEntry;
extern "C" char ductDisplayName[];
extern "C" char ductFieldTypes[];
extern "C" const char* ductFieldNames[];

extern "C" void ductRegister(void)
{
	ductEntry.flags = 0;
	ductEntry.unk18 = 0;

	ductEntry.name   = ductDisplayName;
	ductEntry.load   = ductLoad;
	ductEntry.unload = ductUnload;
	ductEntry.create = ductCreate;
	ductEntry.reset  = ductReset;

	ductEntry.flags = 0x20000;
	ductEntry.unk18 = 0;
	ductEntry.unk20 = 0xf;
	ductEntry.unk1C = 0x707;
	ductEntry.unk1E = 2;
	ductEntry.unk21 = 0;

	ductEntry.fieldTypes = ductFieldTypes;
	ductEntry.fieldNames = ductFieldNames;

	if (ductFieldTypes != NULL) {
		ductEntry.flags |= 8;
	} else {
		ductEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const ductCtorEntry)(void) = ductRegister;
