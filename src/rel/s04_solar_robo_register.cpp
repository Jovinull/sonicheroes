#include "types.h"

// The record that registers S04 Solar Robo with the editor.
//
// The claim is .text 0xA8AA0 to 0xA8B4C and the .ctors word that names it.
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
extern "C" void s04SolarRoboLoad(void);
extern "C" void s04SolarRoboUnload(void);
extern "C" void s04SolarRoboCreate(void);
extern "C" ObjectEntry s04SolarRoboEntry;
extern "C" char s04SolarRoboDisplayName[];
extern "C" char s04SolarRoboFieldTypes[];
extern "C" const char* s04SolarRoboFieldNames[];

extern "C" void s04SolarRoboRegister(void)
{
	s04SolarRoboEntry.flags = 0;
	s04SolarRoboEntry.unk18 = 0;

	s04SolarRoboEntry.name   = s04SolarRoboDisplayName;
	s04SolarRoboEntry.load   = s04SolarRoboLoad;
	s04SolarRoboEntry.unload = s04SolarRoboUnload;
	s04SolarRoboEntry.create = s04SolarRoboCreate;
	s04SolarRoboEntry.reset  = NULL;

	s04SolarRoboEntry.flags = 0x21000;
	s04SolarRoboEntry.unk18 = 0;
	s04SolarRoboEntry.unk20 = 0xa;
	s04SolarRoboEntry.unk1C = 0x483;
	s04SolarRoboEntry.unk1E = 2;
	s04SolarRoboEntry.unk21 = 0;

	s04SolarRoboEntry.fieldTypes = s04SolarRoboFieldTypes;
	s04SolarRoboEntry.fieldNames = s04SolarRoboFieldNames;

	if (s04SolarRoboFieldTypes != NULL) {
		s04SolarRoboEntry.flags |= 8;
	} else {
		s04SolarRoboEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04SolarRoboCtorEntry)(void) = s04SolarRoboRegister;
