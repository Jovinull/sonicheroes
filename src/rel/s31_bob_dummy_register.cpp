#include "types.h"

// The record that registers S31BOB OBJECT(DUMMY) with the editor.
//
// The claim is .text 0xC4ED0 to 0xC4F68 and the .ctors word at 0x158 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It shows no editor fields, so the type and label slots take NULL and
// the trailing test folds bit 3 out rather than in.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// The run is the same in twelve of the fourteen stage modules. stage13D does not
// register this object at all, and stage40D registers it from a different build.

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
extern "C" void s31bobObjectdummyLoad(void);
extern "C" void s31bobObjectdummyUnload(void);
extern "C" void s31bobObjectdummyCreate(void);
extern "C" ObjectEntry s31bobObjectdummyEntry;
extern "C" char s31bobObjectdummyDisplayName[];

extern "C" void s31bobObjectdummyRegister(void)
{
	s31bobObjectdummyEntry.flags = 0;
	s31bobObjectdummyEntry.unk18 = 0;

	s31bobObjectdummyEntry.name   = s31bobObjectdummyDisplayName;
	s31bobObjectdummyEntry.load   = s31bobObjectdummyLoad;
	s31bobObjectdummyEntry.unload = s31bobObjectdummyUnload;
	s31bobObjectdummyEntry.create = s31bobObjectdummyCreate;
	s31bobObjectdummyEntry.unk10  = NULL;

	s31bobObjectdummyEntry.flags = 0x2000000;
	s31bobObjectdummyEntry.unk18 = 0;
	s31bobObjectdummyEntry.unk20 = 30;
	s31bobObjectdummyEntry.unk1C = 13057;
	s31bobObjectdummyEntry.unk1E = 2;
	s31bobObjectdummyEntry.unk21 = 0;

	s31bobObjectdummyEntry.fieldTypes = NULL;
	s31bobObjectdummyEntry.fieldNames = NULL;

	if (s31bobObjectdummyEntry.fieldTypes != NULL) {
		s31bobObjectdummyEntry.flags |= 8;
	} else {
		s31bobObjectdummyEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s31bobObjectdummyCtorEntry)(void)
    = s31bobObjectdummyRegister;
