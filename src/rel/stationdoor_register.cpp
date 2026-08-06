#include "types.h"

// The record that registers STATIONDOOR with the editor.
//
// The claim is .text 0x8E16C to 0x8E21C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
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
extern "C" void stationdoorLoad(void);
extern "C" void stationdoorUnload(void);
extern "C" void stationdoorCreate(void);
extern "C" void stationdoorReset(void);
extern "C" ObjectEntry stationdoorEntry;
extern "C" char stationdoorDisplayName[];
extern "C" char stationdoorFieldTypes[];
extern "C" const char* stationdoorFieldNames[];

extern "C" void stationdoorRegister(void)
{
	stationdoorEntry.flags = 0;
	stationdoorEntry.unk18 = 0;

	stationdoorEntry.name   = stationdoorDisplayName;
	stationdoorEntry.load   = stationdoorLoad;
	stationdoorEntry.unload = stationdoorUnload;
	stationdoorEntry.create = stationdoorCreate;
	stationdoorEntry.reset  = stationdoorReset;

	stationdoorEntry.flags = 0x20000;
	stationdoorEntry.unk18 = 0;
	stationdoorEntry.unk20 = 0xf;
	stationdoorEntry.unk1C = 0x706;
	stationdoorEntry.unk1E = 2;
	stationdoorEntry.unk21 = 0;

	stationdoorEntry.fieldTypes = stationdoorFieldTypes;
	stationdoorEntry.fieldNames = stationdoorFieldNames;

	if (stationdoorFieldTypes != NULL) {
		stationdoorEntry.flags |= 8;
	} else {
		stationdoorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const stationdoorCtorEntry)(void) = stationdoorRegister;
