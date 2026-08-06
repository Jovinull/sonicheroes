#include "types.h"

// The record that registers S13 HOUDAI YOKO with the editor.
//
// The claim is .text 0x7E658 to 0x7E700 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "SfC" is the field type string: one character per parameter the
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
extern "C" void s13HoudaiYokoLoad(void);
extern "C" void s13HoudaiYokoUnload(void);
extern "C" void s13HoudaiYokoCreate(void);
extern "C" ObjectEntry s13HoudaiYokoEntry;
extern "C" char s13HoudaiYokoDisplayName[];
extern "C" char s13HoudaiYokoFieldTypes[];
extern "C" const char* s13HoudaiYokoFieldNames[];

extern "C" void s13HoudaiYokoRegister(void)
{
	s13HoudaiYokoEntry.flags = 0;
	s13HoudaiYokoEntry.unk18 = 0;

	s13HoudaiYokoEntry.name   = s13HoudaiYokoDisplayName;
	s13HoudaiYokoEntry.load   = s13HoudaiYokoLoad;
	s13HoudaiYokoEntry.unload = s13HoudaiYokoUnload;
	s13HoudaiYokoEntry.create = s13HoudaiYokoCreate;
	s13HoudaiYokoEntry.reset  = NULL;

	s13HoudaiYokoEntry.flags = 0x20000;
	s13HoudaiYokoEntry.unk18 = 0;
	s13HoudaiYokoEntry.unk20 = 0x14;
	s13HoudaiYokoEntry.unk1C = 0x1302;
	s13HoudaiYokoEntry.unk1E = 2;
	s13HoudaiYokoEntry.unk21 = 0;

	s13HoudaiYokoEntry.fieldTypes = s13HoudaiYokoFieldTypes;
	s13HoudaiYokoEntry.fieldNames = s13HoudaiYokoFieldNames;

	if (s13HoudaiYokoFieldTypes != NULL) {
		s13HoudaiYokoEntry.flags |= 8;
	} else {
		s13HoudaiYokoEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13HoudaiYokoCtorEntry)(void) = s13HoudaiYokoRegister;
