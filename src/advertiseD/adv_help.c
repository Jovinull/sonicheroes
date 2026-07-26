#include "types.h"

// TAdvHelp: the attract mode help panel. The class names itself, the same way
// TAdvBar does - the constructor stores the string "TAdvHelp" at this+0x0.
//
// The translation unit runs from fn_1_10ED8 at 0x10ED8 to the end of
// fn_1_10FD8 at 0x11000. fn_1_10ED8 is the destructor and fn_1_10F40 the
// constructor, both returning the object; lbl_1_data_7D98 is the vtable, which
// both of them store at this+0x18. The .data is left to the module and only
// referenced here: this unit emits none of its own.
//
// fn_1_10FB0 and fn_1_10FD8 open and close the resource the panel needs, named
// by the descriptor at .data 0x7C9C ("./advertise/adv_help.one").
//
// The constructor ignores its second argument. It is there because the caller
// in attract_object.c passes one, the same shape the emblem task has in
// autosaveD.
//
// It is the same four functions as adv_bar.c against a different set of
// descriptors, which is how the original has them: two separate units rather
// than one shared one.

typedef struct HelpEntry {
	const char* name; // 0x00
	f32 value;        // 0x04
} HelpEntry;

typedef struct HelpDesc {
	s32 unk0;           // 0x00
	s32 unk4;           // 0x04
	HelpEntry* entries; // 0x08
	u8 unkC[0x5C];      // 0x0C
} HelpDesc;

typedef struct AdvHelp {
	const char* name; // 0x00
	u8 unk4[0x14];    // 0x04
	void* vtable;     // 0x18
	u8 unk1C[0x2];    // 0x1C
	u16 unk1E;        // 0x1E
	u8 unk20[0x8];    // 0x20
	HelpDesc* desc;   // 0x28
	f32 unk2C;        // 0x2C
} AdvHelp;

extern "C" const char* lbl_1_data_7BF4;
extern "C" HelpDesc lbl_1_data_7C18;
extern "C" u8 lbl_1_data_7C9C[0x18];
extern "C" u8 lbl_1_data_7D98[0x30];

extern "C" void dtor_800186D0(AdvHelp* help, s32 flag);
extern "C" void fn_80018818(AdvHelp* help);
extern "C" void fn_8012CA94(void* resource);
extern "C" void fn_8012CB70(void* resource);
extern "C" void fn_1_AEC(void* memory);

extern "C" AdvHelp* fn_1_10ED8(AdvHelp* help, s16 free)
{
	if (help != NULL) {
		help->vtable = lbl_1_data_7D98;
		dtor_800186D0(help, 0);
		if (free > 0) {
			fn_1_AEC(help);
		}
	}
	return help;
}

extern "C" AdvHelp* fn_1_10F40(AdvHelp* help, void* owner)
{
	fn_80018818(help);
	help->vtable = lbl_1_data_7D98;
	help->name   = lbl_1_data_7BF4;
	help->unk1E  = 0x30;
	help->desc   = &lbl_1_data_7C18;
	help->unk2C  = help->desc->entries->value;
	return help;
}

extern "C" void fn_1_10FB0(void)
{
	fn_8012CA94(lbl_1_data_7C9C);
}

extern "C" void fn_1_10FD8(void)
{
	fn_8012CB70(lbl_1_data_7C9C);
}
