#include "types.h"

// The record that registers S06CHIP OBJECT with the editor.
//
// The claim is .text 0xBB468 to 0xBB500 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage05D carries this run.

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
extern "C" void s06chipObjectLoad(void);
extern "C" void s06chipObjectUnload(void);
extern "C" void s06chipObjectCreate(void);
extern "C" ObjectEntry s06chipObjectEntry;
extern "C" char s06chipObjectDisplayName[];

extern "C" void s06chipObjectRegister(void)
{
	s06chipObjectEntry.flags = 0;
	s06chipObjectEntry.unk18 = 0;

	s06chipObjectEntry.name   = s06chipObjectDisplayName;
	s06chipObjectEntry.load   = s06chipObjectLoad;
	s06chipObjectEntry.unload = s06chipObjectUnload;
	s06chipObjectEntry.create = s06chipObjectCreate;
	s06chipObjectEntry.reset  = NULL;

	s06chipObjectEntry.flags = 0x1000;
	s06chipObjectEntry.unk18 = 0;
	s06chipObjectEntry.unk20 = 0x1e;
	s06chipObjectEntry.unk1C = 0x511;
	s06chipObjectEntry.unk1E = 2;
	s06chipObjectEntry.unk21 = 0;

	s06chipObjectEntry.fieldTypes = NULL;
	s06chipObjectEntry.fieldNames = NULL;

	if (s06chipObjectEntry.fieldTypes != NULL) {
		s06chipObjectEntry.flags |= 8;
	} else {
		s06chipObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s06chipObjectCtorEntry)(void) = s06chipObjectRegister;
