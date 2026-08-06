#include "types.h"

// The record that registers RAINFRUITMI with the editor.
//
// The claim is .text 0x844D0 to 0x84570 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void rainfruitmiLoad(void);
extern "C" void rainfruitmiUnload(void);
extern "C" void rainfruitmiCreate(void);
extern "C" void rainfruitmiReset(void);
extern "C" ObjectEntry rainfruitmiEntry;
extern "C" char rainfruitmiDisplayName[];

extern "C" void rainfruitmiRegister(void)
{
	rainfruitmiEntry.flags = 0;
	rainfruitmiEntry.unk18 = 0;

	rainfruitmiEntry.name   = rainfruitmiDisplayName;
	rainfruitmiEntry.load   = rainfruitmiLoad;
	rainfruitmiEntry.unload = rainfruitmiUnload;
	rainfruitmiEntry.create = rainfruitmiCreate;
	rainfruitmiEntry.reset  = rainfruitmiReset;

	rainfruitmiEntry.flags = 0x480;
	rainfruitmiEntry.unk18 = 0;
	rainfruitmiEntry.unk20 = 0xa;
	rainfruitmiEntry.unk1C = 0x90f;
	rainfruitmiEntry.unk1E = 2;
	rainfruitmiEntry.unk21 = 0;

	rainfruitmiEntry.fieldTypes = NULL;
	rainfruitmiEntry.fieldNames = NULL;

	if (rainfruitmiEntry.fieldTypes != NULL) {
		rainfruitmiEntry.flags |= 8;
	} else {
		rainfruitmiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rainfruitmiCtorEntry)(void) = rainfruitmiRegister;
