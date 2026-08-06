#include "types.h"

// The record that registers RAINFLOOR with the editor.
//
// The claim is .text 0x80FB0 to 0x81060 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void rainfloorLoad(void);
extern "C" void rainfloorUnload(void);
extern "C" void rainfloorCreate(void);
extern "C" void rainfloorReset(void);
extern "C" ObjectEntry rainfloorEntry;
extern "C" char rainfloorDisplayName[];
extern "C" char rainfloorFieldTypes[];
extern "C" const char* rainfloorFieldNames[];

extern "C" void rainfloorRegister(void)
{
	rainfloorEntry.flags = 0;
	rainfloorEntry.unk18 = 0;

	rainfloorEntry.name   = rainfloorDisplayName;
	rainfloorEntry.load   = rainfloorLoad;
	rainfloorEntry.unload = rainfloorUnload;
	rainfloorEntry.create = rainfloorCreate;
	rainfloorEntry.reset  = rainfloorReset;

	rainfloorEntry.flags = 0x20000;
	rainfloorEntry.unk18 = 0;
	rainfloorEntry.unk20 = 0xa;
	rainfloorEntry.unk1C = 0x907;
	rainfloorEntry.unk1E = 2;
	rainfloorEntry.unk21 = 0;

	rainfloorEntry.fieldTypes = rainfloorFieldTypes;
	rainfloorEntry.fieldNames = rainfloorFieldNames;

	if (rainfloorFieldTypes != NULL) {
		rainfloorEntry.flags |= 8;
	} else {
		rainfloorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rainfloorCtorEntry)(void) = rainfloorRegister;
