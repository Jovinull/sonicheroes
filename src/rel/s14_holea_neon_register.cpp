#include "types.h"

// The records that register S14 HOLEA Neon and S14 HOLEB Neon and S14 GOAL Neon and S14 WALL L Neon and S14 WALL R Neon with the editor.
//
// The claim is .text 0xC4AC8 to 0xC4DB0 and the .ctors word that names it.
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
extern "C" void s14HoleaNeonLoad(void);
extern "C" void s14HoleaNeonUnload(void);
extern "C" void s14HoleaNeonCreate(void);
extern "C" ObjectEntry s14HoleaNeonEntry;
extern "C" char s14HoleaNeonDisplayName[];

extern "C" void s14HolebNeonCreate(void);
extern "C" ObjectEntry s14HolebNeonEntry;
extern "C" char s14HolebNeonDisplayName[];

extern "C" void s14GoalNeonCreate(void);
extern "C" ObjectEntry s14GoalNeonEntry;
extern "C" char s14GoalNeonDisplayName[];

extern "C" void s14WallLNeonCreate(void);
extern "C" ObjectEntry s14WallLNeonEntry;
extern "C" char s14WallLNeonDisplayName[];

extern "C" void s14WallRNeonCreate(void);
extern "C" ObjectEntry s14WallRNeonEntry;
extern "C" char s14WallRNeonDisplayName[];

extern "C" void s14HoleaNeonRegister(void)
{
	s14HoleaNeonEntry.flags = 0;
	s14HoleaNeonEntry.unk18 = 0;

	s14HoleaNeonEntry.name   = s14HoleaNeonDisplayName;
	s14HoleaNeonEntry.load   = s14HoleaNeonLoad;
	s14HoleaNeonEntry.unload = s14HoleaNeonUnload;
	s14HoleaNeonEntry.create = s14HoleaNeonCreate;
	s14HoleaNeonEntry.reset  = NULL;

	s14HoleaNeonEntry.flags = 0x1000;
	s14HoleaNeonEntry.unk18 = 0;
	s14HoleaNeonEntry.unk20 = 0xa;
	s14HoleaNeonEntry.unk1C = 0x1490;
	s14HoleaNeonEntry.unk1E = 2;
	s14HoleaNeonEntry.unk21 = 0x0;

	s14HoleaNeonEntry.fieldTypes = NULL;
	s14HoleaNeonEntry.fieldNames = NULL;

	if (s14HoleaNeonEntry.fieldTypes != NULL) {
		s14HoleaNeonEntry.flags |= 8;
	} else {
		s14HoleaNeonEntry.flags &= ~8;
	}

	s14HolebNeonEntry.flags = 0;
	s14HolebNeonEntry.unk18 = 0;

	s14HolebNeonEntry.name   = s14HolebNeonDisplayName;
	s14HolebNeonEntry.load   = s14HoleaNeonLoad;
	s14HolebNeonEntry.unload = s14HoleaNeonUnload;
	s14HolebNeonEntry.create = s14HolebNeonCreate;
	s14HolebNeonEntry.reset  = NULL;

	s14HolebNeonEntry.flags = 0x1000;
	s14HolebNeonEntry.unk18 = 0;
	s14HolebNeonEntry.unk20 = 0xa;
	s14HolebNeonEntry.unk1C = 0x1492;
	s14HolebNeonEntry.unk1E = 2;
	s14HolebNeonEntry.unk21 = 0x0;

	s14HolebNeonEntry.fieldTypes = NULL;
	s14HolebNeonEntry.fieldNames = NULL;

	if (s14HolebNeonEntry.fieldTypes != NULL) {
		s14HolebNeonEntry.flags |= 8;
	} else {
		s14HolebNeonEntry.flags &= ~8;
	}

	s14GoalNeonEntry.flags = 0;
	s14GoalNeonEntry.unk18 = 0;

	s14GoalNeonEntry.name   = s14GoalNeonDisplayName;
	s14GoalNeonEntry.load   = s14HoleaNeonLoad;
	s14GoalNeonEntry.unload = s14HoleaNeonUnload;
	s14GoalNeonEntry.create = s14GoalNeonCreate;
	s14GoalNeonEntry.reset  = NULL;

	s14GoalNeonEntry.flags = 0x1000;
	s14GoalNeonEntry.unk18 = 0;
	s14GoalNeonEntry.unk20 = 0x7f;
	s14GoalNeonEntry.unk1C = 0x148f;
	s14GoalNeonEntry.unk1E = 2;
	s14GoalNeonEntry.unk21 = 0x0;

	s14GoalNeonEntry.fieldTypes = NULL;
	s14GoalNeonEntry.fieldNames = NULL;

	if (s14GoalNeonEntry.fieldTypes != NULL) {
		s14GoalNeonEntry.flags |= 8;
	} else {
		s14GoalNeonEntry.flags &= ~8;
	}

	s14WallLNeonEntry.flags = 0;
	s14WallLNeonEntry.unk18 = 0;

	s14WallLNeonEntry.name   = s14WallLNeonDisplayName;
	s14WallLNeonEntry.load   = s14HoleaNeonLoad;
	s14WallLNeonEntry.unload = s14HoleaNeonUnload;
	s14WallLNeonEntry.create = s14WallLNeonCreate;
	s14WallLNeonEntry.reset  = NULL;

	s14WallLNeonEntry.flags = 0x1000;
	s14WallLNeonEntry.unk18 = 0;
	s14WallLNeonEntry.unk20 = 0x7f;
	s14WallLNeonEntry.unk1C = 0x148d;
	s14WallLNeonEntry.unk1E = 2;
	s14WallLNeonEntry.unk21 = 0x0;

	s14WallLNeonEntry.fieldTypes = NULL;
	s14WallLNeonEntry.fieldNames = NULL;

	if (s14WallLNeonEntry.fieldTypes != NULL) {
		s14WallLNeonEntry.flags |= 8;
	} else {
		s14WallLNeonEntry.flags &= ~8;
	}

	s14WallRNeonEntry.flags = 0;
	s14WallRNeonEntry.unk18 = 0;

	s14WallRNeonEntry.name   = s14WallRNeonDisplayName;
	s14WallRNeonEntry.load   = s14HoleaNeonLoad;
	s14WallRNeonEntry.unload = s14HoleaNeonUnload;
	s14WallRNeonEntry.create = s14WallRNeonCreate;
	s14WallRNeonEntry.reset  = NULL;

	s14WallRNeonEntry.flags = 0x1000;
	s14WallRNeonEntry.unk18 = 0;
	s14WallRNeonEntry.unk20 = 0x7f;
	s14WallRNeonEntry.unk1C = 0x148e;
	s14WallRNeonEntry.unk1E = 2;
	s14WallRNeonEntry.unk21 = 0x0;

	s14WallRNeonEntry.fieldTypes = NULL;
	s14WallRNeonEntry.fieldNames = NULL;

	if (s14WallRNeonEntry.fieldTypes != NULL) {
		s14WallRNeonEntry.flags |= 8;
	} else {
		s14WallRNeonEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14HoleaNeonCtorEntry)(void) = s14HoleaNeonRegister;
