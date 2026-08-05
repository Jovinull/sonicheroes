#include "types.h"

// The record that registers S01 Gokurakucho with the editor.
//
// The claim is .text 0x7EF80 to 0x7F02C and the .ctors word that names it. Only
// the record is taken: the three hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// Only stage01D carries this run, like the other stage-01 and stage-02 object
// records around it.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void gokurakuchoLoad(void);
extern "C" void gokurakuchoUnload(void);
extern "C" void gokurakuchoCreate(void);
extern "C" ObjectEntry gokurakuchoEntry;
extern "C" char gokurakuchoDisplayName[];
extern "C" char gokurakuchoFieldTypes[];
extern "C" const char* gokurakuchoFieldNames[];

extern "C" void gokurakuchoRegister(void)
{
	gokurakuchoEntry.flags = 0;
	gokurakuchoEntry.unk18 = 0;

	gokurakuchoEntry.name   = gokurakuchoDisplayName;
	gokurakuchoEntry.load   = gokurakuchoLoad;
	gokurakuchoEntry.unload = gokurakuchoUnload;
	gokurakuchoEntry.create = gokurakuchoCreate;
	gokurakuchoEntry.unk10  = NULL;

	gokurakuchoEntry.flags = 0x21000;
	gokurakuchoEntry.unk18 = 0;
	gokurakuchoEntry.unk20 = 127;
	gokurakuchoEntry.unk1C = 388;
	gokurakuchoEntry.unk1E = 2;
	gokurakuchoEntry.unk21 = 0;

	gokurakuchoEntry.fieldTypes = gokurakuchoFieldTypes;
	gokurakuchoEntry.fieldNames = gokurakuchoFieldNames;

	if (gokurakuchoFieldTypes != NULL) {
		gokurakuchoEntry.flags |= 8;
	} else {
		gokurakuchoEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const gokurakuchoCtorEntry)(void) = gokurakuchoRegister;
