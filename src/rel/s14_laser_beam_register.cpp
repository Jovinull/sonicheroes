#include "types.h"

// The record that registers S14 LaserBeam with the editor.
//
// The claim is .text 0xA3D00 to 0xA3DAC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cs" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void s14LaserBeamLoad(void);
extern "C" void s14LaserBeamUnload(void);
extern "C" void s14LaserBeamCreate(void);
extern "C" ObjectEntry s14LaserBeamEntry;
extern "C" char s14LaserBeamDisplayName[];
extern "C" char s14LaserBeamFieldTypes[];
extern "C" const char* s14LaserBeamFieldNames[];

extern "C" void s14LaserBeamRegister(void)
{
	s14LaserBeamEntry.flags = 0;
	s14LaserBeamEntry.unk18 = 0;

	s14LaserBeamEntry.name   = s14LaserBeamDisplayName;
	s14LaserBeamEntry.load   = s14LaserBeamLoad;
	s14LaserBeamEntry.unload = s14LaserBeamUnload;
	s14LaserBeamEntry.create = s14LaserBeamCreate;
	s14LaserBeamEntry.reset  = NULL;

	s14LaserBeamEntry.flags = 0x20000;
	s14LaserBeamEntry.unk18 = 0;
	s14LaserBeamEntry.unk20 = 0x32;
	s14LaserBeamEntry.unk1C = 0x1402;
	s14LaserBeamEntry.unk1E = 2;
	s14LaserBeamEntry.unk21 = 0x64;

	s14LaserBeamEntry.fieldTypes = s14LaserBeamFieldTypes;
	s14LaserBeamEntry.fieldNames = s14LaserBeamFieldNames;

	if (s14LaserBeamFieldTypes != NULL) {
		s14LaserBeamEntry.flags |= 8;
	} else {
		s14LaserBeamEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14LaserBeamCtorEntry)(void) = s14LaserBeamRegister;
