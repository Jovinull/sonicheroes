// Destructor of a playable character (HYPOTHESIS; the class name is UNKNOWN, its vtable is
// lbl_80249F18): releases the character slot (fn_8003EDA8), clears the per-character effect
// pointers by the character kind at 0x761 (kinds 2, 5, 8 and 11, jump table in owned .data; kind 11
// also drops or destroys the object at 0xA74 depending on fn_80017800), runs the teardown helpers
// fn_8003F678 and fn_8003F308, releases 0x5D4 (fn_801A46D0), destroys the member group at 0xA48
// (its two EffWink and the object at 0xB90), the EffBall at 0xA2C and the EffShadow at 0x9EC, runs
// the base destructor dtor_8003FFB8 and frees the object on the game heap when the delete flag is
// positive. Returns the object. The jump table starts on a 4-byte boundary (0x8024A25C), hence
// data_section_alignment=4.
#include "types.h"

struct THeapCtrl {
	void Free(void* p);
};

struct Player80077040 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x5D4 - 0x1C];
	void* f5D4; // 0x5D4
	u8 pad5D8[0x760 - 0x5D8];
	s8 f760; // 0x760
	s8 kind; // 0x761
	u8 pad762[0x8E0 - 0x762];
	s32 f8E0; // 0x8E0
	u8 pad8E4[0x950 - 0x8E4];
	s32 f950; // 0x950
	u8 pad954[0x9EC - 0x954];
	u8 shadow[0xA1C - 0x9EC]; // 0x9EC: EffShadow
	s32 fA1C;                 // 0xA1C
	s32 fA20;                 // 0xA20
	u8 padA24[0xA2C - 0xA24];
	u8 ball[0xA60 - 0xA2C]; // 0xA2C: EffBall
	s32 fA60;               // 0xA60
	s32 fA64;               // 0xA64
	s32 fA68;               // 0xA68
	s32 fA6C;               // 0xA6C
	s32 fA70;               // 0xA70
	void* fA74;             // 0xA74
	s32 fA78;               // 0xA78
	u8 padA7C[0xA80 - 0xA7C];
	s32 fA80; // 0xA80
	u8 padA84[0xBC4 - 0xA84];
	s32 fBC4; // 0xBC4
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_80249F18[];
void fn_8003EDA8(s32 n);
s32 fn_80017800(void* object);
void fn_8005FD8C(void* object, s16 flags);
void fn_8003F678(Player80077040* o);
void fn_8003F308(Player80077040* o);
void fn_801A46D0(void* p);
void dtor_800F1618(void* p, s16 flags);
void __dt__7EffWinkFv(void* p, s16 flags);
void __dt__7EffBallFv(void* p, s16 flags);
void __dt__9EffShadowFv(void* p, s16 flags);
void dtor_8003FFB8(void* p, s16 flags);

Player80077040* fn_80077040(Player80077040* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80249F18;
		fn_8003EDA8(o->f760);
		o->fA1C = 0;
		o->fA20 = 0;
		switch (o->kind) {
			case 2:
				o->fA60 = 0;
				o->fA64 = 0;
				o->fA68 = 0;
				o->fA6C = 0;
				o->fA70 = 0;
				break;
			case 5:
				o->fA60 = 0;
				o->fA64 = 0;
				o->fA68 = 0;
				o->fA6C = 0;
				o->fA70 = 0;
				o->fA74 = 0;
				o->fA80 = 0;
				o->fA78 = 0;
				o->fBC4 = 0;
				break;
			case 8:
				o->fA60 = 0;
				o->fA64 = 0;
				o->fA68 = 0;
				o->fA6C = 0;
				o->fA70 = 0;
				o->fA74 = 0;
				break;
			case 11:
				o->fA60 = 0;
				o->fA64 = 0;
				o->fA68 = 0;
				o->fA6C = 0;
				o->fA70 = 0;
				if (o->kind == 11) {
					if (o->fA74 != NULL && fn_80017800(o->fA74) == 0) {
						o->fA74 = NULL;
					} else if (o->fA74 != NULL) {
						fn_8005FD8C(o->fA74, -1);
						o->fA74 = NULL;
					}
				}
				break;
		}
		fn_8003F678(o);
		o->f8E0 = 0;
		o->f950 = 0;
		fn_8003F308(o);
		fn_801A46D0(o->f5D4);
		o->f5D4 = NULL;
		if ((u8*)o + 0xA48 != NULL) {
			dtor_800F1618((u8*)o + 0xB90, -1);
			__dt__7EffWinkFv((u8*)o + 0xB68, -1);
			__dt__7EffWinkFv((u8*)o + 0xB40, -1);
		}
		__dt__7EffBallFv(o->ball, 0);
		__dt__9EffShadowFv(o->shadow, 0);
		dtor_8003FFB8(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
