#include "types.h"

// The record that registers S04D Energy Up with the editor.
//
// The claim is .text 0x96230 to 0x962D8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s04dEnergyUpLoad(void);
extern "C" void s04dEnergyUpUnload(void);
extern "C" void s04dEnergyUpCreate(void);
extern "C" ObjectEntry s04dEnergyUpEntry;
extern "C" char s04dEnergyUpDisplayName[];
extern "C" char s04dEnergyUpFieldTypes[];
extern "C" const char* s04dEnergyUpFieldNames[];

extern "C" void s04dEnergyUpRegister(void)
{
	s04dEnergyUpEntry.flags = 0;
	s04dEnergyUpEntry.unk18 = 0;

	s04dEnergyUpEntry.name   = s04dEnergyUpDisplayName;
	s04dEnergyUpEntry.load   = s04dEnergyUpLoad;
	s04dEnergyUpEntry.unload = s04dEnergyUpUnload;
	s04dEnergyUpEntry.create = s04dEnergyUpCreate;
	s04dEnergyUpEntry.reset  = NULL;

	s04dEnergyUpEntry.flags = 0x20000;
	s04dEnergyUpEntry.unk18 = 0;
	s04dEnergyUpEntry.unk20 = 0x32;
	s04dEnergyUpEntry.unk1C = 0x412;
	s04dEnergyUpEntry.unk1E = 2;
	s04dEnergyUpEntry.unk21 = 0;

	s04dEnergyUpEntry.fieldTypes = s04dEnergyUpFieldTypes;
	s04dEnergyUpEntry.fieldNames = s04dEnergyUpFieldNames;

	if (s04dEnergyUpFieldTypes != NULL) {
		s04dEnergyUpEntry.flags |= 8;
	} else {
		s04dEnergyUpEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dEnergyUpCtorEntry)(void) = s04dEnergyUpRegister;
