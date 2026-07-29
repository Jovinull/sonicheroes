#include "types.h"

// ADV_CHALLENGE (challenge-mode select screen) translation unit.
//
// Reference-guided from the Sonic Heroes PS2 Sep-28-2003 debug prototype:
// class ADV_CHALLENGE plus its four bundled sub-object classes
// TAdvChallengeTitle / TAdvChallengeArrow / TAdvChallengeEmblem /
// TAdvChallengeEme, source file D:\Tsonic\Tsonic\src\advertise\adv_challenge.cpp.
// The GameCube retail REL bytes are ground truth; the PS2 build only supplies
// names/types/signatures/logic shape.
//
// Sub-object vtable -> class map (from ctor typename stores):
//   lbl_1_data_3740 = TAdvChallengeEme
//   lbl_1_data_3794 = TAdvChallengeEmblem
//   lbl_1_data_37C0 = TAdvChallengeArrow
//   lbl_1_data_37EC = TAdvChallengeTitle
//   lbl_1_data_3818 = ADV_CHALLENGE (main screen)

// One positioned entry inside a sprite bank (stride 8; only the .y matters).
struct SubPos {
	/* 0x00 */ u32 unk_0x00;
	/* 0x04 */ f32 y;
};

// A shared sprite/font bank object. Field 0x8 is the positioned-entry array.
struct Sub {
	/* 0x00 */ u8 pad_0x00[0x8];
	/* 0x08 */ SubPos* pos;
	/* 0x0c */ u8 pad_0x0c[0x5C];
}; // 0x68

// Common layout of the four TAdvChallenge* sub-objects. They derive from a
// shared engine base (ctor __ct__7TObjectFP7TObject / dtor __dt__7TObjectFv); the derived
// fields begin at 0x28.
struct TAdvChallengeSub {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad_0x04[0x14];
	/* 0x18 */ void* vtable;
	/* 0x1c */ u8 pad_0x1c[0x2];
	/* 0x1e */ u16 size;
	/* 0x20 */ u8 pad_0x20[0x8];
	/* 0x28 */ Sub* sub;
	/* 0x2c */ f32 value;
	/* 0x30 */ f32 target;
	/* 0x34 */ s32 flag;
	/* 0x38 */ s32 mode;
};

// One row of a per-stage/char selection table (stride 8).
struct AdvEntry {
	/* 0x00 */ u8 b[0x8];
};

// The ADV_CHALLENGE main select-screen object (vtable 0x3818). Only the fields
// touched so far are named; the rest are explicit padding.
struct ADV_CHALLENGE {
	/* 0x000 */ u8 pad_0x00[0x18];
	/* 0x018 */ void* vtable;
	/* 0x01c */ u8 pad_0x1c[0x2];
	/* 0x01e */ u16 size;
	/* 0x020 */ u8 pad_0x20[0x8];
	/* 0x028 */ s32 unk_0x28;
	/* 0x02c */ s32 mode;
	/* 0x030 */ u8 pad_0x30[0x4];
	/* 0x034 */ f32 unk_0x34;
	/* 0x038 */ void* unk_0x38;
	/* 0x03c */ u8 pad_0x3c[0x4];
	/* 0x040 */ s32 unk_0x40;
	/* 0x044 */ s32 unk_0x44;
	/* 0x048 */ s32 unk_0x48;
	/* 0x04c */ u8 pad_0x4c[0x14];
	/* 0x060 */ s32 unk_0x60;
	/* 0x064 */ s32 unk_0x64;
	/* 0x068 */ s32 unk_0x68;
	/* 0x06c */ s32 unk_0x6c;
	/* 0x070 */ u32 unk_0x70;
	/* 0x074 */ u32 unk_0x74;
	/* 0x078 */ u8 pad_0x78[0x8];
	/* 0x080 */ u8 obj_0x80[0x4];
	/* 0x084 */ s32 unk_0x84;
	/* 0x088 */ s32 unk_0x88;
	/* 0x08c */ s32 unk_0x8c;
	/* 0x090 */ s32 unk_0x90;
	/* 0x094 */ s32 unk_0x94;
	/* 0x098 */ s32 unk_0x98;
	/* 0x09c */ u8 obj_0x9c[0x70];
	/* 0x10c */ u8 obj_0x10c[0x8c];
	/* 0x198 */ u8 obj_0x198[0x8c];
	/* 0x224 */ s32 stage;
	/* 0x228 */ s32 charSel;
	/* 0x22c */ s32 mission;
	/* 0x230 */ void* unk_0x230;
	/* 0x234 */ TAdvChallengeSub* arrow;
	/* 0x238 */ TAdvChallengeSub* unk_0x238;
	/* 0x23c */ TAdvChallengeSub* unk_0x23c;
	/* 0x240 */ void* unk_0x240;
	/* 0x244 */ s32 sel[22];
	/* 0x29c */ s32 timer;
	/* 0x2a0 */ u8 pad_0x2a0[0x160];
	/* 0x400 */ Sub* unk_0x400;
	/* 0x404 */ f32 unk_0x404;
	/* 0x408 */ s32 unk_0x408;
};

// A per-slot option record populated from the config service.
struct AdvOpt {
	/* 0x00 */ u8 pad_0x00[0x1c];
	/* 0x1c */ s8 unk_0x1c;
	/* 0x1d */ s8 unk_0x1d;
	/* 0x1e */ u8 pad_0x1e[0x5];
	/* 0x23 */ s8 unk_0x23;
	/* 0x24 */ u8 pad_0x24[0x14];
	/* 0x38 */ s32 unk_0x38;
};

extern "C" {

// Module-shared data (dtk-named; addresses are ground truth).
extern u8 lbl_1_data_3740;          // TAdvChallengeEme vtable
extern u8 lbl_1_data_3794;          // TAdvChallengeEmblem vtable
extern u8 lbl_1_data_37C0;          // TAdvChallengeArrow vtable
extern u8 lbl_1_data_37EC;          // TAdvChallengeTitle vtable
extern u8 lbl_1_data_3818;          // ADV_CHALLENGE main vtable
extern void* const lbl_1_data_373C; // -> "TAdvChallengeEme"
extern void* const lbl_1_data_3724; // -> "TAdvChallengeEmblem"
extern void* const lbl_1_data_370C; // -> "TAdvChallengeArrow"
extern void* const lbl_1_data_36F4; // -> "TAdvChallengeTitle"
extern Sub lbl_1_data_3060[6];      // shared sprite banks (stride 0x68)
extern const f32 lbl_1_rodata_F40;  // 0.0
extern const f32 lbl_1_rodata_F44;  // 1.0

// Engine base + render helpers (DOL / other REL objects).
// The engine base ctor takes (self, parent) and returns self; the sub-object
// ctors that wrap it ignore the return, fn_1_A208 uses it for the node list.
extern void* __ct__7TObjectFP7TObject(void* self, void* parent);
extern void __dt__7TObjectFv(TAdvChallengeSub* self, s32 flag);
extern void fn_8012CC20(Sub* s);
extern void fn_8012CEF0(Sub* s, f32 v);
extern void* advE3Rom_resume(s32 size);
extern void fn_1_10F40(void* child, TAdvChallengeSub* self);
extern void advE3Rom_pause(void* self);

// Constructor fn_1_89E4 defined after fn_1_A208 so its call there stays a bl.

// Getter for the enable flag (defined at file end so fn_1_9CCC keeps its call).
s32 fn_1_8A60(TAdvChallengeSub* self);

// Set the display value from a positioned entry (index = a*2 [+1 if b]).
// Enable/Disable/SetValue are defined after fn_1_945C so MWCC keeps its calls
// to them out-of-line (bl) rather than inlining these small helpers.
void fn_1_8A68(TAdvChallengeSub* self, s32 a, s32 b);
void fn_1_8A9C(TAdvChallengeSub* self);
void fn_1_8AA8(TAdvChallengeSub* self);

// Constructor fn_1_8B8C (bank index = arg + 1) defined after fn_1_A208.

// ---- TAdvChallengeArrow (vtable 0x37C0) --------------------------------

// Right/Left defined near end of file so MWCC keeps them out-of-line calls
// from the ADV_CHALLENGE delegators (fn_1_9AEC/fn_1_9AC0).
void fn_1_8C1C(TAdvChallengeSub* self);
void fn_1_8C28(TAdvChallengeSub* self);

// SetMode (defined after fn_1_8D18 so MWCC keeps it an out-of-line call there).
void fn_1_8C34(TAdvChallengeSub* self, s32 mode);

// Constructor fn_1_8FA8 defined after fn_1_A208.

// ---- ADV_CHALLENGE main screen (vtable 0x3818) -------------------------

extern AdvEntry lbl_1_rodata_D70[22];
extern AdvEntry lbl_1_rodata_E20[22];
extern const f32 lbl_1_rodata_102C; // 0.0
extern u8 lbl_8042C0C0;
extern void* lbl_8042C180;
extern void fn_1_7B24(void* dst, AdvEntry* src);
extern void fn_1_922C(ADV_CHALLENGE* self);
extern void fn_1_945C(ADV_CHALLENGE* self);
extern s32 fn_1_12A0(void* obj, s32 x);

// Stage/char navigation delegators + SetStage/SetChar (defined at file end so
// fn_1_9E20 / fn_1_A208 keep out-of-line calls to them).
void fn_1_9AC0(ADV_CHALLENGE* self);
void fn_1_9AEC(ADV_CHALLENGE* self);
void fn_1_9B18(ADV_CHALLENGE* self);
void fn_1_9B64(ADV_CHALLENGE* self);
void fn_1_9BB0(ADV_CHALLENGE* self, s32 mission);
void fn_1_9CA4(ADV_CHALLENGE* self);
void fn_1_9BD4(ADV_CHALLENGE* self, s32 stage);
void fn_1_9BF8(ADV_CHALLENGE* self, s32 charSel);

// Config-service accessors (defined at file end so the ExecSelect handlers
// keep out-of-line calls to them).
s32 fn_1_A9E0(void* self);

extern u8 lbl_80303EC8;
extern u8 lbl_803E774C;
extern void fn_800A8C38(void* obj);
extern void fn_800A8C20(void* obj);
extern void fn_800A96B0(void* obj, s32 id, s32 val);
extern AdvOpt* fn_80116D2C(void* p);
extern void fn_801D5B9C(s32 v);
extern void fn_800B41A0(s32 v);
extern void advE3Rom_setFlag(void* p);
extern ADV_CHALLENGE* fn_1_A208(ADV_CHALLENGE* self, void* parent);

// Count decoded lines in a u16 string (defined near file end; forward decl so
// the display-request builders keep out-of-line calls to it).
s32 fn_1_A6DC(void* self, u16* str);

void fn_1_A72C(void* self, s32 flag);
s32 fn_1_A76C(void* self);
void fn_1_A79C(void* self, s32 arg);
s32 fn_1_A808(void* self);
s32 fn_1_A91C(void* self);
void fn_1_A954(void* self, s32 flag);
void fn_1_AA10(void* self, s32 arg);

// Remap the difficulty index (defined at file end so B9E8 keeps its call).
void fn_1_A85C(void* self, s32 arg);

extern void* const lbl_1_data_36DC; // -> "ADV_CHALLENGE"
extern void fn_800A8828(void* self, void* parent);
extern void fn_1_12124(void* panel);
extern void fn_1_119D4(void* cursor);
extern void fn_1_120C4(void* cursor, s32 i);
extern void fn_1_119E0(void* cursor, s32 val);
extern void __ct__10DAnimClassFv(ADV_CHALLENGE* self, s32 arg);
struct TObject {
	u8 data[0x28];
	static void* operator new(unsigned long size) { return advE3Rom_resume(size); }
	TObject(TObject* parent);
};

struct TAdvChallengeTitle {
	u8 data[0x34];
	static void* operator new(unsigned long size) { return advE3Rom_resume(size); }
	TAdvChallengeTitle(TObject* parent);
};

struct TAdvChallengeArrow {
	u8 data[0x3c];
	static void* operator new(unsigned long size) { return advE3Rom_resume(size); }
	TAdvChallengeArrow(TObject* parent);
};

struct TAdvChallengeEmblem {
	u8 data[0x38];
	static void* operator new(unsigned long size) { return advE3Rom_resume(size); }
	TAdvChallengeEmblem(TObject* parent, s32 bank);
};

struct TAdvChallengeEme {
	u8 data[0x38];
	static void* operator new(unsigned long size) { return advE3Rom_resume(size); }
	TAdvChallengeEme(TObject* parent);
};

extern void fn_1_120E0(void* obj, s32 flag);
extern void fn_800A8620(ADV_CHALLENGE* self, s32 flag);
extern void fn_1_92D0(ADV_CHALLENGE* self, s8* out, s32 arg, s32 charSel);
extern void fn_1_9C30(ADV_CHALLENGE* self);
extern void fn_1_9CCC(ADV_CHALLENGE* self);
extern void fn_1_9E20(ADV_CHALLENGE* self);
extern void fn_1_905C(ADV_CHALLENGE* self);

// Shared sprite banks (defined below; forward-declared for the draw pass).
extern u32 lbl_1_bss_590[22][2];
extern u32 lbl_1_bss_640[22][2];
extern u32 lbl_1_bss_6F0[12];
extern void fn_801A45A0(u32 obj, u32 pos);
s32 fn_1_901C(ADV_CHALLENGE* self, s32 entry);

// A displayable list node (intrusive singly-linked via 0xc).
struct Node {
	/* 0x00 */ u8 pad_0x00[0xc];
	/* 0x0c */ Node* next;
};

// The list container held at ADV_CHALLENGE::unk_0x230 (head at 0x14).
struct NodeList {
	/* 0x00 */ u8 pad_0x00[0x14];
	/* 0x14 */ Node* head;
};

// A per-row selection table entry (a = position index, b = payload).
struct TabEntry {
	/* 0x00 */ u32 a;
	/* 0x04 */ u32 b;
};

extern void* lbl_1_data_11A4;
extern Sub lbl_1_data_3AB4;
extern s32 fn_1_86B0(Node* n, void* key);
extern void fn_1_55A4(Node* n, s32 v);

// Load a selection-table row into the live position fields (defined at file
// end so the ExecSelect handlers keep out-of-line calls to it).
void fn_1_B03C(ADV_CHALLENGE* self, TabEntry* table, s32 idx);

extern u8 lbl_8029C310;
extern s32 lbl_1_rodata_BD0[22];
extern u8 lbl_1_rodata_CD8[];
extern void fn_8001867C(void* list);

struct MakePlayerTmp {
	/* 0x00 */ s32 index;
	/* 0x04 */ u8 sub[0xc];
	/* 0x10 */ s32 flag;
};

extern void fn_1_6ABC(MakePlayerTmp* p);
extern void fn_1_5994(void* sub, void* entry);
extern void fn_1_63A8(void* list, MakePlayerTmp* p);

// MakePlayer (defined at file end so fn_1_9BF8 keeps its out-of-line call).
void fn_1_922C(ADV_CHALLENGE* self);
extern void fn_800191F8(void* obj, s32 a, s32 b);
extern void fn_8001938C(void* obj);
extern void fn_8001934C(void* obj, s32 a, s32 b);
extern void fn_8001936C(void* obj, s32 a, s32 b);

// GotoGame (defined at file end so fn_1_9CCC keeps its call).
void fn_1_9954(ADV_CHALLENGE* self);

// ---- CLASS_GDISP_CHALLENGE (large display object) ----------------------

struct GdispChallenge {
	/* 0x000 */ u8 pad_0x00[0x2c];
	/* 0x02c */ s32 unk_0x2c;
	/* 0x030 */ u8 pad_0x30[0x18];
	/* 0x048 */ s32 unk_0x48;
	/* 0x04c */ u8 pad_0x4c[0x34];
	/* 0x080 */ s32 unk_0x80;
	/* 0x084 */ u8 pad_0x84[0x360];
	/* 0x3e4 */ s32 unk_0x3e4;
	/* 0x3e8 */ s32 unk_0x3e8;
	/* 0x3ec */ s32 unk_0x3ec;
	/* 0x3f0 */ u8 pad_0x3f0[0x8];
	/* 0x3f8 */ u32 unk_0x3f8;
	/* 0x3fc */ void* unk_0x3fc;
};

// Free the held object at 0x3fc. Defined at file end so MWCC keeps every
// call to it out-of-line (bl), matching the original.
void fn_1_AAC0(GdispChallenge* self);

extern s32 fn_801248F8(s32 v);
extern s32 fn_1_146C0(void* p);
extern void fn_1_AB00(GdispChallenge* self);
void fn_1_B674(GdispChallenge* self);

extern void fn_80116B60(void* p, s32 v);
extern s32 fn_80124924(s32 v);
extern s32 fn_8012491C(s32 v);
extern void* fn_8012ECA8(s32 a, s32 b);
extern void fn_1_B218(
    GdispChallenge* self, void* a, void* b, void* c, void* d, s32 e, s32 f, s32 g, s32 h);

extern s32 fn_8012586C(s32 v);

// ---- Shared sprite-bank tables (ADV_CHALLENGE data view) ---------------

struct Data32F4 {
	/* 0x00 */ u8 pad_0x00[0xc];
	/* 0x0c */ void* handle;
	/* 0x10 */ u8 pad_0x10[0x8];
}; // 0x18

struct Vec3w {
	u32 w[3];
};

extern u32 lbl_1_bss_590[22][2];
extern u32 lbl_1_bss_640[22][2];
extern u32 lbl_1_bss_6F0[12];
extern void* lbl_1_data_35CC[22][2];
extern void* lbl_1_data_36B4[6];
extern Data32F4 lbl_1_data_32F4;
extern const Vec3w lbl_1_rodata_F28;
extern void fn_1_11750(s32 v);
extern void fn_1_65BC(void);
extern void fn_1_64E0(void);
extern void fn_800A8C9C(void* obj, Vec3w* v);
extern void fn_8012CB70(Data32F4* d);
extern void fn_8012CA94(Data32F4* d);
extern void fn_801A45A0(u32 obj, u32 pos);
extern u32 fn_801A4BBC(void* handle, void* name);

extern s32 lbl_1_rodata_ED0[];

// A display-request descriptor filled on the stack for fn_1_150AC.
struct DispReq {
	/* 0x00 */ void* obj;
	/* 0x04 */ u32 m4;
	/* 0x08 */ u32 m8;
	/* 0x0c */ u32 mc;
	/* 0x10 */ s32 flag;
	/* 0x14 */ f32 f14;
	/* 0x18 */ f32 f18;
	/* 0x1c */ f32 f1c;
	/* 0x20 */ f32 f20;
	/* 0x24 */ f32 f24;
	/* 0x28 */ u8 pad_0x28[0x20];
}; // 0x48

extern const f32 lbl_1_rodata_1030;
extern const f32 lbl_1_rodata_1034;
extern const f32 lbl_1_rodata_1038;
extern const f32 lbl_1_rodata_103C;
extern const f32 lbl_1_rodata_1040;
extern const f32 lbl_1_rodata_1044;
extern const f32 lbl_1_rodata_1050;
extern const f32 lbl_1_rodata_1054;
extern const f32 lbl_1_rodata_1058;
extern const f32 lbl_1_rodata_105C;
extern void fn_1_152C0(DispReq* r);
extern void* fn_1_150AC(GdispChallenge* self, DispReq* r);

extern s32 fn_80116B68(void* p);
extern void fn_8012EC18(void* buf, void* fmt, ...);
extern void* lbl_8042C388;
extern TabEntry lbl_1_rodata_FB0[];
extern s32 fn_1_11FFC(void* cursor, s32 arg);
extern void fn_800A8120(ADV_CHALLENGE* self);
extern void fn_800A8174(ADV_CHALLENGE* self, s32 id);
extern s32 fn_800A9398(void* obj, s32 arg);
extern void fn_800B52E8(void* obj, s32 id, s32 a, s32 b);

extern TabEntry lbl_1_rodata_F90[];
extern Sub lbl_1_data_3AB4;
extern const f32 lbl_1_rodata_1060;
extern const f32 lbl_1_rodata_1064;
extern s32 fn_1_11E48(void* cursor, s32 arg);
extern TabEntry lbl_1_rodata_FC8[];
extern TabEntry lbl_1_rodata_FD8[];
extern void fn_1_119E0(void* cursor, s32 val);
extern void fn_800A9224(void* obj);
extern TabEntry lbl_1_rodata_F48[];
extern s32 lbl_1_rodata_1018[];
extern AdvEntry lbl_1_rodata_F70[];
extern s32 fn_1_11AA8(void* cursor, s32 a, s32 b, s32 c);

extern s32 lbl_1_rodata_D68[];
extern void fn_80014154(void);

extern s32 fn_1_146C0(void* p);
extern s32 fn_8012554C(s32 v);
extern s32 fn_80124924(s32 v);

// One decoded data record read out of the option table (r26 target).
struct DataRec {
	/* 0x00 */ s16 h0;
	/* 0x02 */ u8 pad_0x02[0x2];
	/* 0x04 */ u32 w4;
	/* 0x08 */ s8 b8;
	/* 0x09 */ s8 b9;
	/* 0x0a */ s8 ba;
}; // 0xc

struct ActionValues {
	s8 score;
	s8 time;
};

struct RowB {
	s8 b0;
	s8 b1;
	s8 b2;
	u8 b3;
};

struct ExtraData {
	u8 padding[0x470];
	u8 rows[1][0x10];
};

// Watch-slot destinations for the debug value display (stride 0xc).
struct WatchSlot {
	u8 pad[0xc];
};

extern WatchSlot lbl_1_data_3018[5];
extern WatchSlot lbl_1_data_3054;
extern u8 lbl_1_data_376C;
extern u8 lbl_1_data_3774;
extern u8 lbl_1_data_377C;
extern u8 lbl_1_data_3784;
extern u8 lbl_1_data_3788;
extern u8 lbl_1_data_2F18;
extern u8 lbl_1_data_2BC8;
extern u8 lbl_1_data_300C;
extern s32 lbl_1_rodata_C28[22];
extern s32 lbl_1_rodata_C80[22];
extern void fn_8012C858(void* slot, const char* fmt, ...);
extern s32 fn_80116A8C(void* p, s32 v);
extern void fn_1_88D0(void* obj, s32 v);
extern void fn_1_88C4(void* obj);

#pragma dont_inline on
// ---- TAdvChallengeEme (vtable 0x3740) ----------------------------------

// Exec: tick the sprite bank while enabled.
void fn_1_890C(TAdvChallengeSub* self)
{
	if (self->sub != 0 && self->flag != 0) {
		fn_8012CC20(self->sub);
	}
}

// Disp: draw the sprite bank at the current value.
void fn_1_8948(TAdvChallengeSub* self)
{
	if (self->sub != 0) {
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvChallengeSub* fn_1_897C(TAdvChallengeSub* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_3740;
		__dt__7TObjectFv(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// TAdvChallengeEme constructor.
TAdvChallengeEme::TAdvChallengeEme(TObject* parent)
{
	TAdvChallengeSub* self = (TAdvChallengeSub*)this;
	__ct__7TObjectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_3740;
	self->name   = lbl_1_data_373C;
	self->size   = 0x38;
	self->sub    = &lbl_1_data_3060[3];
	self->value  = lbl_1_rodata_F40;
	self->flag   = 0;
}

// Getter for the enable flag.
s32 fn_1_8A60(TAdvChallengeSub* self)
{
	return self->flag;
}

// Set the display value from a positioned entry (index = a*2 [+1 if b]).
void fn_1_8A68(TAdvChallengeSub* self, s32 a, s32 b)
{
	s32 idx = a * 2;
	if (b != 0) {
		idx++;
	}
	if (self->sub == 0) {
		return;
	}
	self->value = self->sub->pos[idx].y;
}

// Disable.
void fn_1_8A9C(TAdvChallengeSub* self)
{
	self->flag = 0;
}

// Enable.
void fn_1_8AA8(TAdvChallengeSub* self)
{
	self->flag = 1;
}

// ---- TAdvChallengeEmblem (vtable 0x3794) -------------------------------

// Exec.
void fn_1_8AB4(TAdvChallengeSub* self)
{
	if (self->sub != 0 && self->flag != 0) {
		fn_8012CC20(self->sub);
	}
}

// Disp.
void fn_1_8AF0(TAdvChallengeSub* self)
{
	if (self->sub != 0) {
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvChallengeSub* fn_1_8B24(TAdvChallengeSub* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_3794;
		__dt__7TObjectFv(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// TAdvChallengeEmblem constructor (bank index = arg + 1).
TAdvChallengeEmblem::TAdvChallengeEmblem(TObject* parent, s32 bank)
{
	TAdvChallengeSub* self = (TAdvChallengeSub*)this;
	__ct__7TObjectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_3794;
	self->name   = lbl_1_data_3724;
	self->size   = 0x38;
	self->sub    = &lbl_1_data_3060[bank + 1];
	self->value  = lbl_1_rodata_F40;
	self->flag   = 1;
}

// Point the arrow right.
void fn_1_8C1C(TAdvChallengeSub* self)
{
	self->mode = 3;
}

// Point the arrow left.
void fn_1_8C28(TAdvChallengeSub* self)
{
	self->mode = 2;
}

// SetMode: snap value/target to the bank positions for the given mode.
void fn_1_8C34(TAdvChallengeSub* self, s32 mode)
{
	self->flag = mode;
	self->mode = mode;
	switch (mode) {
		case 1:
			self->value  = self->sub->pos[0].y;
			self->target = self->sub->pos[0].y;
			break;
		case 2:
			self->value  = self->sub->pos[1].y;
			self->target = self->sub->pos[2].y - lbl_1_rodata_F44;
			break;
		case 3:
			self->value  = self->sub->pos[3].y;
			self->target = self->sub->pos[4].y - lbl_1_rodata_F44;
			break;
	}
}

// Exec.
void fn_1_8CEC(TAdvChallengeSub* self)
{
	if (self->sub != 0) {
		fn_8012CC20(self->sub);
	}
}

// Disp: resync mode, animate value toward target, draw.
void fn_1_8D18(TAdvChallengeSub* self)
{
	if (self->flag != self->mode) {
		fn_1_8C34(self, self->mode);
	}
	switch (self->flag) {
		case 1:
			break;
		case 2:
		case 3:
			self->value += lbl_1_rodata_F44;
			if (self->value < self->target) {
				self->mode = 1;
			}
			break;
	}
	if (self->sub != 0) {
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvChallengeSub* fn_1_8DB0(TAdvChallengeSub* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_37C0;
		__dt__7TObjectFv(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// TAdvChallengeArrow constructor.
TAdvChallengeArrow::TAdvChallengeArrow(TObject* parent)
{
	TAdvChallengeSub* self = (TAdvChallengeSub*)this;
	void* child;

	__ct__7TObjectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_37C0;
	self->name   = lbl_1_data_370C;
	self->size   = 0x3c;
	self->sub    = &lbl_1_data_3060[4];
	self->value  = lbl_1_rodata_F40;
	self->flag   = 0;
	self->mode   = 1;

	child = advE3Rom_resume(0x30);
	if (child != 0) {
		fn_1_10F40(child, self);
	}
}

// Constructor fn_1_8E18 defined after fn_1_A208.

// ---- TAdvChallengeTitle (vtable 0x37EC) --------------------------------

// Exec.
void fn_1_8EB4(TAdvChallengeSub* self)
{
	if (self->sub != 0) {
		fn_8012CC20(self->sub);
	}
}

// Disp: scroll the title value up to pos[1], drawing while it moves.
void fn_1_8EE0(TAdvChallengeSub* self)
{
	if (self->sub != 0) {
		if (self->value < self->sub->pos[1].y) {
			self->value += lbl_1_rodata_F44;
		}
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvChallengeSub* fn_1_8F40(TAdvChallengeSub* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_37EC;
		__dt__7TObjectFv(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// TAdvChallengeTitle constructor.
TAdvChallengeTitle::TAdvChallengeTitle(TObject* parent)
{
	TAdvChallengeSub* self = (TAdvChallengeSub*)this;
	__ct__7TObjectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_37EC;
	self->name   = lbl_1_data_36F4;
	self->size   = 0x34;
	self->sub    = &lbl_1_data_3060[5];
	self->value  = lbl_1_rodata_F40;
}

// Test whether the given menu entry is currently selectable.
s32 fn_1_901C(ADV_CHALLENGE* self, s32 entry)
{
	s8 result;

	fn_1_92D0(self, &result, entry, self->charSel);
	return result != 0;
}

// Draw pass: refresh per-item selectability, then blit each sprite bank.
void fn_1_905C(ADV_CHALLENGE* self)
{
	s32 i;
	s32 j;

	for (i = 0; i != 22; i++) {
		self->sel[i] = fn_1_901C(self, i);
	}
	for (j = 0; j != 22; j++) {
		if (self->sel[j] == 0) {
			fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_6F0[0]);
			fn_801A45A0(lbl_1_bss_590[j][1], lbl_1_bss_6F0[1]);
		} else {
			fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_640[j][0]);
			if (j == 5) {
				switch (self->charSel) {
					case 0:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[3]);
						break;
					case 1:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[5]);
						break;
					case 2:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[2]);
						break;
					case 3:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[4]);
						break;
				}
			} else if (j == 14) {
				fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_640[j][0]);
				switch (self->charSel) {
					case 0:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[4]);
						break;
					case 1:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[2]);
						break;
					case 2:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[5]);
						break;
					case 3:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[3]);
						break;
				}
			} else {
				fn_801A45A0(lbl_1_bss_590[j][1], lbl_1_bss_640[j][1]);
			}
		}
	}
}

// MakePlayer: build three player records into the active list.
void fn_1_922C(ADV_CHALLENGE* self)
{
	MakePlayerTmp tmp;
	s32 i;

	if (self->unk_0x230 == 0) {
		return;
	}
	fn_8001867C(self->unk_0x230);
	i = 0;
	do {
		fn_1_6ABC(&tmp);
		tmp.index = i + self->charSel * 3;
		fn_1_5994(&tmp.sub, (u8*)lbl_1_rodata_CD8 + self->charSel * 0x24 + i * 0xc);
		tmp.flag = 1;
		fn_1_63A8(self->unk_0x230, &tmp);
		i++;
	} while (i != 3);
}

// Resolve the rank/emblem bytes for a menu entry into out[0..1].
void fn_1_92D0(ADV_CHALLENGE* self, s8* out, s32 entry, s32 mode)
{
	s8* base;
	s32 x;
	s32 v;

	if (out == 0) {
		return;
	}
	out[0] = 0;
	out[1] = 0;
	fn_80116D2C(&lbl_803E774C);
	base = (s8*)fn_80116D2C(&lbl_803E774C) + 0x3c;
	x    = lbl_1_rodata_ED0[entry];
	if (x < 0xe) {
		switch (mode) {
			case 0:
				v      = base[x * 0x50 + 0x1b];
				out[0] = v;
				v      = base[x * 0x50 + 0x27];
				out[1] = v;
				break;
			case 1:
				v      = base[x * 0x50 + 0x33];
				out[0] = v;
				v      = base[x * 0x50 + 0x37];
				out[1] = v;
				break;
			case 2:
				v      = base[x * 0x50 + 0x43];
				out[0] = v;
				v      = base[x * 0x50 + 0x47];
				out[1] = v;
				break;
			case 3:
				v      = base[x * 0x50 + 0x53];
				out[0] = v;
				v      = base[x * 0x50 + 0x5f];
				out[1] = v;
				break;
		}
	} else {
		if (x == 0x15) {
			v      = base[x * 0x10 + 0x393];
			out[0] = v;
		} else {
			v      = base[x * 0x10 + self->charSel * 4 + 0x393];
			out[0] = v;
		}
	}
}

// UpdateData: refresh the debug value display and the emblem/eme sub-panels
// from the current stage/char/mission selection.
void fn_1_945C(ADV_CHALLENGE* self)
{
	u8* opt;
	ActionValues values;
	s32 x;
	u8* base;
	DataRec* p26;
	u32 p25;
	void* p624;
	s32 offset;
	s32 rowOffset;

	opt          = (u8*)fn_80116D2C(&lbl_803E774C);
	base         = (u8*)fn_80116D2C(&lbl_803E774C) + 0x3c;
	p624         = (s8*)fn_80116D2C(&lbl_803E774C) + 0x624;
	p26          = 0;
	p25          = 0;
	values.score = 0;
	values.time  = values.score;
	fn_8012C858(&lbl_1_data_3054, (const char*)&lbl_1_data_376C, opt[0x22]);

	x = lbl_1_rodata_ED0[self->stage];
	if (x < 0xe) {
		switch (self->charSel) {
			case 0:
				offset       = x * 0x50;
				values.score = (s8)base[offset + 0x1b];
				values.time  = (s8)base[offset + 0x27];
				rowOffset    = self->mission * 0xc;
				rowOffset    = offset + rowOffset;
				p26          = (DataRec*)(base + rowOffset + 0x10);
				break;
			case 1:
				offset       = x * 0x50;
				values.score = (s8)base[offset + 0x33];
				values.time  = (s8)base[offset + 0x37];
				if (self->mission == 0) {
					p26 = (DataRec*)(base + offset + 0x28);
				} else {
					p25 = (u32)(base + offset + 0x34);
				}
				break;
			case 2:
				offset       = x * 0x50;
				values.score = (s8)base[offset + 0x43];
				values.time  = (s8)base[offset + 0x47];
				if (self->mission == 0) {
					p26 = (DataRec*)(base + offset + 0x38);
				} else {
					p25 = (u32)(base + offset + 0x44);
				}
				break;
			case 3:
				offset       = x * 0x50;
				values.score = (s8)base[offset + 0x53];
				values.time  = (s8)base[offset + 0x5f];
				rowOffset    = self->mission * 0xc;
				rowOffset    = offset + rowOffset;
				p26          = (DataRec*)(base + rowOffset + 0x48);
				break;
		}
		if (self->unk_0x240 != 0) {
			if (lbl_1_rodata_C28[self->stage] != 0) {
				if (fn_80116A8C(p624, lbl_1_rodata_C80[self->stage]) != 0) {
					fn_1_88D0(self->unk_0x240, (self->stage + 5) / 3);
				} else {
					fn_1_88D0(self->unk_0x240, 0);
				}
			} else {
				fn_1_88C4(self->unk_0x240);
			}
		}
	} else {
		if (x == 0x15) {
			p25 = (u32) & ((ExtraData*)base)->rows[x - 0xe][0];
		} else {
			p25 = (u32) & ((ExtraData*)base)->rows[x - 0xe][self->charSel * 4];
		}
		values.score = (s8)((RowB*)p25)->b3;
		if (self->unk_0x240 != 0) {
			fn_1_88C4(self->unk_0x240);
		}
	}

	if (p26 != 0) {
		fn_8012C858(&lbl_1_data_3018[0], (const char*)&lbl_1_data_3774, p26->b8);
		fn_8012C858(&lbl_1_data_3018[1], (const char*)&lbl_1_data_3774, p26->b9);
		fn_8012C858(&lbl_1_data_3018[2], (const char*)&lbl_1_data_3774, p26->ba);
		fn_8012C858(&lbl_1_data_3018[3], (const char*)&lbl_1_data_376C, p26->h0);
		fn_8012C858(&lbl_1_data_3018[4], (const char*)&lbl_1_data_377C, p26->w4);
	} else if (p25 != 0) {
		fn_8012C858(&lbl_1_data_3018[0], (const char*)&lbl_1_data_3774, ((RowB*)p25)->b0);
		fn_8012C858(&lbl_1_data_3018[1], (const char*)&lbl_1_data_3774, ((RowB*)p25)->b1);
		fn_8012C858(&lbl_1_data_3018[2], (const char*)&lbl_1_data_3774, ((RowB*)p25)->b2);
		fn_8012C858(&lbl_1_data_3018[3], (const char*)&lbl_1_data_3784);
		fn_8012C858(&lbl_1_data_3018[4], (const char*)&lbl_1_data_3788);
	} else {
		fn_8012C858(&lbl_1_data_3018[0], (const char*)&lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[1], (const char*)&lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[2], (const char*)&lbl_1_data_2F18);
		fn_8012C858(&lbl_1_data_3018[3], (const char*)&lbl_1_data_2BC8);
		fn_8012C858(&lbl_1_data_3018[4], (const char*)&lbl_1_data_300C);
	}

	if (x < 0xe) {
		if (self->unk_0x23c != 0) {
			fn_1_8AA8(self->unk_0x23c);
		}
	} else {
		if (self->unk_0x23c != 0) {
			fn_1_8A9C(self->unk_0x23c);
		}
	}

	if (self->unk_0x238 != 0) {
		u8 f = 0;
		if (self->mission == 0 && self->unk_0x28 == 6) {
			f = 1;
		}
		fn_1_8A68(self->unk_0x238, values.score, f);
	}
	if (self->unk_0x23c != 0) {
		u8 f = 0;
		if (self->mission != 0 && self->unk_0x28 == 6) {
			f = 1;
		}
		fn_1_8A68(self->unk_0x23c, values.time, f);
	}
}

// GotoGame: push the run parameters into the config service and start.
void fn_1_9954(ADV_CHALLENGE* self)
{
	if (self->mission == 0) {
		fn_800A96B0(&lbl_80303EC8, 0x28, 0);
	} else {
		fn_800A96B0(&lbl_80303EC8, 0x28, 1);
	}
	fn_800191F8(&lbl_8029C310, 0, 0);
	fn_800A96B0(&lbl_80303EC8, 0x27, 0);
	fn_800A96B0(&lbl_80303EC8, 0x18, 0);
	fn_8001938C(&lbl_8029C310);
	fn_8001934C(&lbl_8029C310, 0, self->charSel);
	if (self->charSel == 3 && lbl_1_rodata_BD0[self->stage] == 8) {
		fn_8001936C(&lbl_8029C310, 0, 0x24);
	} else {
		fn_8001936C(&lbl_8029C310, 0, lbl_1_rodata_BD0[self->stage]);
	}
	if (lbl_1_rodata_BD0[self->stage] == 0x17) {
		fn_8001936C(&lbl_8029C310, 1, 0x18);
	}
	self->mode = 7;
	fn_800A96B0(&lbl_80303EC8, 0x2a, 6);
}

// GotoStageDown: step the selection arrow left.
void fn_1_9AC0(ADV_CHALLENGE* self)
{
	if (self->arrow != 0) {
		fn_1_8C28(self->arrow);
	}
}

// GotoStageUp: step the selection arrow right.
void fn_1_9AEC(ADV_CHALLENGE* self)
{
	if (self->arrow != 0) {
		fn_1_8C1C(self->arrow);
	}
}

// GotoCharUp: enter char-select and load its table row.
void fn_1_9B18(ADV_CHALLENGE* self)
{
	self->mode     = 1;
	self->unk_0x60 = 5;
	fn_1_7B24(&self->unk_0x64, &lbl_1_rodata_E20[self->stage]);
}

// GotoCharDown: enter char-select and load its table row.
void fn_1_9B64(ADV_CHALLENGE* self)
{
	self->mode     = 1;
	self->unk_0x60 = 5;
	fn_1_7B24(&self->unk_0x64, &lbl_1_rodata_D70[self->stage]);
}

// SetMission.
void fn_1_9BB0(ADV_CHALLENGE* self, s32 mission)
{
	self->mission = mission;
	fn_1_945C(self);
}

// SetStage.
void fn_1_9BD4(ADV_CHALLENGE* self, s32 stage)
{
	self->stage = stage;
	fn_1_945C(self);
}

// SetChar.
void fn_1_9BF8(ADV_CHALLENGE* self, s32 charSel)
{
	self->charSel = charSel;
	fn_1_922C(self);
	fn_1_945C(self);
}

// Walk the active node list and flag every node matching the key.
void fn_1_9C30(ADV_CHALLENGE* self)
{
	NodeList* list = (NodeList*)self->unk_0x230;
	Node* n;

	if (list == 0) {
		return;
	}
	n = list->head;
	while (n != 0) {
		if (fn_1_86B0(n, lbl_1_data_11A4) != 0) {
			fn_1_55A4(n, 1);
		}
		n = n->next;
	}
}

// Idle timer: after 0x12c frames, flag done and switch to mode 3.
void fn_1_9CA4(ADV_CHALLENGE* self)
{
	if (++self->timer > 0x12c) {
		self->unk_0x48 = 1;
		self->mode     = 3;
	}
}

// ExecSelect2: mission list (title panel active) menu row.
void fn_1_9CCC(ADV_CHALLENGE* self)
{
	s32 sel;

	if (self->unk_0x23c != 0 && fn_1_8A60(self->unk_0x23c) != 0) {
		sel = fn_1_11E48((u8*)self + 0x198, -1);
		if (sel != -1 && sel != self->mission) {
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
			}
			fn_1_9BB0(self, sel);
		}
	}
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			fn_800A8174(self, lbl_1_rodata_D68[1]);
			break;
		case 1:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			self->mode = 5;
			break;
		case 2:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			fn_1_9954(self);
			fn_80014154();
			break;
	}
}

// ExecSelect: stage/char navigation and confirm on the main select screen.
void fn_1_9E20(ADV_CHALLENGE* self)
{
	s32 done;
	s32 sel;

	done = 0;
	sel  = fn_1_11FFC((u8*)self + 0x80, -1);
	if (sel != -1 && sel != self->stage) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		if (sel == 0 && *(volatile s32*)&self->stage == 0x15) {
			fn_1_9B64(self);
		} else if (*(volatile s32*)&self->stage == 0 && sel == 0x15) {
			fn_1_9B18(self);
		} else if (sel < *(volatile s32*)&self->stage) {
			fn_1_9B18(self);
		} else {
			fn_1_9B64(self);
		}
		fn_1_9BD4(self, sel);
		done = 1;
	}
	sel = fn_1_11E48((u8*)self + 0x10c, -1);
	if (sel != -1 && sel != self->charSel) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		if (sel < self->charSel) {
			fn_1_9AC0(self);
		} else {
			fn_1_9AEC(self);
		}
		fn_1_9BF8(self, sel);
		done = 1;
	}
	if (done == 0) {
		switch (fn_800A9398(&lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				fn_800A8174(self, lbl_1_rodata_D68[0]);
				break;
			case 1:
				if (lbl_8042C388 != 0) {
					fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
				}
				self->unk_0x48 = 0;
				self->mode     = 2;
				break;
			case 2:
				if (self->sel[self->stage] != 0) {
					if (lbl_8042C388 != 0) {
						fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
					}
					self->mode = 6;
				} else {
					if (lbl_8042C388 != 0) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
		}
	}
}

// Handle a select-menu result, then clear the idle timer.
void fn_1_A098(ADV_CHALLENGE* self, s32 result)
{
	switch (result) {
		case 5:
			fn_1_945C(self);
			break;
		case 6:
			fn_1_945C(self);
			fn_1_9BB0(self, 0);
			break;
		case 7:
			fn_1_9C30(self);
			self->timer = 0;
			break;
	}
}

// Per-frame update: dispatch on the current sub-mode then run the base step.
void fn_1_A10C(ADV_CHALLENGE* self)
{
	switch (self->unk_0x28) {
		case 5:
			fn_1_9E20(self);
			break;
		case 6:
			fn_1_9CCC(self);
			break;
		case 7:
			fn_1_9CA4(self);
			break;
	}
	fn_1_905C(self);
}

// Deleting destructor: tear down the three embedded panels then the base.
ADV_CHALLENGE* fn_1_A178(ADV_CHALLENGE* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_3818;
		fn_1_120E0(self->obj_0x198, -1);
		fn_1_120E0(self->obj_0x10c, -1);
		fn_1_120E0(self->obj_0x80, -1);
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// Constructor: base init, build the three panels and five sub-objects, seed the
// stage/char/mission selection, then latch mode 1.
#pragma dont_inline reset
ADV_CHALLENGE* fn_1_A208(ADV_CHALLENGE* self, void* parent)
{
	s32 i;

	fn_800A8828(self, parent);
	self->vtable = &lbl_1_data_3818;
	fn_1_12124(&self->obj_0x80);
	fn_1_12124(&self->obj_0x10c);
	fn_1_12124(&self->obj_0x198);
	*(void**)self = lbl_1_data_36DC;
	self->size    = 0x2a0;

	new TAdvChallengeTitle((TObject*)self);
	self->arrow     = (TAdvChallengeSub*)new TAdvChallengeArrow((TObject*)self);
	self->unk_0x238 = (TAdvChallengeSub*)new TAdvChallengeEmblem((TObject*)self, 0);
	self->unk_0x23c = (TAdvChallengeSub*)new TAdvChallengeEmblem((TObject*)self, 1);
	self->unk_0x240 = new TAdvChallengeEme((TObject*)self);

	self->unk_0x40 = 0xf;
	self->unk_0x44 = 4;
	self->unk_0x48 = 1;
	self->unk_0x28 = 0;
	self->unk_0x38 = lbl_1_data_3060;
	self->stage    = 0;
	self->charSel  = 0;
	self->mission  = 0;

	void* node = advE3Rom_resume(sizeof(TObject));
	if (node != 0)
		node = __ct__7TObjectFP7TObject(node, self);
	self->unk_0x230 = node;

	fn_1_119D4(&self->obj_0x80);
	for (i = 0; i != 0x16; i++) {
		fn_1_120C4(&self->obj_0x80, i);
	}
	fn_1_119E0(&self->obj_0x80, 0);
	fn_1_9BD4(self, 0);

	fn_1_119D4(&self->obj_0x10c);
	fn_1_120C4(&self->obj_0x10c, 0);
	fn_1_120C4(&self->obj_0x10c, 1);
	fn_1_120C4(&self->obj_0x10c, 2);
	fn_1_120C4(&self->obj_0x10c, 3);
	fn_1_119E0(&self->obj_0x10c, 0);
	fn_1_9BF8(self, 0);

	fn_1_120C4(&self->obj_0x198, 0);
	fn_1_120C4(&self->obj_0x198, 1);
	fn_1_9BB0(self, 0);

	self->mode     = 1;
	self->unk_0x60 = 5;
	self->unk_0x64 = 0;
	self->unk_0x68 = 1;
	__ct__10DAnimClassFv(self, 4);
	return self;
}
#pragma dont_inline on

// Create: allocate and construct the ADV_CHALLENGE screen object.
void fn_1_A460(void* parent)
{
	ADV_CHALLENGE* self = (ADV_CHALLENGE*)advE3Rom_resume(0x2a0);
	if (self != 0) {
		fn_1_A208(self, parent);
	}
}

// Release + clear the shared sprite banks, then tear the sprite set down.
void fn_1_A4A0(void)
{
	s32 i;
	s32 j;

	{
		u32* p = lbl_1_bss_6F0;
		for (i = 0; i != 6; i++) {
			*p = 0;
			p++;
		}
	}
	for (i = 0; i != 22; i++) {
		for (j = 0; j != 2; j++) {
			if (lbl_1_bss_640[i][j] != 0) {
				fn_801A45A0(lbl_1_bss_590[i][j], lbl_1_bss_640[i][j]);
			}
			lbl_1_bss_590[i][j] = 0;
			lbl_1_bss_640[i][j] = 0;
		}
	}
	fn_1_64E0();
	fn_8012CA94(&lbl_1_data_32F4);
}

// Build the shared sprite banks from the resource set.
#pragma dont_inline reset
void fn_1_A578(void)
{
	s32 i;
	s32 j;
	u32 obj;

	fn_1_11750(2);
	fn_8012CB70(&lbl_1_data_32F4);
	fn_1_65BC();
	Vec3w tmp = lbl_1_rodata_F28;
	fn_800A8C9C(&lbl_80303EC8, &tmp);
	if (lbl_1_data_32F4.handle != 0) {
		for (i = 0; i != 22; i++) {
			for (j = 0; j != 2; j++) {
				lbl_1_bss_590[i][j] = fn_801A4BBC(lbl_1_data_32F4.handle, lbl_1_data_35CC[i][j]);
				if (lbl_1_bss_590[i][j] != 0) {
					lbl_1_bss_640[i][j] = *(u32*)lbl_1_bss_590[i][j];
				}
			}
		}
		for (i = 0; i != 6; i++) {
			obj = fn_801A4BBC(lbl_1_data_32F4.handle, lbl_1_data_36B4[i]);
			if (obj != 0) {
				lbl_1_bss_6F0[i] = *(u32*)obj;
			}
		}
	}
}
#pragma dont_inline on

// Empty virtual (vtable slot).
void fn_1_A6C4(void) { }

// Virtual returning a constant.
f32 fn_1_A6C8(void)
{
	return lbl_1_rodata_102C;
}

// Empty virtual (vtable slot).
void fn_1_A6D8(void) { }

// Count decoded lines in a u16 string (newline-delimited, +1).
s32 fn_1_A6DC(void* self, u16* str)
{
	s32 n;
	s32 c;

	if (str == 0) {
		return 1;
	}
	n = 1;
	while ((c = *str) != 0) {
		if (c == 0xa) {
			n++;
		}
		str++;
	}
	return n;
}

// Point the arrow right/left: defined at file end so the moved delegators
// fn_1_9AEC / fn_1_9AC0 keep out-of-line calls to them.

// Return whether the global flag byte is clear.
bool fn_1_A714(void)
{
	return lbl_8042C0C0 == 0;
}

// Enable/disable the shared sprite bank.
void fn_1_A72C(void* self, s32 flag)
{
	if (flag == 0) {
		fn_800A8C38(&lbl_80303EC8);
	} else {
		fn_800A8C20(&lbl_80303EC8);
	}
}

// Query region/config field 0x14.
s32 fn_1_A76C(void* self)
{
	return fn_1_12A0(lbl_8042C180, 0x14);
}

// Push config field 0x14 and cache it back.
void fn_1_A79C(void* self, s32 arg)
{
	AdvOpt* p;

	fn_800A96B0(&lbl_80303EC8, 0x14, arg);
	p = fn_80116D2C(&lbl_803E774C);
	if (p != 0) {
		p->unk_0x1d = fn_1_12A0(lbl_8042C180, 0x14);
	}
}

// Query config field 0x13, clamping toward the neighbouring option.
s32 fn_1_A808(void* self)
{
	s32 x = fn_1_12A0(lbl_8042C180, 0x13);
	switch (x) {
		case 4:
			x -= 1;
			break;
		case 3:
			x += 1;
			break;
	}
	return x;
}

// Remap the difficulty index (swapping 3<->4) and push config field 0x13.
void fn_1_A85C(void* self, s32 arg)
{
	switch (arg) {
		case 0:
			arg = 0;
			break;
		case 1:
			arg = 1;
			break;
		case 2:
			arg = 2;
			break;
		case 3:
			arg = 4;
			break;
		case 4:
			arg = 3;
			break;
		case 5:
			arg = 5;
			break;
		case 6:
			arg = 6;
			break;
	}
	fn_800A96B0(&lbl_80303EC8, 0x13, arg);
	{
		AdvOpt* p = fn_80116D2C(&lbl_803E774C);
		if (p != 0) {
			p->unk_0x1c = fn_1_12A0(lbl_8042C180, 0x13);
		}
	}
}

// Return whether config field 0x15 is clear.
s32 fn_1_A91C(void* self)
{
	return (u32)__cntlzw(fn_1_12A0(lbl_8042C180, 0x15)) >> 5;
}

// Toggle config field 0x15 and cache it back.
void fn_1_A954(void* self, s32 flag)
{
	AdvOpt* p;

	if (flag == 0) {
		fn_800A96B0(&lbl_80303EC8, 0x15, 1);
	} else {
		fn_800A96B0(&lbl_80303EC8, 0x15, 0);
	}
	p = fn_80116D2C(&lbl_803E774C);
	if (p != 0) {
		p->unk_0x23 = fn_1_12A0(lbl_8042C180, 0x15);
	}
}

// Query region/config field 0x12.
s32 fn_1_A9E0(void* self)
{
	return fn_1_12A0(lbl_8042C180, 0x12);
}

// Push config field 0x12, cache it, apply the widescreen toggle.
void fn_1_AA10(void* self, s32 arg)
{
	AdvOpt* p;

	fn_800A96B0(&lbl_80303EC8, 0x12, arg);
	p = fn_80116D2C(&lbl_803E774C);
	if (p != 0) {
		p->unk_0x38 = (s8)fn_1_12A0(lbl_8042C180, 0x12);
	}
	if (fn_1_12A0(lbl_8042C180, 0x12) == 1) {
		fn_801D5B9C(0);
	} else {
		fn_801D5B9C(1);
	}
	fn_800B41A0(arg);
}

// Free the held object at 0x3fc.
void fn_1_AAC0(GdispChallenge* self)
{
	if (self->unk_0x3fc != 0) {
		advE3Rom_setFlag(self->unk_0x3fc);
		self->unk_0x3fc = 0;
	}
}

// Advance the challenge display: pick the next panel by phase and sub-state.
void fn_1_AB00(GdispChallenge* self)
{
	s32 sel;

	if (self->unk_0x3f8 == 0) {
		return;
	}
	sel = fn_8012491C(self->unk_0x3f8);
	switch (fn_801248F8(self->unk_0x3f8)) {
		case 3:
			fn_1_B218(self, fn_8012ECA8(0, 0x24), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0,
			    0xc, 0xf, 0, 0);
			break;
		case 4:
			fn_1_B218(self, fn_8012ECA8(0, 0x26), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0,
			    0xc, 0xf, 0, 0);
			break;
		case 2:
			fn_1_B218(self, fn_8012ECA8(0, 0x30), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0,
			    0xc, 0xf, 0, 0);
			break;
		case 0:
		default:
			switch (sel) {
				case 0:
				case 1:
					break;
				case 9:
				case 0xb:
					fn_1_B218(self, fn_8012ECA8(0, 0x40), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
				case 6:
					fn_1_B218(self, fn_8012ECA8(0, 0x15), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), fn_8012ECA8(0, 0x54), 0xc, 0xf, 0x10, 1);
					break;
				case 0xc:
					fn_1_B218(self, fn_8012ECA8(0, 0x19), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), fn_8012ECA8(0, 0x54), 0xc, 0xf, 0x10, 1);
					break;
				case 5:
					fn_1_B218(self, fn_8012ECA8(0, 0x21), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
				case 3:
					fn_1_B218(self, fn_8012ECA8(0, 0x24), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
				case 4:
					fn_1_B218(self, fn_8012ECA8(0, 0x26), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
				case 7:
					fn_1_B218(self, fn_8012ECA8(0, 0x28), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
				case 8: {
					s32 n = fn_80116B68(&lbl_803E774C);
					char buf[0x400];
					fn_8012EC18(buf, fn_8012ECA8(0, 0x2b), n + 1);
					fn_1_B218(self, buf, fn_8012ECA8(0, 0x56), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0x11, 0xc, 0xf, 1);
					break;
				}
				case 0xa:
					break;
				case 2:
					fn_1_B218(self, fn_8012ECA8(0, 0x30), fn_8012ECA8(0, 0x50),
					    fn_8012ECA8(0, 0x51), 0, 0xc, 0xf, 0, 0);
					break;
			}
			break;
	}
}

// Load a selection-table row into the live position fields.
void fn_1_B03C(ADV_CHALLENGE* self, TabEntry* table, s32 idx)
{
	TabEntry* e    = &table[idx];
	self->unk_0x70 = e->a;
	self->unk_0x74 = e->b;
	self->unk_0x34 = lbl_1_data_3AB4.pos[e->a].y;
}

// Build a display request for a plain object (flag = 1).
void fn_1_B078(GdispChallenge* self, void* arg)
{
	DispReq req;
	s32 n;

	fn_1_152C0(&req);
	req.obj  = arg;
	req.m4   = 0;
	req.m8   = 0;
	req.mc   = 0;
	req.f14  = lbl_1_rodata_1030;
	req.f18  = lbl_1_rodata_1034;
	req.f1c  = lbl_1_rodata_102C;
	req.f20  = lbl_1_rodata_1038;
	req.f24  = lbl_1_rodata_103C;
	req.flag = 1;
	n        = fn_1_A6DC(self, (u16*)arg);
	if (n >= 6) {
		f32 p;
		p       = lbl_1_rodata_1040 * (f32)(n - 5);
		req.f18 = req.f18 - p;
		p       = lbl_1_rodata_1044 * (f32)(n - 5);
		req.f24 = req.f24 + p;
	}
	self->unk_0x3fc = fn_1_150AC(self, &req);
}

// Dispatch on the current phase state.
void fn_1_B1B4(GdispChallenge* self)
{
	switch (fn_801248F8(self->unk_0x3f8)) {
		case 0:
			fn_1_B674(self);
			break;
		case 2:
		case 3:
		case 4:
		default:
			fn_1_AB00(self);
			break;
	}
}

// Build a display request for a ranked selection (offset by rank/flags).
void fn_1_B218(GdispChallenge* self, void* a, void* b, void* c, void* d, s32 e, s32 f, s32 g, s32 h)
{
	DispReq req;
	s32 n;

	fn_1_152C0(&req);
	req.obj  = a;
	req.m4   = (u32)b;
	req.m8   = (u32)c;
	req.mc   = (u32)d;
	req.flag = 0;
	req.f14  = lbl_1_rodata_1030;
	req.f18  = lbl_1_rodata_1034;
	req.f1c  = lbl_1_rodata_102C;
	req.f20  = lbl_1_rodata_1038;
	req.f24  = lbl_1_rodata_103C;
	if (req.m4 != 0) {
		req.f18 = lbl_1_rodata_1034 - lbl_1_rodata_1050;
	}
	if (req.m8 != 0) {
		req.f18 = req.f18 - lbl_1_rodata_1054;
	}
	if (req.mc != 0) {
		req.f18 = req.f18 - lbl_1_rodata_1054;
	}
	n = fn_1_A6DC(self, (u16*)a);
	if (n >= 6) {
		f32 p;
		p       = lbl_1_rodata_1058 * (f32)(n - 5);
		req.f18 = req.f18 - p;
		p       = lbl_1_rodata_105C * (f32)(n - 5);
		req.f24 = req.f24 + p;
	}
	fn_1_AAC0(self);
	self->unk_0x3fc = fn_1_150AC(self, &req);
	self->unk_0x3e4 = e;
	self->unk_0x3e8 = f;
	self->unk_0x3ec = g;
	if (h == 0) {
		self->unk_0x2c = 0xd;
	} else {
		self->unk_0x2c = 0xe;
	}
}

// Poll phase (mission list): latch ready, then commit or advance.
void fn_1_B400(GdispChallenge* self)
{
	if (self->unk_0x80 == 0) {
		if (fn_8012554C(self->unk_0x3f8) != 0) {
			self->unk_0x80 = 1;
		}
	} else if (self->unk_0x3fc == 0 || fn_1_146C0(self->unk_0x3fc) == 1) {
		if (fn_80124924(self->unk_0x3f8) == 0) {
			fn_1_AAC0(self);
			switch (fn_8012491C(self->unk_0x3f8)) {
				case 0: {
					s32 n = fn_80116B68(&lbl_803E774C);
					char buf[0x400];
					fn_8012EC18(buf, fn_8012ECA8(0, 0x11), n + 1);
					fn_1_B218(self, buf, 0, 0, 0, 0xc, 0, 0, 0);
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 0xa:
				case 0xc:
				default:
					fn_1_AB00(self);
					break;
			}
		}
	}
}

// Commit the current selection into a new held object, or advance.
void fn_1_B518(GdispChallenge* self)
{
	if (self->unk_0x3fc == 0 || fn_1_146C0(self->unk_0x3fc) == 1) {
		if (fn_80124924(self->unk_0x3f8) == 0) {
			fn_1_AAC0(self);
			switch (fn_8012491C(self->unk_0x3f8)) {
				case 0:
					fn_1_B218(self, fn_8012ECA8(0, 0x1d), 0, 0, 0, 0xc, 0, 0, 0);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 0xa:
				case 0xc:
				default:
					fn_1_AB00(self);
					break;
			}
		}
	}
}

// SetMode variant: snap 0x2c and free, with an extra config poke on mode 2.
void fn_1_B5DC(GdispChallenge* self)
{
	if (self->unk_0x3fc != 0) {
		switch (fn_1_146C0(self->unk_0x3fc)) {
			case 1:
				self->unk_0x2c = 0xc;
				fn_1_AAC0(self);
				break;
			case 2:
				self->unk_0x2c = 2;
				fn_80116B60(&lbl_803E774C, -2);
				fn_1_AAC0(self);
				break;
		}
	} else {
		self->unk_0x2c = 0xc;
		fn_1_AAC0(self);
	}
}

// SetMode: snap 0x2c to the mode-specific slot then free the held object.
void fn_1_B674(GdispChallenge* self)
{
	if (self->unk_0x3fc != 0) {
		switch (fn_1_146C0(self->unk_0x3fc)) {
			case 1:
				if (self->unk_0x3e4 != 0) {
					self->unk_0x2c = self->unk_0x3e4;
					fn_1_AAC0(self);
				}
				break;
			case 2:
				if (self->unk_0x3e8 != 0) {
					self->unk_0x2c = self->unk_0x3e8;
					fn_1_AAC0(self);
				}
				break;
			case 3:
				if (self->unk_0x3ec != 0) {
					self->unk_0x2c = self->unk_0x3ec;
					fn_1_AAC0(self);
				}
				break;
		}
	} else {
		self->unk_0x2c = self->unk_0x3e8;
		fn_1_AAC0(self);
	}
}

// Poll phase: latch ready, else commit the selection on a valid state.
void fn_1_B734(GdispChallenge* self)
{
	if (self->unk_0x80 == 0) {
		if (fn_8012586C(self->unk_0x3f8) != 0) {
			self->unk_0x80 = 1;
		}
	} else if (self->unk_0x3fc == 0 || fn_1_146C0(self->unk_0x3fc) == 1) {
		if (fn_80124924(self->unk_0x3f8) == 0) {
			fn_1_AAC0(self);
			switch (fn_8012491C(self->unk_0x3f8)) {
				case 0:
					self->unk_0x48 = 1;
					fn_1_B218(self, fn_8012ECA8(0, 0x3c), 0, 0, 0, 2, 0, 0, 0);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 0xa:
				case 0xc:
				default:
					fn_1_AB00(self);
					break;
			}
		}
	}
}

// ExecSelect: stage-select row with scrolling highlight.
void fn_1_B828(ADV_CHALLENGE* self)
{
	s32 sel;

	if (self->unk_0x400 != 0) {
		if (self->unk_0x404 < self->unk_0x400->pos[1].y) {
			self->unk_0x404 = self->unk_0x404 + lbl_1_rodata_1060;
		}
	}
	sel = fn_1_11E48((u8*)self + 0x358, -1);
	if (sel != -1 && self->unk_0x98 != sel) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		self->unk_0x98 = sel;
		switch (sel) {
			case 0:
				self->unk_0x34 = lbl_1_rodata_1064;
				break;
			default:
				self->unk_0x34 = lbl_1_rodata_102C;
				break;
		}
	}
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			fn_800A8174(self, 0x19d);
			break;
		case 1:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			self->mode      = 5;
			self->unk_0x38  = &lbl_1_data_3AB4;
			self->unk_0x400 = 0;
			break;
		case 2:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			fn_1_A72C(self, self->unk_0x98);
			self->mode      = 6;
			self->unk_0x38  = &lbl_1_data_3AB4;
			self->unk_0x400 = 0;
			break;
	}
}

// ExecSelect: character-select row (two sub-panels keyed off unk_0x408).
void fn_1_B9E8(ADV_CHALLENGE* self)
{
	s32 sel;

	if (self->unk_0x408 == 0) {
		sel = fn_1_11FFC((u8*)self + 0x240, -1);
		if (sel != -1 && self->unk_0x90 != sel) {
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
			}
			self->unk_0x90 = sel;
			fn_1_B03C(self, lbl_1_rodata_FC8, sel);
		}
	} else {
		sel = fn_1_11FFC((u8*)self + 0x1b4, -1);
		if (sel != -1 && self->unk_0x8c != sel) {
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
			}
			self->unk_0x8c = sel;
			fn_1_B03C(self, lbl_1_rodata_FD8, sel);
		}
	}
	fn_800A8120(self);
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			if (self->unk_0x408 == 0) {
				fn_800A8174(self, 0x18f);
			} else {
				fn_800A8174(self, 0x190);
			}
			break;
		case 1:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			if (self->unk_0x408 == 0) {
				self->unk_0x90 = fn_1_A76C(self);
				self->unk_0x8c = fn_1_A808(self);
				self->mode     = 1;
				self->unk_0x60 = 6;
				self->unk_0x64 = 0x24;
				self->unk_0x68 = 0x25;
			} else {
				self->unk_0x90 = fn_1_A76C(self);
				self->unk_0x8c = fn_1_A808(self);
				self->mode     = 1;
				self->unk_0x60 = 6;
				self->unk_0x64 = 0x20;
				self->unk_0x68 = 0x21;
			}
			break;
		case 2:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			if (self->unk_0x408 == 0) {
				self->unk_0x408 = 1;
				fn_1_119E0((u8*)self + 0x1b4, self->unk_0x8c);
				fn_1_B03C(self, lbl_1_rodata_FD8, self->unk_0x8c);
			} else {
				fn_1_A79C(self, self->unk_0x90);
				fn_1_A85C(self, self->unk_0x8c);
				self->mode     = 2;
				self->unk_0x44 = 7;
				fn_800A9224(&lbl_80303EC8);
			}
			break;
	}
}

// ExecSelect: widescreen-toggle menu row.
void fn_1_BC98(ADV_CHALLENGE* self)
{
	s32 sel;

	sel = fn_1_11FFC((u8*)self + 0x128, -1);
	if (sel != -1 && self->unk_0x88 != sel) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		self->unk_0x88 = sel;
		fn_1_B03C(self, lbl_1_rodata_FB0, sel);
	}
	fn_800A8120(self);
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			fn_800A8174(self, 0x18e);
			break;
		case 1:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			self->unk_0x88 = fn_1_A91C(self);
			self->mode     = 1;
			self->unk_0x60 = 6;
			self->unk_0x64 = 0x24;
			self->unk_0x68 = 0x25;
			break;
		case 2:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			fn_1_A954(self, self->unk_0x88);
			self->mode = 6;
			break;
	}
}

// ExecSelect: progressive-scan menu row.
void fn_1_BE0C(ADV_CHALLENGE* self)
{
	s32 sel;

	sel = fn_1_11FFC((u8*)self + 0x9c, -1);
	if (sel != -1 && self->unk_0x84 != sel) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		self->unk_0x84 = sel;
		fn_1_B03C(self, lbl_1_rodata_F90, sel);
	}
	fn_800A8120(self);
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			fn_800A8174(self, 0x18d);
			break;
		case 1:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			self->unk_0x84 = fn_1_A9E0(self);
			self->mode     = 1;
			self->unk_0x60 = 6;
			self->unk_0x64 = 0xe;
			self->unk_0x68 = 0xf;
			break;
		case 2:
			fn_1_AA10(self, self->unk_0x84);
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			self->mode = 6;
			break;
	}
}

// ExecSelect: mission-select row.
void fn_1_BF80(ADV_CHALLENGE* self)
{
	s32 sel;

	fn_800A8120(self);
	sel = fn_1_11AA8((u8*)self + 0x2cc, 2, 3, -1);
	if (sel != -1 && self->unk_0x94 != sel) {
		if (lbl_8042C388 != 0) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		self->unk_0x94 = sel;
		fn_1_B03C(self, lbl_1_rodata_F48, sel);
	}
	switch (fn_800A9398(&lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			fn_800A8174(self, lbl_1_rodata_1018[self->unk_0x94]);
			break;
		case 1: {
			s32 t = fn_80116B68(&lbl_803E774C);
			if (t >= 0 && t < 0x63) {
				self->mode = 0xc;
			} else {
				self->unk_0x48 = 1;
				self->mode     = 2;
			}
			break;
		}
		case 2:
			if (lbl_8042C388 != 0) {
				fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
			}
			switch (self->unk_0x94) {
				case 0:
				case 1:
				case 3:
					self->mode     = 1;
					self->unk_0x60 = self->unk_0x94 + 7;
					self->unk_0x6c = 1;
					fn_1_7B24(&self->unk_0x64, &lbl_1_rodata_F70[self->unk_0x94]);
					break;
				case 2:
					self->mode     = 1;
					self->unk_0x60 = 2;
					self->unk_0x64 = 0x22;
					self->unk_0x68 = 0x23;
					self->unk_0x44 = 8;
					break;
				case 4:
					self->mode     = 1;
					self->unk_0x60 = 0xb;
					self->unk_0x64 = 0x22;
					self->unk_0x68 = 0x23;
					break;
				case 5: {
					s32 t = fn_80116B68(&lbl_803E774C);
					if (t >= 0 && t < 0x63) {
						self->mode = 0xc;
					} else {
						self->unk_0x48 = 1;
						self->mode     = 2;
					}
					break;
				}
			}
			break;
	}
}

// Enter mode 1, selecting sprite bank 6 with options 0 and 7.
void fn_1_C1CC(ADV_CHALLENGE* self)
{
	self->mode     = 1;
	self->unk_0x60 = 6;
	self->unk_0x64 = 0;
	self->unk_0x68 = 7;
}
#pragma dont_inline reset
}
