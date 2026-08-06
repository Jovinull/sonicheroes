#include "types.h"

// The record that registers TRAINCOLLISION with the editor.
//
// The claim is .text 0x9313C to 0x931EC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FiFi" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void traincollisionLoad(void);
extern "C" void traincollisionUnload(void);
extern "C" void traincollisionCreate(void);
extern "C" void traincollisionReset(void);
extern "C" ObjectEntry traincollisionEntry;
extern "C" char traincollisionDisplayName[];
extern "C" char traincollisionFieldTypes[];
extern "C" const char* traincollisionFieldNames[];

extern "C" void traincollisionRegister(void)
{
	traincollisionEntry.flags = 0;
	traincollisionEntry.unk18 = 0;

	traincollisionEntry.name   = traincollisionDisplayName;
	traincollisionEntry.load   = traincollisionLoad;
	traincollisionEntry.unload = traincollisionUnload;
	traincollisionEntry.create = traincollisionCreate;
	traincollisionEntry.reset  = traincollisionReset;

	traincollisionEntry.flags = 0x20000;
	traincollisionEntry.unk18 = 0;
	traincollisionEntry.unk20 = 0xf;
	traincollisionEntry.unk1C = 0x740;
	traincollisionEntry.unk1E = 2;
	traincollisionEntry.unk21 = 0;

	traincollisionEntry.fieldTypes = traincollisionFieldTypes;
	traincollisionEntry.fieldNames = traincollisionFieldNames;

	if (traincollisionFieldTypes != NULL) {
		traincollisionEntry.flags |= 8;
	} else {
		traincollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const traincollisionCtorEntry)(void) = traincollisionRegister;
