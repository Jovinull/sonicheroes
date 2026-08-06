#include "types.h"

// The records that register S13D RAIL CAP FORE and S13D RAIL CAP BACK with the editor.
//
// The claim is .text 0x94A0C to 0x94B38 and the .ctors word that names it.
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
extern "C" void s13dRailCapForeLoad(void);
extern "C" void s13dRailCapForeUnload(void);
extern "C" void s13dRailCapForeCreate(void);
extern "C" ObjectEntry s13dRailCapForeEntry;
extern "C" char s13dRailCapForeDisplayName[];

extern "C" void s13dRailCapBackCreate(void);
extern "C" ObjectEntry s13dRailCapBackEntry;
extern "C" char s13dRailCapBackDisplayName[];

extern "C" void s13dRailCapForeRegister(void)
{
	s13dRailCapForeEntry.flags = 0;
	s13dRailCapForeEntry.unk18 = 0;

	s13dRailCapForeEntry.name   = s13dRailCapForeDisplayName;
	s13dRailCapForeEntry.load   = s13dRailCapForeLoad;
	s13dRailCapForeEntry.unload = s13dRailCapForeUnload;
	s13dRailCapForeEntry.create = s13dRailCapForeCreate;
	s13dRailCapForeEntry.reset  = NULL;

	s13dRailCapForeEntry.flags = 0x1000;
	s13dRailCapForeEntry.unk18 = 0;
	s13dRailCapForeEntry.unk20 = 0xd;
	s13dRailCapForeEntry.unk1C = 0x1391;
	s13dRailCapForeEntry.unk1E = 2;
	s13dRailCapForeEntry.unk21 = 0x0;

	s13dRailCapForeEntry.fieldTypes = NULL;
	s13dRailCapForeEntry.fieldNames = NULL;

	if (s13dRailCapForeEntry.fieldTypes != NULL) {
		s13dRailCapForeEntry.flags |= 8;
	} else {
		s13dRailCapForeEntry.flags &= ~8;
	}

	s13dRailCapBackEntry.flags = 0;
	s13dRailCapBackEntry.unk18 = 0;

	s13dRailCapBackEntry.name   = s13dRailCapBackDisplayName;
	s13dRailCapBackEntry.load   = s13dRailCapForeLoad;
	s13dRailCapBackEntry.unload = s13dRailCapForeUnload;
	s13dRailCapBackEntry.create = s13dRailCapBackCreate;
	s13dRailCapBackEntry.reset  = NULL;

	s13dRailCapBackEntry.flags = 0x1000;
	s13dRailCapBackEntry.unk18 = 0;
	s13dRailCapBackEntry.unk20 = 0xd;
	s13dRailCapBackEntry.unk1C = 0x1392;
	s13dRailCapBackEntry.unk1E = 2;
	s13dRailCapBackEntry.unk21 = 0x0;

	s13dRailCapBackEntry.fieldTypes = NULL;
	s13dRailCapBackEntry.fieldNames = NULL;

	if (s13dRailCapBackEntry.fieldTypes != NULL) {
		s13dRailCapBackEntry.flags |= 8;
	} else {
		s13dRailCapBackEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dRailCapForeCtorEntry)(void) = s13dRailCapForeRegister;
