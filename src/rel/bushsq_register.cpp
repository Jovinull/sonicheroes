#include "types.h"

// The record that registers BUSHSQ with the editor.
//
// The claim is .text 0x93FF4 to 0x940A4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void bushsqLoad(void);
extern "C" void bushsqUnload(void);
extern "C" void bushsqCreate(void);
extern "C" void bushsqReset(void);
extern "C" ObjectEntry bushsqEntry;
extern "C" char bushsqDisplayName[];
extern "C" char bushsqFieldTypes[];
extern "C" const char* bushsqFieldNames[];

extern "C" void bushsqRegister(void)
{
	bushsqEntry.flags = 0;
	bushsqEntry.unk18 = 0;

	bushsqEntry.name   = bushsqDisplayName;
	bushsqEntry.load   = bushsqLoad;
	bushsqEntry.unload = bushsqUnload;
	bushsqEntry.create = bushsqCreate;
	bushsqEntry.reset  = bushsqReset;

	bushsqEntry.flags = 0x1000;
	bushsqEntry.unk18 = 0;
	bushsqEntry.unk20 = 0xa;
	bushsqEntry.unk1C = 0x993;
	bushsqEntry.unk1E = 2;
	bushsqEntry.unk21 = 0;

	bushsqEntry.fieldTypes = bushsqFieldTypes;
	bushsqEntry.fieldNames = bushsqFieldNames;

	if (bushsqFieldTypes != NULL) {
		bushsqEntry.flags |= 8;
	} else {
		bushsqEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bushsqCtorEntry)(void) = bushsqRegister;
