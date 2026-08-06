#include "types.h"

// The record that registers S03D Pipe Design with the editor.
//
// The claim is .text 0x83304 to 0x833B0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cfff" is the field type string: one character per parameter the
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
extern "C" void s03dPipeDesignLoad(void);
extern "C" void s03dPipeDesignUnload(void);
extern "C" void s03dPipeDesignCreate(void);
extern "C" ObjectEntry s03dPipeDesignEntry;
extern "C" char s03dPipeDesignDisplayName[];
extern "C" char s03dPipeDesignFieldTypes[];
extern "C" const char* s03dPipeDesignFieldNames[];

extern "C" void s03dPipeDesignRegister(void)
{
	s03dPipeDesignEntry.flags = 0;
	s03dPipeDesignEntry.unk18 = 0;

	s03dPipeDesignEntry.name   = s03dPipeDesignDisplayName;
	s03dPipeDesignEntry.load   = s03dPipeDesignLoad;
	s03dPipeDesignEntry.unload = s03dPipeDesignUnload;
	s03dPipeDesignEntry.create = s03dPipeDesignCreate;
	s03dPipeDesignEntry.reset  = NULL;

	s03dPipeDesignEntry.flags = 0x21000;
	s03dPipeDesignEntry.unk18 = 0;
	s03dPipeDesignEntry.unk20 = 0xa;
	s03dPipeDesignEntry.unk1C = 0x383;
	s03dPipeDesignEntry.unk1E = 2;
	s03dPipeDesignEntry.unk21 = 0;

	s03dPipeDesignEntry.fieldTypes = s03dPipeDesignFieldTypes;
	s03dPipeDesignEntry.fieldNames = s03dPipeDesignFieldNames;

	if (s03dPipeDesignFieldTypes != NULL) {
		s03dPipeDesignEntry.flags |= 8;
	} else {
		s03dPipeDesignEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03dPipeDesignCtorEntry)(void) = s03dPipeDesignRegister;
