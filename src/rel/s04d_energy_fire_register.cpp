#include "types.h"

// The record that registers S04D EnergyFire with the editor.
//
// The claim is .text 0x951C4 to 0x9526C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
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
extern "C" void s04dEnergyFireLoad(void);
extern "C" void s04dEnergyFireUnload(void);
extern "C" void s04dEnergyFireCreate(void);
extern "C" ObjectEntry s04dEnergyFireEntry;
extern "C" char s04dEnergyFireDisplayName[];
extern "C" char s04dEnergyFireFieldTypes[];
extern "C" const char* s04dEnergyFireFieldNames[];

extern "C" void s04dEnergyFireRegister(void)
{
	s04dEnergyFireEntry.flags = 0;
	s04dEnergyFireEntry.unk18 = 0;

	s04dEnergyFireEntry.name   = s04dEnergyFireDisplayName;
	s04dEnergyFireEntry.load   = s04dEnergyFireLoad;
	s04dEnergyFireEntry.unload = s04dEnergyFireUnload;
	s04dEnergyFireEntry.create = s04dEnergyFireCreate;
	s04dEnergyFireEntry.reset  = NULL;

	s04dEnergyFireEntry.flags = 0x20000;
	s04dEnergyFireEntry.unk18 = 0;
	s04dEnergyFireEntry.unk20 = 0xa;
	s04dEnergyFireEntry.unk1C = 0x405;
	s04dEnergyFireEntry.unk1E = 2;
	s04dEnergyFireEntry.unk21 = 0;

	s04dEnergyFireEntry.fieldTypes = s04dEnergyFireFieldTypes;
	s04dEnergyFireEntry.fieldNames = s04dEnergyFireFieldNames;

	if (s04dEnergyFireFieldTypes != NULL) {
		s04dEnergyFireEntry.flags |= 8;
	} else {
		s04dEnergyFireEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dEnergyFireCtorEntry)(void) = s04dEnergyFireRegister;
