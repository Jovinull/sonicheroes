#include "types.h"

// The record that registers S04D Elevator with the editor.
//
// The claim is .text 0x94D34 to 0x94DDC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "xff" is the field type string: one character per parameter the
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
extern "C" void s04dElevatorLoad(void);
extern "C" void s04dElevatorUnload(void);
extern "C" void s04dElevatorCreate(void);
extern "C" ObjectEntry s04dElevatorEntry;
extern "C" char s04dElevatorDisplayName[];
extern "C" char s04dElevatorFieldTypes[];
extern "C" const char* s04dElevatorFieldNames[];

extern "C" void s04dElevatorRegister(void)
{
	s04dElevatorEntry.flags = 0;
	s04dElevatorEntry.unk18 = 0;

	s04dElevatorEntry.name   = s04dElevatorDisplayName;
	s04dElevatorEntry.load   = s04dElevatorLoad;
	s04dElevatorEntry.unload = s04dElevatorUnload;
	s04dElevatorEntry.create = s04dElevatorCreate;
	s04dElevatorEntry.reset  = NULL;

	s04dElevatorEntry.flags = 0x20000;
	s04dElevatorEntry.unk18 = 0;
	s04dElevatorEntry.unk20 = 0x32;
	s04dElevatorEntry.unk1C = 0x402;
	s04dElevatorEntry.unk1E = 2;
	s04dElevatorEntry.unk21 = 0;

	s04dElevatorEntry.fieldTypes = s04dElevatorFieldTypes;
	s04dElevatorEntry.fieldNames = s04dElevatorFieldNames;

	if (s04dElevatorFieldTypes != NULL) {
		s04dElevatorEntry.flags |= 8;
	} else {
		s04dElevatorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dElevatorCtorEntry)(void) = s04dElevatorRegister;
