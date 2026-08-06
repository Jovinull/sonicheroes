#include "types.h"

// The records that register S14 TowerNeon A and S14 TowerNeon B with the editor.
//
// The claim is .text 0xD2558 to 0xD2684 and the .ctors word that names it.
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
extern "C" void s14TowerNeonALoad(void);
extern "C" void s14TowerNeonAUnload(void);
extern "C" void s14TowerNeonACreate(void);
extern "C" ObjectEntry s14TowerNeonAEntry;
extern "C" char s14TowerNeonADisplayName[];

extern "C" void s14TowerNeonBCreate(void);
extern "C" ObjectEntry s14TowerNeonBEntry;
extern "C" char s14TowerNeonBDisplayName[];

extern "C" void s14TowerNeonARegister(void)
{
	s14TowerNeonAEntry.flags = 0;
	s14TowerNeonAEntry.unk18 = 0;

	s14TowerNeonAEntry.name   = s14TowerNeonADisplayName;
	s14TowerNeonAEntry.load   = s14TowerNeonALoad;
	s14TowerNeonAEntry.unload = s14TowerNeonAUnload;
	s14TowerNeonAEntry.create = s14TowerNeonACreate;
	s14TowerNeonAEntry.reset  = NULL;

	s14TowerNeonAEntry.flags = 0x1000;
	s14TowerNeonAEntry.unk18 = 0;
	s14TowerNeonAEntry.unk20 = 0x1e;
	s14TowerNeonAEntry.unk1C = 0x1493;
	s14TowerNeonAEntry.unk1E = 2;
	s14TowerNeonAEntry.unk21 = 0x0;

	s14TowerNeonAEntry.fieldTypes = NULL;
	s14TowerNeonAEntry.fieldNames = NULL;

	if (s14TowerNeonAEntry.fieldTypes != NULL) {
		s14TowerNeonAEntry.flags |= 8;
	} else {
		s14TowerNeonAEntry.flags &= ~8;
	}

	s14TowerNeonBEntry.flags = 0;
	s14TowerNeonBEntry.unk18 = 0;

	s14TowerNeonBEntry.name   = s14TowerNeonBDisplayName;
	s14TowerNeonBEntry.load   = s14TowerNeonALoad;
	s14TowerNeonBEntry.unload = s14TowerNeonAUnload;
	s14TowerNeonBEntry.create = s14TowerNeonBCreate;
	s14TowerNeonBEntry.reset  = NULL;

	s14TowerNeonBEntry.flags = 0x1000;
	s14TowerNeonBEntry.unk18 = 0;
	s14TowerNeonBEntry.unk20 = 0x1e;
	s14TowerNeonBEntry.unk1C = 0x1494;
	s14TowerNeonBEntry.unk1E = 2;
	s14TowerNeonBEntry.unk21 = 0x0;

	s14TowerNeonBEntry.fieldTypes = NULL;
	s14TowerNeonBEntry.fieldNames = NULL;

	if (s14TowerNeonBEntry.fieldTypes != NULL) {
		s14TowerNeonBEntry.flags |= 8;
	} else {
		s14TowerNeonBEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14TowerNeonACtorEntry)(void) = s14TowerNeonARegister;
