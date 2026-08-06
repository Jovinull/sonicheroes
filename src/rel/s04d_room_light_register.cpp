#include "types.h"

// The record that registers S04D RoomLight with the editor.
//
// The claim is .text 0xA784C to 0xA78F8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "x" is the field type string: one character per parameter the
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
extern "C" void s04dRoomLightLoad(void);
extern "C" void s04dRoomLightUnload(void);
extern "C" void s04dRoomLightCreate(void);
extern "C" ObjectEntry s04dRoomLightEntry;
extern "C" char s04dRoomLightDisplayName[];
extern "C" char s04dRoomLightFieldTypes[];
extern "C" const char* s04dRoomLightFieldNames[];

extern "C" void s04dRoomLightRegister(void)
{
	s04dRoomLightEntry.flags = 0;
	s04dRoomLightEntry.unk18 = 0;

	s04dRoomLightEntry.name   = s04dRoomLightDisplayName;
	s04dRoomLightEntry.load   = s04dRoomLightLoad;
	s04dRoomLightEntry.unload = s04dRoomLightUnload;
	s04dRoomLightEntry.create = s04dRoomLightCreate;
	s04dRoomLightEntry.reset  = NULL;

	s04dRoomLightEntry.flags = 0x21000;
	s04dRoomLightEntry.unk18 = 0;
	s04dRoomLightEntry.unk20 = 0xa;
	s04dRoomLightEntry.unk1C = 0x484;
	s04dRoomLightEntry.unk1E = 2;
	s04dRoomLightEntry.unk21 = 0;

	s04dRoomLightEntry.fieldTypes = s04dRoomLightFieldTypes;
	s04dRoomLightEntry.fieldNames = s04dRoomLightFieldNames;

	if (s04dRoomLightFieldTypes != NULL) {
		s04dRoomLightEntry.flags |= 8;
	} else {
		s04dRoomLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dRoomLightCtorEntry)(void) = s04dRoomLightRegister;
