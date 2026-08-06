#include "types.h"

// The records that register S13D RAIL ARROW 1 and S13D RAIL ARROW 3 with the editor.
//
// The claim is .text 0x93CBC to 0x93DE8 and the .ctors word that names it.
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
extern "C" void s13dRailArrow1Load(void);
extern "C" void s13dRailArrow1Unload(void);
extern "C" void s13dRailArrow1Create(void);
extern "C" ObjectEntry s13dRailArrow1Entry;
extern "C" char s13dRailArrow1DisplayName[];

extern "C" void s13dRailArrow3Create(void);
extern "C" ObjectEntry s13dRailArrow3Entry;
extern "C" char s13dRailArrow3DisplayName[];

extern "C" void s13dRailArrow1Register(void)
{
	s13dRailArrow1Entry.flags = 0;
	s13dRailArrow1Entry.unk18 = 0;

	s13dRailArrow1Entry.name   = s13dRailArrow1DisplayName;
	s13dRailArrow1Entry.load   = s13dRailArrow1Load;
	s13dRailArrow1Entry.unload = s13dRailArrow1Unload;
	s13dRailArrow1Entry.create = s13dRailArrow1Create;
	s13dRailArrow1Entry.reset  = NULL;

	s13dRailArrow1Entry.flags = 0x1000;
	s13dRailArrow1Entry.unk18 = 0;
	s13dRailArrow1Entry.unk20 = 0xd;
	s13dRailArrow1Entry.unk1C = 0x1393;
	s13dRailArrow1Entry.unk1E = 2;
	s13dRailArrow1Entry.unk21 = 0x0;

	s13dRailArrow1Entry.fieldTypes = NULL;
	s13dRailArrow1Entry.fieldNames = NULL;

	if (s13dRailArrow1Entry.fieldTypes != NULL) {
		s13dRailArrow1Entry.flags |= 8;
	} else {
		s13dRailArrow1Entry.flags &= ~8;
	}

	s13dRailArrow3Entry.flags = 0;
	s13dRailArrow3Entry.unk18 = 0;

	s13dRailArrow3Entry.name   = s13dRailArrow3DisplayName;
	s13dRailArrow3Entry.load   = s13dRailArrow1Load;
	s13dRailArrow3Entry.unload = s13dRailArrow1Unload;
	s13dRailArrow3Entry.create = s13dRailArrow3Create;
	s13dRailArrow3Entry.reset  = NULL;

	s13dRailArrow3Entry.flags = 0x1000;
	s13dRailArrow3Entry.unk18 = 0;
	s13dRailArrow3Entry.unk20 = 0xd;
	s13dRailArrow3Entry.unk1C = 0x1394;
	s13dRailArrow3Entry.unk1E = 2;
	s13dRailArrow3Entry.unk21 = 0x0;

	s13dRailArrow3Entry.fieldTypes = NULL;
	s13dRailArrow3Entry.fieldNames = NULL;

	if (s13dRailArrow3Entry.fieldTypes != NULL) {
		s13dRailArrow3Entry.flags |= 8;
	} else {
		s13dRailArrow3Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dRailArrow1CtorEntry)(void) = s13dRailArrow1Register;
