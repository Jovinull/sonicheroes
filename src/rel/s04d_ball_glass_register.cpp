#include "types.h"

// The record that registers S04D BallGlass with the editor.
//
// The claim is .text 0x88818 to 0x888B4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s04dBallGlassLoad(void);
extern "C" void s04dBallGlassUnload(void);
extern "C" void s04dBallGlassCreate(void);
extern "C" ObjectEntry s04dBallGlassEntry;
extern "C" char s04dBallGlassDisplayName[];

extern "C" void s04dBallGlassRegister(void)
{
	s04dBallGlassEntry.flags = 0;
	s04dBallGlassEntry.unk18 = 0;

	s04dBallGlassEntry.name   = s04dBallGlassDisplayName;
	s04dBallGlassEntry.load   = s04dBallGlassLoad;
	s04dBallGlassEntry.unload = s04dBallGlassUnload;
	s04dBallGlassEntry.create = s04dBallGlassCreate;
	s04dBallGlassEntry.reset  = NULL;

	s04dBallGlassEntry.flags = 0x21000;
	s04dBallGlassEntry.unk18 = 0;
	s04dBallGlassEntry.unk20 = 0xa;
	s04dBallGlassEntry.unk1C = 0x480;
	s04dBallGlassEntry.unk1E = 2;
	s04dBallGlassEntry.unk21 = 0;

	s04dBallGlassEntry.fieldTypes = NULL;
	s04dBallGlassEntry.fieldNames = NULL;

	if (s04dBallGlassEntry.fieldTypes != NULL) {
		s04dBallGlassEntry.flags |= 8;
	} else {
		s04dBallGlassEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dBallGlassCtorEntry)(void) = s04dBallGlassRegister;
