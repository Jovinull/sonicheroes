#include "types.h"

// Shared editor registration record used by the stages that provide the
// no-ottotto collision object outside the stage11 implementation TU.

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	s16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

extern "C" void noOttottoCollisionCreate(void);
extern "C" ObjectEntry noOttottoCollisionEntry;
extern "C" char noOttottoCollisionDisplayName[];
extern "C" char noOttottoCollisionFieldTypes[];
extern "C" const char* noOttottoCollisionFieldNames[];

extern "C" void noOttottoCollisionRegister(void)
{
	noOttottoCollisionEntry.flags  = 0;
	noOttottoCollisionEntry.unk18  = 0;
	noOttottoCollisionEntry.name   = noOttottoCollisionDisplayName;
	noOttottoCollisionEntry.load   = NULL;
	noOttottoCollisionEntry.unload = NULL;
	noOttottoCollisionEntry.create = noOttottoCollisionCreate;
	noOttottoCollisionEntry.reset  = NULL;

	noOttottoCollisionEntry.flags = 0x20000;
	noOttottoCollisionEntry.unk18 = 0;
	noOttottoCollisionEntry.unk20 = 10;
	noOttottoCollisionEntry.unk1C = 130;
	noOttottoCollisionEntry.unk1E = 2;
	noOttottoCollisionEntry.unk21 = 0;

	noOttottoCollisionEntry.fieldTypes = noOttottoCollisionFieldTypes;
	noOttottoCollisionEntry.fieldNames = noOttottoCollisionFieldNames;
	if (noOttottoCollisionFieldTypes != NULL) {
		noOttottoCollisionEntry.flags |= 8;
	} else {
		noOttottoCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const noOttottoCollisionCtorEntry)(void)
    = noOttottoCollisionRegister;
