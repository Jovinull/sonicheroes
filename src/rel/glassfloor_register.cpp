#include "types.h"

// The record that registers GLASSFLOOR with the editor.
//
// The claim is .text 0x91444 to 0x914F4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void glassfloorLoad(void);
extern "C" void glassfloorUnload(void);
extern "C" void glassfloorCreate(void);
extern "C" void glassfloorReset(void);
extern "C" ObjectEntry glassfloorEntry;
extern "C" char glassfloorDisplayName[];
extern "C" char glassfloorFieldTypes[];
extern "C" const char* glassfloorFieldNames[];

extern "C" void glassfloorRegister(void)
{
	glassfloorEntry.flags = 0;
	glassfloorEntry.unk18 = 0;

	glassfloorEntry.name   = glassfloorDisplayName;
	glassfloorEntry.load   = glassfloorLoad;
	glassfloorEntry.unload = glassfloorUnload;
	glassfloorEntry.create = glassfloorCreate;
	glassfloorEntry.reset  = glassfloorReset;

	glassfloorEntry.flags = 0x20000;
	glassfloorEntry.unk18 = 0;
	glassfloorEntry.unk20 = 0xf;
	glassfloorEntry.unk1C = 0x509;
	glassfloorEntry.unk1E = 2;
	glassfloorEntry.unk21 = 0;

	glassfloorEntry.fieldTypes = glassfloorFieldTypes;
	glassfloorEntry.fieldNames = glassfloorFieldNames;

	if (glassfloorFieldTypes != NULL) {
		glassfloorEntry.flags |= 8;
	} else {
		glassfloorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const glassfloorCtorEntry)(void) = glassfloorRegister;
