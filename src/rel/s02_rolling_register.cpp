#include "types.h"

// The static initializer of the rolling stone's unit in stage01D (named
// s02RollingRegister after its record): it sets the unit's float to 80 + 40,
// then registers S02 ROLLING (its Load, Unload and Create hooks) and S02
// Rolling Colli (only a Create, rel/s02_rolling_cl_create.cpp's fn_3_9FC0C)
// with the editor, as rel/s02_colli_for_quake_register.cpp registers one: the
// run at .text 0xA28C4 to 0xA2A28 and the .ctors word at 0x11C.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void s02RollingLoad(void);
extern "C" void s02RollingUnload(void);
extern "C" void s02RollingCreate(void);
extern "C" void fn_3_9FC0C(void);
extern "C" ObjectEntry s02RollingEntry;
extern "C" ObjectEntry s02RollingColliEntry;
extern "C" char s02RollingDisplayName[];
extern "C" char s02RollingFieldTypes[];
extern "C" const char* s02RollingFieldNames[];
extern "C" char s02RollingColliDisplayName[];
extern "C" char s02RollingColliFieldTypes[];
extern "C" const char* s02RollingColliFieldNames[];
extern "C" f32 lbl_3_bss_1B30;
extern "C" const f32 lbl_3_rodata_1A00;
extern "C" f32 lbl_3_data_12474;

extern "C" void s02RollingRegister(void)
{
	lbl_3_bss_1B30 = lbl_3_rodata_1A00 + lbl_3_data_12474;

	s02RollingEntry.flags = 0;
	s02RollingEntry.unk18 = 0;

	s02RollingEntry.name   = s02RollingDisplayName;
	s02RollingEntry.load   = s02RollingLoad;
	s02RollingEntry.unload = s02RollingUnload;
	s02RollingEntry.create = s02RollingCreate;
	s02RollingEntry.reset  = NULL;

	s02RollingEntry.flags = 0x20000;
	s02RollingEntry.unk18 = 0;
	s02RollingEntry.unk20 = 100;
	s02RollingEntry.unk1C = 516;
	s02RollingEntry.unk1E = 2;
	s02RollingEntry.unk21 = 0;

	s02RollingEntry.fieldTypes = s02RollingFieldTypes;
	s02RollingEntry.fieldNames = s02RollingFieldNames;

	if (s02RollingEntry.fieldTypes != NULL) {
		s02RollingEntry.flags |= 8;
	} else {
		s02RollingEntry.flags &= ~8;
	}

	s02RollingColliEntry.flags = 0;
	s02RollingColliEntry.unk18 = 0;

	s02RollingColliEntry.name   = s02RollingColliDisplayName;
	s02RollingColliEntry.load   = NULL;
	s02RollingColliEntry.unload = NULL;
	s02RollingColliEntry.create = fn_3_9FC0C;
	s02RollingColliEntry.reset  = NULL;

	s02RollingColliEntry.flags = 0x20000;
	s02RollingColliEntry.unk18 = 0;
	s02RollingColliEntry.unk20 = 50;
	s02RollingColliEntry.unk1C = 524;
	s02RollingColliEntry.unk1E = 2;
	s02RollingColliEntry.unk21 = 0;

	s02RollingColliEntry.fieldTypes = s02RollingColliFieldTypes;
	s02RollingColliEntry.fieldNames = s02RollingColliFieldNames;

	if (s02RollingColliEntry.fieldTypes != NULL) {
		s02RollingColliEntry.flags |= 8;
	} else {
		s02RollingColliEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02RollingCtorEntry)(void) = s02RollingRegister;
