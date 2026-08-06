#include "types.h"

// The records that register S14 ROADSIDE A and S14 ROADSIDE B with the editor.
//
// The claim is .text 0xC9A54 to 0xC9B70 and the .ctors word that names it.
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
extern "C" void s14RoadsideALoad(void);
extern "C" void s14RoadsideAUnload(void);
extern "C" void s14RoadsideACreate(void);
extern "C" ObjectEntry s14RoadsideAEntry;
extern "C" char s14RoadsideADisplayName[];

extern "C" void s14RoadsideBCreate(void);
extern "C" ObjectEntry s14RoadsideBEntry;
extern "C" char s14RoadsideBDisplayName[];

extern "C" void s14RoadsideARegister(void)
{
	s14RoadsideAEntry.flags = 0;
	s14RoadsideAEntry.unk18 = 0;

	s14RoadsideAEntry.name   = s14RoadsideADisplayName;
	s14RoadsideAEntry.load   = s14RoadsideALoad;
	s14RoadsideAEntry.unload = s14RoadsideAUnload;
	s14RoadsideAEntry.create = s14RoadsideACreate;
	s14RoadsideAEntry.reset  = NULL;

	s14RoadsideAEntry.flags = 0x1000;
	s14RoadsideAEntry.unk18 = 0;
	s14RoadsideAEntry.unk20 = 0xa;
	s14RoadsideAEntry.unk1C = 0x1486;
	s14RoadsideAEntry.unk1E = 2;
	s14RoadsideAEntry.unk21 = 0x0;

	s14RoadsideAEntry.fieldTypes = NULL;
	s14RoadsideAEntry.fieldNames = NULL;

	if (s14RoadsideAEntry.fieldTypes != NULL) {
		s14RoadsideAEntry.flags |= 8;
	} else {
		s14RoadsideAEntry.flags &= ~8;
	}

	s14RoadsideBEntry.flags = 0;
	s14RoadsideBEntry.unk18 = 0;

	s14RoadsideBEntry.name   = s14RoadsideBDisplayName;
	s14RoadsideBEntry.load   = NULL;
	s14RoadsideBEntry.unload = NULL;
	s14RoadsideBEntry.create = s14RoadsideBCreate;
	s14RoadsideBEntry.reset  = NULL;

	s14RoadsideBEntry.flags = 0x1000;
	s14RoadsideBEntry.unk18 = 0;
	s14RoadsideBEntry.unk20 = 0xa;
	s14RoadsideBEntry.unk1C = 0x1491;
	s14RoadsideBEntry.unk1E = 2;
	s14RoadsideBEntry.unk21 = 0x0;

	s14RoadsideBEntry.fieldTypes = NULL;
	s14RoadsideBEntry.fieldNames = NULL;

	if (s14RoadsideBEntry.fieldTypes != NULL) {
		s14RoadsideBEntry.flags |= 8;
	} else {
		s14RoadsideBEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14RoadsideACtorEntry)(void) = s14RoadsideARegister;
