#include "types.h"

// advertiseD module (REL, module 1) - the ADV_STORY story-select task class and
// its embedded TAdvStoryTitle title sub-object. .text 0x070B0-0x0880C (31
// functions). Class name string "ADV_STORY" @data 0x1DD8, "TAdvStoryTitle"
// @data 0x2974. Two vtables: lbl_1_data_2988 (TAdvStoryTitle),
// lbl_1_data_29BC (ADV_STORY). Loads "adv_story.one".
//
// This TU's .data also holds the module-level manager/dispatch tables
// lbl_1_data_2A68 (per-screen title/sub triples) and lbl_1_data_2A08. The REL
// glue at 0x880C and two-function tail at 0x88C4 are separate link units.
//
// PS2 reference: ADV_STORY + TAdvStoryTitle in advertise.cpp. GC bytes are
// ground truth; names below inspired by the PS2 symbols, not proven.
//
// Object is NonMatching while the TU is carved; do not flip to Matching here.

extern "C" {

// 8-byte {id, float} table entry.
struct Ent8 {
	s32 a;
	f32 b;
};

// 8-byte {id, id} sound-effect pair.
struct Snd {
	s32 a;
	s32 b;
};

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

enum StoryIndex { STORY_INDEX_ZERO = 0 };

struct PlayerTransform {
	s32 index;
	Vec3 translation;
	s32 type;
	f32 angle;
};

// Per-page selector list object (0x8c bytes), managed by fn_1_11xxx helpers.
struct Sel {
	u8 pad[0x8c];
};

// ---- TAdvStoryTitle: small embedded title object -----------------------
struct Title {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad_04[0x18 - 0x04];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 pad_1C[0x1E - 0x1C];
	/* 0x1E */ u16 unk_1E;
	/* 0x20 */ u8 pad_20[0x28 - 0x20];
	/* 0x28 */ void* window; // 0x28
	/* 0x2C */ f32 timer;    // 0x2C
	/* 0x30 */ u8 pad_30[0x34 - 0x30];
	/* 0x34 */ s32 flag_34; // 0x34
};

// ---- ADV_STORY: story-select task object -------------------------------
struct AStory {
	/* 0x000 */ void* name;
	/* 0x004 */ u8 pad_004[0x18 - 0x04];
	/* 0x018 */ void* vtable;
	/* 0x01C */ u8 pad_01C[0x1E - 0x1C];
	/* 0x01E */ u16 unk_1E;
	/* 0x020 */ u8 pad_020[0x28 - 0x20];
	/* 0x028 */ s32 mode;  // 0x28
	/* 0x02C */ s32 state; // 0x2C
	/* 0x030 */ u8 pad_030[0x34 - 0x30];
	/* 0x034 */ f32 unk_34;     // 0x34
	/* 0x038 */ void* timeline; // 0x38
	/* 0x03C */ u8 pad_03C[0x40 - 0x3C];
	/* 0x040 */ s32 unk_40;
	/* 0x044 */ s32 unk_44;
	/* 0x048 */ s32 unk_48;
	/* 0x04C */ u8 pad_04C[0x60 - 0x4C];
	/* 0x060 */ s32 unk_60;
	/* 0x064 */ Snd snd_64; // 8-byte pair (fn_1_7B24 dest)
	/* 0x06C */ u8 pad_06C[0x70 - 0x6C];
	/* 0x070 */ s32 unk_70;
	/* 0x074 */ s32 unk_74;
	/* 0x078 */ u8 pad_078[0x80 - 0x78];
	/* 0x080 */ Sel pageSel;      // 0x80 (0x8c)
	/* 0x10C */ s32 curPage;      // 0x10C
	/* 0x110 */ s32 sel110[4];    // 0x110
	/* 0x120 */ Sel itemSel[4];   // 0x120 (4 * 0x8c)
	/* 0x350 */ void* players[4]; // 0x350
	/* 0x360 */ s32 counter;      // 0x360
};

// ---- module data (dtk labels; paired by name) --------------------------
extern void* lbl_1_data_2988[]; // TAdvStoryTitle vtable
extern void* lbl_1_data_29BC[]; // ADV_STORY vtable
extern void* lbl_1_data_2984;   // -> "TAdvStoryTitle"
extern void* lbl_1_data_1DE4;   // -> "ADV_STORY"
extern u8 lbl_1_data_2824[];    // shared config/base object
extern u8 lbl_1_data_27E8[];    // scratch string buffers
extern u8 lbl_1_data_29B4[];    // format string
extern Ent8* lbl_1_data_293C[]; // per-page transition table A
extern Ent8* lbl_1_data_292C[]; // per-page transition table B
extern s32 lbl_1_data_294C[];   // item-kind table
extern void* lbl_1_data_11A4[]; // node id list
extern u8 lbl_1_data_2914[];    // .one load descriptor
extern u8 lbl_1_data_2968[];    // callback descriptor
extern u8 lbl_1_data_29F8[];    // controller descriptor
extern void* lbl_1_data_2A08;   // module dispatch table
extern void* lbl_1_data_2A68;   // module per-screen triples
extern void* lbl_1_data_2BB8;   // module table
extern void* lbl_1_data_29F0;   // module init descriptor

extern void* lbl_8042C388; // debug event flag word
extern u8 lbl_8042C7E0[];  // story render/scene object
extern u8 lbl_803E774C[];  // sound/anim controller object
extern u8 lbl_80303EC8[];  // save/card controller object
extern u8 lbl_8029C310[];  // scratch object
extern u8 lbl_8042C1C0[];  // module registration slot

extern const f32 lbl_1_rodata_BC4;
extern const f32 lbl_1_rodata_BC8;
// 0x18-stride table: {range lo/hi, then two 8-byte sound-effect pairs}.
struct R750 {
	s32 lo;    // 0x00
	s32 hi;    // 0x04
	Snd snd08; // 0x08
	Snd snd10; // 0x10
};
extern R750 lbl_1_rodata_750[];
extern Vec3 lbl_1_rodata_7B0[];
extern f32 lbl_1_rodata_840[];
extern u8 lbl_1_rodata_930[];
extern f32 lbl_1_rodata_9C0[];
extern u8 lbl_1_rodata_870[];
extern f32 lbl_1_rodata_900[];
extern void* lbl_1_rodata_9F0[];
extern const double lbl_1_rodata_F38;

// ---- sibling-TU (adv_e3rom.cpp) shared base methods --------------------
void advE3Rom_pause(void*);
void* advE3Rom_resume(s32);

// ---- externals in earlier TUs of this module ---------------------------
void fn_1_5844(void*, f32);
void fn_1_58B4(void*, void*);
Vec3* fn_1_5994(Vec3*, const Vec3*);
void fn_1_55A4(void*, int);
void fn_1_63A8(void*, void*);
void fn_1_6ABC(void*);
void fn_1_64E0(void);
void fn_1_65BC(void);
void fn_1_69AC(void);
void fn_1_6A0C(void);
void fn_1_10F40(void*, void*);
void fn_1_10FB0(void);
void fn_1_10FD8(void);
void fn_1_11000(void);
void fn_1_118E4(void*);
void fn_1_11940(void);
void fn_1_11994(void);
void fn_1_119D4(void*);
void fn_1_119E0(void*, int);
int fn_1_11E48(void*, int);
int fn_1_11FFC(void*, int);
void fn_1_11750(int);
void fn_1_120C4(Sel*, int);
void fn_1_120E0(void*, int);
void fn_1_12124(void*);
void fn_1_15268(void);
void fn_1_15294(void);

// ---- external functions (DOL) ------------------------------------------
void __dt__7TObjectFv(void*, int);
void* __ct__7TObjectFP7TObject(void*, void*);
void* fn_800191F8(void*, int, int);
void fn_8001938C(void*);
void fn_8001867C(void*);
void fn_800421B4(void*, void*);
void fn_800A8120(void*);
void fn_800A8174(void*, int);
void fn_800A8620(void*, int);
void __ct__10DAnimClassFv(void*, int);
void __ct__10EasySelectFP7TObject(void*);
void fn_800A8C9C(void*, void*);
void fn_800A9418(void*, void*);
void fn_800A9444(void*);
void fn_800A94C4(void*);
void fn_800A94E8(void*);
void fn_800A953C(void*);
void fn_800A9584(void*);
void fn_800A96B0(void*, int, int);
int fn_800A9398(void*, int);
void fn_800B52E8(void*, int, int, int);
int fn_80116AE4(void*);
void* fn_80116D2C(void*);
void fn_8011F13C(void);
void fn_8011F3AC(void);
void fn_8012C858(void*, void*, ...);
void fn_8012CA94(void*);
void fn_8012CB70(void*);
void fn_8012CC20(void*);
void fn_8012CEF0(void*, f32);
void fn_80126254(void);
void fn_801262DC(void);
int fn_80138994(void*, int, int);
void fn_801384F0(void*, int);
void fn_80138A9C(void*);
void fn_80138C78(void*, int);
void fn_8013BBE0(void);
void fn_8013BC78(void);
void fn_80014154(void);
void* fn_8016E810(void*);
void fn_8016E868(void*, void*);
void fn_80196D00(void);
void __destroy_arr(void*, void*, int, int);
void __construct_array(void*, void*, void*, int, int);

// forward decls (internal)
void fn_1_70B0(Title* self);
void fn_1_70DC(Title* self);
Title* fn_1_713C(Title* self, s16 flag);
Title* fn_1_71A4(Title* self, void* parent);
void fn_1_7218(AStory* self);
int fn_1_7314(AStory* self, int chapter);
int fn_1_73D8(AStory* self);
void fn_1_74A0(AStory* self, int keep);
void fn_1_7524(AStory* self);
void fn_1_7578(AStory* self);
void fn_1_7644(AStory* self);
void fn_1_76D4(AStory* self, int mode);
void fn_1_782C(AStory* self);
void fn_1_7854(AStory* self, int page);
void fn_1_787C(AStory* self);
void fn_1_78A4(AStory* self);
void fn_1_7B24(void* dst, const void* src);
void fn_1_7B38(AStory* self);
void fn_1_7DE8(AStory* self);
void fn_1_8010(AStory* self);
void fn_1_8030(AStory* self, int mode);
void fn_1_810C(AStory* self);
AStory* fn_1_8190(AStory* self, s16 flag);
AStory* fn_1_8434(AStory* self, void* parent);
void fn_1_85FC(AStory* self);
int fn_1_86B0(s32* p, s32 v);
void fn_1_8740(void);
void fn_1_88C4(Title* self);
void fn_1_88D0(Title* self, s32 ticks);

// =======================================================================
#pragma dont_inline on
// 0x70B0 - TAdvStoryTitle: tear down the title window if open.
void fn_1_70B0(Title* self)
{
	if (self->window) {
		fn_8012CC20(self->window);
	}
}

// 0x70DC - TAdvStoryTitle::Exec: advance the fade timer and drive the window.
void fn_1_70DC(Title* self)
{
	if (self->window) {
		if (self->timer < *(f32*)((char*)*(void**)((char*)self->window + 8) + 0xc)) {
			self->timer += lbl_1_rodata_BC4;
		}
		fn_8012CEF0(self->window, self->timer);
	}
}

// 0x713C - TAdvStoryTitle::__dt.
Title* fn_1_713C(Title* self, s16 flag)
{
	if (self) {
		self->vtable = lbl_1_data_2988;
		__dt__7TObjectFv(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// 0x71A4 - TAdvStoryTitle::__ct.
Title* fn_1_71A4(Title* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	self->vtable = lbl_1_data_2988;
	self->name   = lbl_1_data_2984;
	self->unk_1E = 0x34;
	self->window = lbl_1_data_2824 + 0x68;
	self->timer  = lbl_1_rodata_BC8;
	return self;
}

// 0x7218 - build the four story-progress label strings.
void fn_1_7218(AStory* self)
{
	fn_8012C858(lbl_1_data_27E8 + 0x00, lbl_1_data_29B4, fn_1_7314(self, 0));
	fn_8012C858(lbl_1_data_27E8 + 0x0c, lbl_1_data_29B4, fn_1_7314(self, 1));
	fn_8012C858(lbl_1_data_27E8 + 0x18, lbl_1_data_29B4, fn_1_7314(self, 2));
	fn_8012C858(lbl_1_data_27E8 + 0x24, lbl_1_data_29B4, fn_1_7314(self, 3));
	fn_8012C858(lbl_1_data_27E8 + 0x30, lbl_1_data_29B4, fn_1_7314(self, 4));
}

// 0x7314 - GetStoryProgress: read the save slot for a chapter.
int fn_1_7314(AStory* self, int chapter)
{
	(void)self;
	switch (chapter) {
		case 0:
			return fn_80138994(lbl_8042C7E0, 0, 0);
		case 1:
			return fn_80138994(lbl_8042C7E0, 1, 0);
		case 2:
			return fn_80138994(lbl_8042C7E0, 2, 0);
		case 3:
			return fn_80138994(lbl_8042C7E0, 3, 0);
		case 4:
			return fn_80138994(lbl_8042C7E0, 4, 0);
	}
	return 0;
}

// 0x73D8 - IsLastEnable: true once every chapter is complete.
int fn_1_73D8(AStory* self)
{
	int c0 = fn_1_7314(self, 0);
	int c1 = fn_1_7314(self, 1);
	int c2 = fn_1_7314(self, 2);
	int c3 = fn_1_7314(self, 3);
	if (c0 == 100 && c1 == 100 && c2 == 100 && c3 == 100) {
		if (fn_80116AE4((char*)fn_80116D2C(lbl_803E774C) + 0x624) == 7) {
			return 2;
		}
		return 1;
	}
	return 0;
}

// 0x74A0 - HidePlayer: hide every loaded player except the given index.
void fn_1_74A0(AStory* self, int keep)
{
	AStory* p;
	int i;
	for (i = 0, p = self; i != 4; p = (AStory*)((char*)p + 4), i++) {
		if (p->players[0]) {
			if (i != keep) {
				fn_8001867C(p->players[0]);
			} else {
				fn_1_76D4(self, 2);
			}
		}
	}
}

// 0x7524 - ShowPlayer: reset every loaded player object.
void fn_1_7524(AStory* self)
{
	AStory* p;
	int i;
	for (i = 0, p = self; i != 4; p = (AStory*)((char*)p + 4), i++) {
		if (p->players[0]) {
			fn_8001867C(p->players[0]);
		}
	}
}

// 0x7578 - TranslatePlayer: re-place each player at its 3 preset transforms.
void fn_1_7578(AStory* self)
{
	int idx = 0;
	int i   = 0;
	for (; i != 4; i++) {
		AStory* p = (AStory*)((char*)self + i * 4);
		if (p->players[0]) {
			int j;
			fn_8001867C(p->players[0]);
			j = 3;
			do {
				PlayerTransform transform;
				fn_1_6ABC(&transform);
				transform.index = idx;
				fn_1_5994(&transform.translation, &lbl_1_rodata_7B0[idx]);
				transform.angle = lbl_1_rodata_840[idx];
				transform.type  = 2;
				fn_1_63A8(p->players[0], &transform);
				j--;
				idx++;
			} while (j != 0);
		}
	}
}

// 0x7644 - walk the current page's player list, kill matching nodes.
void fn_1_7644(AStory* self)
{
	int page = self->curPage;
	if (page >= 0 && page < 4) {
		void* obj = self->players[page];
		if (obj) {
			void* node = *(void**)((char*)obj + 0x14);
			s32* ids   = (s32*)lbl_1_data_11A4;
			while (node) {
				if (fn_1_86B0((s32*)node, *ids)) {
					fn_1_55A4(node, 3);
				}
				node = *(void**)((char*)node + 0xc);
			}
		}
	}
}

// 0x76D4 - set the play/hide/translate state for every loaded player.
void fn_1_76D4(AStory* self, int mode)
{
	register StoryIndex k;
	AStory* p;
	int i3;
	int i;
	i  = 0;
	p  = self;
	i3 = 0;
	for (; i != 4; p = (AStory*)((char*)p + 4), i3 += 3, i++) {
		if (p->players[0]) {
			void* node = *(void**)((char*)p->players[0] + 0x14);
			k          = (StoryIndex)i3;
			s32* ids   = (s32*)lbl_1_data_11A4;
			for (; node; node = *(void**)((char*)node + 0xc)) {
				if (fn_1_86B0((s32*)node, ids[0])) {
					f32 val;
					u8 buf[0xc];
					int off12 = (u32)k * 0xc;
					int off4  = (u32)k * 4;
					switch (mode) {
						case 0:
							fn_1_5994((Vec3*)buf, (Vec3*)((char*)lbl_1_rodata_7B0 + off12));
							val = *(f32*)((char*)lbl_1_rodata_840 + off4);
							break;
						case 1:
							fn_1_5994((Vec3*)buf, (Vec3*)((char*)lbl_1_rodata_930 + off12));
							val = *(f32*)((char*)lbl_1_rodata_9C0 + off4);
							break;
						case 2:
							fn_1_5994((Vec3*)buf, (Vec3*)((char*)lbl_1_rodata_870 + off12));
							val = *(f32*)((char*)lbl_1_rodata_900 + off4);
							break;
						default:
							break;
					}
					fn_1_58B4(node, buf);
					fn_1_5844(node, val);
					k = (StoryIndex)(k + 1);
				}
			}
		}
	}
}

// 0x782C - snap the title fade value from the timeline keyframe.
void fn_1_782C(AStory* self)
{
	if (self->timeline) {
		Ent8* keys   = *(Ent8**)((char*)self->timeline + 8);
		self->unk_34 = keys[self->unk_70].b;
	}
}

// 0x7854 - SetMode helper: load the keyframe range for a page.
void fn_1_7854(AStory* self, int page)
{
	self->unk_70  = lbl_1_rodata_750[page].lo;
	self->unk_74  = lbl_1_rodata_750[page].hi;
	self->curPage = page;
}

// 0x787C - count-up watchdog; force the reset state after 300 ticks.
void fn_1_787C(AStory* self)
{
	if (++self->counter > 300) {
		self->unk_48 = 1;
		self->state  = 3;
	}
}

// 0x78A4 - ExecSelect: navigate the page ring / poll the controller.
void fn_1_78A4(AStory* self)
{
	int idx = fn_1_11FFC(&self->itemSel[self->curPage], -1);
	if (idx != -1 && self->sel110[self->curPage] != idx) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		}
		self->state  = 1;
		self->unk_60 = 7;
		{
			volatile AStory* page = (AStory*)((char*)self + self->curPage * 4);
			int old               = page->sel110[0];
			if (old == 6 && idx == 0) {
				fn_1_7B24(&self->snd_64, &lbl_1_data_293C[self->curPage][old]);
			} else if (old == 0 && idx == 6) {
				fn_1_7B24(&self->snd_64, &lbl_1_data_292C[self->curPage][page->sel110[0]]);
			} else if (old > idx) {
				fn_1_7B24(&self->snd_64, &lbl_1_data_292C[self->curPage][page->sel110[0]]);
			} else {
				fn_1_7B24(&self->snd_64, &lbl_1_data_293C[self->curPage][page->sel110[0]]);
			}
		}
		self->sel110[self->curPage] = idx;
	} else {
		switch (fn_800A9398(lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				fn_800A8174(self, 0x155);
				break;
			case 1:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
				}
				self->state  = 1;
				self->unk_60 = 6;
				fn_1_7B24(&self->snd_64, &lbl_1_rodata_750[self->curPage].snd10);
				fn_1_7524(self);
				fn_1_119E0(&self->itemSel[self->curPage], 0);
				self->sel110[self->curPage] = 0;
				break;
			case 2:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
				}
				self->state = 9;
				fn_80014154();
				break;
		}
	}
}

// 0x7B24 - copy an 8-byte {id,float} pair.
void fn_1_7B24(void* dst, const void* src)
{
	((s32*)dst)[0] = ((const s32*)src)[0];
	((s32*)dst)[1] = ((const s32*)src)[1];
}

// 0x7B38 - ExecLast: last-story confirm sub-state machine.
void fn_1_7B38(AStory* self)
{
	int sel = fn_1_11E48(&self->pageSel, -1);
	if (sel != -1 && sel != 4) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		}
		fn_1_7854(self, sel);
		switch (sel) {
			case 0:
				if (fn_1_73D8(self) == 2) {
					self->state    = 1;
					self->unk_60   = 6;
					self->snd_64.a = 0x62;
					self->snd_64.b = 0x63;
				} else {
					self->state    = 1;
					self->unk_60   = 6;
					self->snd_64.a = 0x59;
					self->snd_64.b = 0x5a;
				}
				break;
			case 3:
				if (fn_1_73D8(self) == 2) {
					self->state    = 1;
					self->unk_60   = 6;
					self->snd_64.a = 0x60;
					self->snd_64.b = 0x61;
				} else {
					self->state    = 1;
					self->unk_60   = 6;
					self->snd_64.a = 0x57;
					self->snd_64.b = 0x58;
				}
				fn_1_76D4(self, 0);
				break;
		}
	} else {
		if (fn_1_73D8(self) == 2) {
			self->unk_34 += lbl_1_rodata_BC4;
			if (((f32*)(*(char**)(lbl_1_data_2824 + 8)))[0x2ec / 4] < self->unk_34) {
				self->unk_34 = ((f32*)(*(char**)(lbl_1_data_2824 + 8)))[0x2e4 / 4];
			}
		} else {
			self->unk_34 = ((f32*)(*(char**)(lbl_1_data_2824 + 8)))[0x2b4 / 4];
		}
		switch (fn_800A9398(lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				if (fn_1_73D8(self) == 2) {
					fn_800A8174(self, 0x152);
				} else {
					fn_800A8174(self, 0x153);
				}
				break;
			case 1:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
				}
				self->unk_48 = 0;
				self->state  = 2;
				break;
			case 2:
				if (fn_1_73D8(self) == 2) {
					if (lbl_8042C388) {
						fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
					}
					self->state = 9;
					fn_80014154();
				} else {
					fn_800A8174(self, 0x153);
				}
				break;
		}
	}
}

// 0x7DE8 - ExecSelect2: chapter-select sub-state machine.
void fn_1_7DE8(AStory* self)
{
	int sel = fn_1_11E48(&self->pageSel, -1);
	if (sel != -1 && sel != self->curPage) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		}
		if (sel != 4) {
			fn_1_7854(self, sel);
			fn_1_782C(self);
		} else {
			self->curPage = 4;
			if (fn_1_73D8(self) == 2) {
				self->state    = 1;
				self->unk_60   = 8;
				self->snd_64.a = 0x5b;
				self->snd_64.b = 0x5c;
			} else {
				self->state    = 1;
				self->unk_60   = 8;
				self->snd_64.a = 0x55;
				self->snd_64.b = 0x56;
			}
			fn_1_76D4(self, 1);
		}
	} else {
		fn_800A8120(self);
		switch (fn_800A9398(lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				fn_800A8174(self, (int)lbl_1_rodata_9F0[self->curPage]);
				break;
			case 1:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
				}
				self->unk_48 = 0;
				self->state  = 2;
				break;
			case 2:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
				}
				if (fn_1_7314(self, self->curPage) != 100) {
					self->state = 9;
					fn_80014154();
				} else {
					self->state  = 1;
					self->unk_60 = 7;
					fn_1_7B24(&self->snd_64, &lbl_1_rodata_750[self->curPage].snd08);
					fn_1_74A0(self, self->curPage);
				}
				break;
		}
	}
}

// 0x8010 - arm the fade-out transition.
void fn_1_8010(AStory* self)
{
	self->state    = 1;
	self->unk_60   = 6;
	self->snd_64.a = 0;
	self->snd_64.b = 1;
}

// 0x8030 - SetMode: reconfigure for a new sub-mode.
void fn_1_8030(AStory* self, int mode)
{
	switch (mode) {
		case 1:
			self->timeline = lbl_1_data_2824;
			break;
		case 6:
			self->timeline = lbl_1_data_2824;
			fn_1_782C(self);
			fn_1_7578(self);
			break;
		case 8:
			self->timeline = lbl_1_data_2824;
			if (fn_1_73D8(self) == 2) {
				self->unk_34 = ((f32*)(*(char**)(lbl_1_data_2824 + 8)))[0x2e4 / 4];
			} else {
				self->unk_34 = ((f32*)(*(char**)(lbl_1_data_2824 + 8)))[0x2b4 / 4];
			}
			break;
		case 9:
			fn_1_7644(self);
			self->counter = 0;
			break;
	}
}

// 0x810C - OnExec: per-frame state dispatch.
void fn_1_810C(AStory* self)
{
	switch (self->mode) {
		case 5:
			fn_1_8010(self);
			break;
		case 6:
			fn_1_7DE8(self);
			break;
		case 7:
			fn_1_78A4(self);
			break;
		case 8:
			fn_1_7B38(self);
			break;
		case 9:
			fn_1_787C(self);
			break;
	}
	fn_1_7218(self);
}

// 0x8190 - __ct.
AStory* fn_1_8190(AStory* self, s16 flag)
{
	s32* pg;
	if (self) {
		self->vtable = lbl_1_data_29BC;
		fn_800A96B0(lbl_80303EC8, 0x28, 0);
		if (self->unk_48 == 1) {
			fn_800191F8(lbl_8029C310, 0, 0);
			fn_8001938C(lbl_8029C310);
			fn_800A96B0(lbl_80303EC8, 0x27, 1);
			fn_800A96B0(lbl_80303EC8, 0x18, 0);
			switch (*(pg = &self->curPage)) {
				case 0:
					fn_80138C78(lbl_8042C7E0, 0);
					break;
				case 1:
					fn_80138C78(lbl_8042C7E0, 1);
					break;
				case 2:
					fn_80138C78(lbl_8042C7E0, 2);
					break;
				case 3:
					fn_80138C78(lbl_8042C7E0, 3);
					break;
				case 4:
					fn_80138C78(lbl_8042C7E0, 4);
					break;
			}
			if (self->curPage == 4 && fn_1_73D8(self) == 2) {
				if (fn_1_7314(self, self->curPage) == 100) {
					fn_80138A9C(lbl_8042C7E0);
				}
			} else if (fn_1_7314(self, *pg) == 100) {
				if (*pg == 3 && lbl_1_data_294C[self->sel110[*pg]] == 8) {
					fn_801384F0(lbl_8042C7E0, 0x24);
				} else if (*pg == 2 && lbl_1_data_294C[self->sel110[self->curPage]] == 2) {
					fn_801384F0(lbl_8042C7E0, 0x19);
				} else {
					fn_801384F0(lbl_8042C7E0, lbl_1_data_294C[self->sel110[self->curPage]]);
				}
			}
		}
		fn_800A96B0(lbl_80303EC8, 0x2a, 5);
		__destroy_arr(&self->itemSel[0], (void*)fn_1_120E0, 0x8c, 4);
		fn_1_120E0(&self->pageSel, -1);
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// 0x8434 - Create: full field initialisation.
#pragma opt_strength_reduction off
#pragma opt_loop_invariants off
#pragma opt_common_subs off
#pragma opt_propagation off
AStory* fn_1_8434(AStory* self, void* parent)
{
	int i;
	int itemOff;
	int selOff;
	int j;
	(void)parent;
	__ct__10EasySelectFP7TObject(self);
	self->vtable = lbl_1_data_29BC;
	fn_1_12124(&self->pageSel);
	__construct_array(&self->itemSel[0], (void*)fn_1_12124, (void*)fn_1_120E0, 0x8c, 4);
	self->name   = lbl_1_data_1DE4;
	self->unk_1E = 0x364;
	self->unk_40 = 0xf;
	self->unk_44 = 4;
	itemOff      = 0;
	self->mode   = itemOff;
	self->state  = 5;
	self->unk_60 = itemOff;
	for (i = 0; i != 4; itemOff += 4, i++) {
		void* p = advE3Rom_resume(0x28);
		if (p) {
			p = __ct__7TObjectFP7TObject(p, self);
		}
		*(void**)((char*)self + itemOff + 0x350) = p;
	}
	selOff  = 0;
	itemOff = 0;
	i       = 0;
	for (; selOff != 4; itemOff += 0x8c, i += 4, selOff++) {
		fn_1_120C4(&self->pageSel, selOff);
		for (j = 0; j != 7; j++) {
			fn_1_120C4((Sel*)((char*)self + itemOff + 0x120), j);
		}
		fn_1_119E0((char*)self + itemOff + 0x120, 0);
		fn_1_119D4((char*)self + itemOff + 0x120);
		*(s32*)((char*)self + i + 0x110) = 0;
	}
	if (fn_1_73D8(self) != 0) {
		fn_1_120C4(&self->pageSel, 4);
	}
	fn_1_119E0(&self->pageSel, 0);
	fn_1_7854(self, 0);
	{
		void* t = advE3Rom_resume(0x34);
		if (t) {
			fn_1_71A4((Title*)t, self);
		}
	}
	{
		void* t = advE3Rom_resume(0x30);
		if (t) {
			fn_1_10F40(t, self);
		}
	}
	__ct__10DAnimClassFv(self, 4);
	return self;
}

#pragma opt_strength_reduction on
#pragma opt_loop_invariants reset
#pragma opt_common_subs reset
#pragma opt_propagation reset

// 0x85FC - OnExec: instantiate when the manager hands back a slot.
void fn_1_85FC(AStory* self)
{
	AStory* obj = (AStory*)advE3Rom_resume(0x364);
	if (obj) {
		fn_1_8434(obj, self);
	}
}

// 0x863C - Initialize: load adv_story .one file.
void fn_1_863C(void)
{
	fn_1_64E0();
	fn_8012CA94(lbl_1_data_2914);
}

// 0x8668 - Finalize: release adv_story .one file and reset the manager.
void fn_1_8668(void)
{
	fn_1_11750(2);
	fn_8012CB70(lbl_1_data_2914);
	fn_1_65BC();
	fn_800A8C9C(lbl_80303EC8, lbl_1_data_2968);
}

// 0x86B0 - equality helper (returns 1 when *p == v).
int fn_1_86B0(s32* p, s32 v)
{
	return *p == v;
}

// 0x86C8 - module boot: register the ADV_STORY task class and init subsystems.
void fn_1_86C8(void)
{
	void* tbl[4];
	tbl[0] = 0;
	tbl[1] = 0;
	tbl[2] = 0;
	tbl[3] = 0;
	fn_800A9418(lbl_80303EC8, tbl);
	fn_1_69AC();
	fn_80126254();
	fn_1_15268();
	fn_8013BBE0();
	fn_1_10FB0();
	fn_1_11940();
	fn_800A94C4(lbl_80303EC8);
	fn_8011F13C();
	fn_800A953C(lbl_80303EC8);
	fn_80196D00();
}

// 0x8740 - module setup: register the dispatch tables into the save controller.
void fn_1_8740(void)
{
	void* tbl[4];
	fn_80196D00();
	fn_8011F3AC();
	fn_800A9584(lbl_80303EC8);
	fn_800A94E8(lbl_80303EC8);
	{
		void* h = fn_8016E810(lbl_1_data_29F8);
		fn_8016E868(h, lbl_1_data_29F8);
	}
	fn_1_11994();
	fn_1_118E4(*(void**)((char*)lbl_80303EC8 + 0x68));
	fn_1_10FD8();
	fn_8013BC78();
	fn_1_15294();
	fn_801262DC();
	fn_1_6A0C();
	tbl[0] = &lbl_1_data_2A08;
	tbl[1] = &lbl_1_data_2A68;
	tbl[2] = &lbl_1_data_2BB8;
	tbl[3] = (void*)fn_1_11000;
	fn_800A9418(lbl_80303EC8, tbl);
	fn_800A9444(lbl_80303EC8);
}
#pragma dont_inline reset

} // extern "C"
