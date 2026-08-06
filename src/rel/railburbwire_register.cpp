#include "types.h"

// The record that registers RAILBURBWIRE with the editor.
//
// The claim is .text 0x7F880 to 0x7F920 and the .ctors word that names it.
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
extern "C" void railburbwireLoad(void);
extern "C" void railburbwireUnload(void);
extern "C" void railburbwireCreate(void);
extern "C" void railburbwireReset(void);
extern "C" ObjectEntry railburbwireEntry;
extern "C" char railburbwireDisplayName[];

extern "C" void railburbwireRegister(void)
{
	railburbwireEntry.flags = 0;
	railburbwireEntry.unk18 = 0;

	railburbwireEntry.name   = railburbwireDisplayName;
	railburbwireEntry.load   = railburbwireLoad;
	railburbwireEntry.unload = railburbwireUnload;
	railburbwireEntry.create = railburbwireCreate;
	railburbwireEntry.reset  = railburbwireReset;

	railburbwireEntry.flags = 0x1000;
	railburbwireEntry.unk18 = 0;
	railburbwireEntry.unk20 = 0xf;
	railburbwireEntry.unk1C = 0x782;
	railburbwireEntry.unk1E = 2;
	railburbwireEntry.unk21 = 0;

	railburbwireEntry.fieldTypes = NULL;
	railburbwireEntry.fieldNames = NULL;

	if (railburbwireEntry.fieldTypes != NULL) {
		railburbwireEntry.flags |= 8;
	} else {
		railburbwireEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railburbwireCtorEntry)(void) = railburbwireRegister;
