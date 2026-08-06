#include "types.h"

// The records that register S02D Kameashi and S02 Kame Wave with the editor.
//
// The claim is .text 0x9E794 to 0x9E8D0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FF" is S02D Kameashi's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "cFF" is S02 Kame Wave's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage01D carries this run.

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
extern "C" void s02dKameashiLoad(void);
extern "C" void s02dKameashiUnload(void);
extern "C" void s02dKameashiCreate(void);
extern "C" ObjectEntry s02dKameashiEntry;
extern "C" char s02dKameashiDisplayName[];
extern "C" char s02dKameashiFieldTypes[];
extern "C" const char* s02dKameashiFieldNames[];

extern "C" void s02KameWaveCreate(void);
extern "C" ObjectEntry s02KameWaveEntry;
extern "C" char s02KameWaveDisplayName[];
extern "C" char s02KameWaveFieldTypes[];
extern "C" const char* s02KameWaveFieldNames[];

extern "C" void s02dKameashiRegister(void)
{
	s02dKameashiEntry.flags = 0;
	s02dKameashiEntry.unk18 = 0;

	s02dKameashiEntry.name   = s02dKameashiDisplayName;
	s02dKameashiEntry.load   = s02dKameashiLoad;
	s02dKameashiEntry.unload = s02dKameashiUnload;
	s02dKameashiEntry.create = s02dKameashiCreate;
	s02dKameashiEntry.reset  = NULL;

	s02dKameashiEntry.flags = 0x1000;
	s02dKameashiEntry.unk18 = 0;
	s02dKameashiEntry.unk20 = 0x14;
	s02dKameashiEntry.unk1C = 0x281;
	s02dKameashiEntry.unk1E = 2;
	s02dKameashiEntry.unk21 = 0x0;

	s02dKameashiEntry.fieldTypes = s02dKameashiFieldTypes;
	s02dKameashiEntry.fieldNames = s02dKameashiFieldNames;

	if (s02dKameashiFieldTypes != NULL) {
		s02dKameashiEntry.flags |= 8;
	} else {
		s02dKameashiEntry.flags &= ~8;
	}

	s02KameWaveEntry.flags = 0;
	s02KameWaveEntry.unk18 = 0;

	s02KameWaveEntry.name   = s02KameWaveDisplayName;
	s02KameWaveEntry.load   = NULL;
	s02KameWaveEntry.unload = NULL;
	s02KameWaveEntry.create = s02KameWaveCreate;
	s02KameWaveEntry.reset  = NULL;

	s02KameWaveEntry.flags = 0x20000;
	s02KameWaveEntry.unk18 = 0;
	s02KameWaveEntry.unk20 = 0x7f;
	s02KameWaveEntry.unk1C = 0x282;
	s02KameWaveEntry.unk1E = 4098;
	s02KameWaveEntry.unk21 = 0x0;

	s02KameWaveEntry.fieldTypes = s02KameWaveFieldTypes;
	s02KameWaveEntry.fieldNames = s02KameWaveFieldNames;

	if (s02KameWaveFieldTypes != NULL) {
		s02KameWaveEntry.flags |= 8;
	} else {
		s02KameWaveEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02dKameashiCtorEntry)(void) = s02dKameashiRegister;
