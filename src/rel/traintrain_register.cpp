#include "types.h"

// The record that registers TRAINTRAIN with the editor.
//
// The claim is .text 0x9533C to 0x953DC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage07D carries this run.

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
extern "C" void traintrainLoad(void);
extern "C" void traintrainUnload(void);
extern "C" void traintrainCreate(void);
extern "C" void traintrainReset(void);
extern "C" ObjectEntry traintrainEntry;
extern "C" char traintrainDisplayName[];

extern "C" void traintrainRegister(void)
{
	traintrainEntry.flags = 0;
	traintrainEntry.unk18 = 0;

	traintrainEntry.name   = traintrainDisplayName;
	traintrainEntry.load   = traintrainLoad;
	traintrainEntry.unload = traintrainUnload;
	traintrainEntry.create = traintrainCreate;
	traintrainEntry.reset  = traintrainReset;

	traintrainEntry.flags = 0x480;
	traintrainEntry.unk18 = 0;
	traintrainEntry.unk20 = 0xf;
	traintrainEntry.unk1C = 0x71b;
	traintrainEntry.unk1E = 2;
	traintrainEntry.unk21 = 0;

	traintrainEntry.fieldTypes = NULL;
	traintrainEntry.fieldNames = NULL;

	if (traintrainEntry.fieldTypes != NULL) {
		traintrainEntry.flags |= 8;
	} else {
		traintrainEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const traintrainCtorEntry)(void) = traintrainRegister;
