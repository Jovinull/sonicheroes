#include "types.h"

// The record that registers S04D PIPE ELEV with the editor.
//
// The claim is .text 0xC4970 to 0xC4A08 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s04dPipeElevLoad(void);
extern "C" void s04dPipeElevUnload(void);
extern "C" void s04dPipeElevCreate(void);
extern "C" ObjectEntry s04dPipeElevEntry;
extern "C" char s04dPipeElevDisplayName[];

extern "C" void s04dPipeElevRegister(void)
{
	s04dPipeElevEntry.flags = 0;
	s04dPipeElevEntry.unk18 = 0;

	s04dPipeElevEntry.name   = s04dPipeElevDisplayName;
	s04dPipeElevEntry.load   = s04dPipeElevLoad;
	s04dPipeElevEntry.unload = s04dPipeElevUnload;
	s04dPipeElevEntry.create = s04dPipeElevCreate;
	s04dPipeElevEntry.reset  = NULL;

	s04dPipeElevEntry.flags = 0x20000;
	s04dPipeElevEntry.unk18 = 0;
	s04dPipeElevEntry.unk20 = 0xa;
	s04dPipeElevEntry.unk1C = 0x416;
	s04dPipeElevEntry.unk1E = 2;
	s04dPipeElevEntry.unk21 = 0;

	s04dPipeElevEntry.fieldTypes = NULL;
	s04dPipeElevEntry.fieldNames = NULL;

	if (s04dPipeElevEntry.fieldTypes != NULL) {
		s04dPipeElevEntry.flags |= 8;
	} else {
		s04dPipeElevEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dPipeElevCtorEntry)(void) = s04dPipeElevRegister;
