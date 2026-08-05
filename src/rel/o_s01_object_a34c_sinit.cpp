#include "types.h"

// The static initializer of the object class whose destructor and factory are in
// rel/o_s01_object_a34c_dtor.cpp and rel/o_s01_object_a34c_create.cpp. It fills
// the editor's registration record for the class and registers itself in
// .ctors.
//
// The claim is .text 0x0007D8BC to 0x0007D968 and .ctors 0x000000C8 to
// 0x000000CC. Everything it writes stays in the module's data and bss and is
// only referenced here, so the unit owns no data of its own.
//
// The record is the SETOBJ_PARAM that rel/o_s01_ciseki.cpp already describes,
// and the assignment order is that unit's too: the flags and the field after
// them are cleared first, then every field is written in declaration order, and
// the trailing test folds bit 3 in or out depending on whether the field-type
// string is present. It is written out as separate assignments rather than an
// aggregate initializer because that is what reproduces the two writes to the
// flags word.
//
// Its create slot is the factory matched earlier, which is how the record is
// tied to that class rather than to the one at data 0xA1C8.
//
// The exec and display slots at +0x04 and +0x08 are still assembly and keep
// their placeholder names. Those carry the module id, which is safe only
// because this source belongs to stage01D alone, like the other o_s01_* units.

typedef struct SETOBJ_PARAM {
	char* displayName; // 0x00
	void (*exec)();    // 0x04
	void (*disp)();    // 0x08
	void (*create)();  // 0x0C
	u32 field10;       // 0x10
	u32 flags;         // 0x14
	u32 field18;       // 0x18
	u16 id;            // 0x1C
	u16 count;         // 0x1E
	u8 field20;        // 0x20
	u8 field21;        // 0x21
	u8 pad22[2];       // 0x22
	char* fieldTypes;  // 0x24
	void* fields;      // 0x28
	u32 pad2C;         // 0x2C
} SETOBJ_PARAM;        // 0x30

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" SETOBJ_PARAM s01ObjectA34CParam;
extern "C" char s01ObjectA34CDisplayName[];
extern "C" char s01ObjectA34CFieldTypes[];
extern "C" void* s01ObjectA34CFields;

extern "C" void fn_3_7D728();
extern "C" void fn_3_7D66C();
extern "C" void s01ObjectA34CCreate();

extern "C" void __sinit_o_s01_object_a34c_cpp()
{
	s01ObjectA34CParam.flags       = 0;
	s01ObjectA34CParam.field18     = 0;
	s01ObjectA34CParam.displayName = s01ObjectA34CDisplayName;
	s01ObjectA34CParam.exec        = fn_3_7D728;
	s01ObjectA34CParam.disp        = fn_3_7D66C;
	s01ObjectA34CParam.create      = s01ObjectA34CCreate;
	s01ObjectA34CParam.field10     = 0;
	s01ObjectA34CParam.flags       = 0x21000;
	s01ObjectA34CParam.field18     = 0;
	s01ObjectA34CParam.field20     = 20;
	s01ObjectA34CParam.id          = 393;
	s01ObjectA34CParam.count       = 2;
	s01ObjectA34CParam.field21     = 0;
	s01ObjectA34CParam.fieldTypes  = s01ObjectA34CFieldTypes;
	s01ObjectA34CParam.fields      = &s01ObjectA34CFields;

	if (s01ObjectA34CParam.fieldTypes != NULL)
		s01ObjectA34CParam.flags |= 8;
	else
		s01ObjectA34CParam.flags &= ~8;
}

__declspec(section ".ctors") void (*const S01ObjectA34CCtorEntry)() = __sinit_o_s01_object_a34c_cpp;
