#include "types.h"

// The record that registers S04D FloorLight with the editor.
//
// The claim is .text 0xA5BC4 to 0xA5C6C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fff" is the field type string: one character per parameter the
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
extern "C" void s04dFloorLightLoad(void);
extern "C" void s04dFloorLightUnload(void);
extern "C" void s04dFloorLightCreate(void);
extern "C" ObjectEntry s04dFloorLightEntry;
extern "C" char s04dFloorLightDisplayName[];
extern "C" char s04dFloorLightFieldTypes[];
extern "C" const char* s04dFloorLightFieldNames[];

extern "C" void s04dFloorLightRegister(void)
{
	s04dFloorLightEntry.flags = 0;
	s04dFloorLightEntry.unk18 = 0;

	s04dFloorLightEntry.name   = s04dFloorLightDisplayName;
	s04dFloorLightEntry.load   = s04dFloorLightLoad;
	s04dFloorLightEntry.unload = s04dFloorLightUnload;
	s04dFloorLightEntry.create = s04dFloorLightCreate;
	s04dFloorLightEntry.reset  = NULL;

	s04dFloorLightEntry.flags = 0x20000;
	s04dFloorLightEntry.unk18 = 0;
	s04dFloorLightEntry.unk20 = 0xa;
	s04dFloorLightEntry.unk1C = 0x485;
	s04dFloorLightEntry.unk1E = 4098;
	s04dFloorLightEntry.unk21 = 0;

	s04dFloorLightEntry.fieldTypes = s04dFloorLightFieldTypes;
	s04dFloorLightEntry.fieldNames = s04dFloorLightFieldNames;

	if (s04dFloorLightFieldTypes != NULL) {
		s04dFloorLightEntry.flags |= 8;
	} else {
		s04dFloorLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dFloorLightCtorEntry)(void) = s04dFloorLightRegister;
