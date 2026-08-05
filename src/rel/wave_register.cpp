#include "types.h"

// The record that registers S01 Wave with the editor.
//
// The claim is .text 0x89438 to 0x894E4 and the .ctors word at 0xE8 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The .ctors slot follows from the order being monotonic in .text address:
// rel/o_s01_iwamizu.cpp holds 0xD8 and rel/o_s01_shachicolli.cpp holds 0xF0,
// and this record's run sits between them.
//
// Only stage01D carries this run, like the other stage-01 object records around
// it.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void waveLoad(void);
extern "C" void waveUnload(void);
extern "C" void waveCreate(void);
extern "C" ObjectEntry waveEntry;
extern "C" char waveDisplayName[];
extern "C" char waveFieldTypes[];
extern "C" const char* waveFieldNames[];

extern "C" void waveRegister(void)
{
	waveEntry.flags = 0;
	waveEntry.unk18 = 0;

	waveEntry.name   = waveDisplayName;
	waveEntry.load   = waveLoad;
	waveEntry.unload = waveUnload;
	waveEntry.create = waveCreate;
	waveEntry.unk10  = NULL;

	waveEntry.flags = 0x21000;
	waveEntry.unk18 = 0;
	waveEntry.unk20 = 127;
	waveEntry.unk1C = 391;
	waveEntry.unk1E = 2;
	waveEntry.unk21 = 0;

	waveEntry.fieldTypes = waveFieldTypes;
	waveEntry.fieldNames = waveFieldNames;

	if (waveFieldTypes != NULL) {
		waveEntry.flags |= 8;
	} else {
		waveEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const waveCtorEntry)(void) = waveRegister;
