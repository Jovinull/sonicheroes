#include "types.h"

// The record that registers IRONBALL OBJECT with the editor.
//
// The claim is .text 0x76C0 to 0x7768 and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in all thirteen stage modules that share the engine
// core. stage40D is a different revision of the source and is left out.
//
// "iff" is the field type string: one character per parameter the editor
// shows, and the array beside it holds their labels.

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

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void ironballLoad(void);
extern "C" void ironballUnload(void);
extern "C" void ironballCreate(void);
extern "C" ObjectEntry ironballEntry;
extern "C" char ironballDisplayName[];
extern "C" char ironballFieldTypes[];
extern "C" const char* ironballFieldNames[];

extern "C" void ironballRegister(void)
{
	ironballEntry.flags = 0;
	ironballEntry.unk18 = 0;

	ironballEntry.name   = ironballDisplayName;
	ironballEntry.load   = ironballLoad;
	ironballEntry.unload = ironballUnload;
	ironballEntry.create = ironballCreate;
	ironballEntry.unk10  = NULL;

	ironballEntry.flags = 0x20000;
	ironballEntry.unk18 = 0;
	ironballEntry.unk20 = 0x1E;
	ironballEntry.unk1C = 0x15;
	ironballEntry.unk1E = 2;
	ironballEntry.unk21 = 0;

	ironballEntry.fieldTypes = ironballFieldTypes;
	ironballEntry.fieldNames = ironballFieldNames;

	if (ironballFieldTypes != NULL) {
		ironballEntry.flags |= 8;
	} else {
		ironballEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const ironballCtorEntry)(void) = ironballRegister;
