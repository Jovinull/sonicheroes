// Destructor of a playable character (HYPOTHESIS; the class name is UNKNOWN, its vtable is
// lbl_8024D420). When the character is still registered in its slot (lbl_802AD090[0x760] points
// to its block at 0x6F0) it releases the slot (fn_8003EDA8), clears the team words 0x268-0x270 and
// its own effect words, then by the character kind at 0x761 (kinds 0, 3, 6 and 9, jump table in
// owned .data) clears the per-kind effect pointers: kind 0 also resets EffBall's original clumps 3
// and 4 and destroys the object at 0xA90, kind 3 the objects at 0xA88 and 0xA8C, kind 9 calls
// fn_8011AA70 and fn_80122B74. It then runs the teardown helpers fn_8003F678 and fn_8003F308 and
// releases 0x5D4 (fn_801A46D0). In every case it destroys the EffWink of the member group at
// 0xA48, the EffBall at 0xA2C and the EffShadow at 0x9EC, runs the base destructor dtor_8003FFB8
// and frees the object on the game heap when the delete flag is positive. Returns the object.
#include "types.h"

struct THeapCtrl {
	void Free(void* p);
};

struct RpClump;

struct EffBall {
	static void SetOriginalEffBallClumpPointer(int index, RpClump* clump);
};

struct Team80081B88 {
	u8 pad0[0x268];
	s32 f268; // 0x268
	s32 f26C; // 0x26C
	s32 f270; // 0x270
};

struct Player80081B88 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x5D4 - 0x1C];
	void* f5D4; // 0x5D4
	u8 pad5D8[0x6F0 - 0x5D8];
	u8 f6F0[0x760 - 0x6F0]; // 0x6F0
	s8 f760;                // 0x760
	s8 kind;                // 0x761
	u8 pad762[0x8E0 - 0x762];
	s32 f8E0; // 0x8E0
	u8 pad8E4[0x9B8 - 0x8E4];
	Team80081B88* team; // 0x9B8
	u8 pad9BC[0x9EC - 0x9BC];
	u8 shadow[0xA1C - 0x9EC]; // 0x9EC: EffShadow
	s32 fA1C;                 // 0xA1C
	u8 padA20[0xA2C - 0xA20];
	u8 ball[0xA68 - 0xA2C]; // 0xA2C: EffBall
	s32 fA68;               // 0xA68
	s32 fA6C;               // 0xA6C
	s32 fA70;               // 0xA70
	s32 fA74;               // 0xA74
	s32 fA78;               // 0xA78
	s32 fA7C;               // 0xA7C
	s32 fA80;               // 0xA80
	s32 fA84;               // 0xA84
	void* fA88;             // 0xA88
	void* fA8C;             // 0xA8C
	void* fA90;             // 0xA90
	u8 padA94[0xB10 - 0xA94];
	s32 fB10; // 0xB10
	s32 fB14; // 0xB14
	s32 fB18; // 0xB18
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_8024D420[];
extern void* lbl_802AD090[8];
void fn_8003EDA8(s32 n);
void fn_8005FD8C(void* object, s16 flags);
void fn_8003F678(Player80081B88* o);
void fn_8003F308(Player80081B88* o);
void fn_801A46D0(void* p);
void fn_8011AA70(void);
void fn_80122B74(void);
void __dt__7EffWinkFv(void* p, s16 flags);
void __dt__7EffBallFv(void* p, s16 flags);
void __dt__9EffShadowFv(void* p, s16 flags);
void dtor_8003FFB8(void* p, s16 flags);

Player80081B88* fn_80081B88(Player80081B88* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_8024D420;
		if (o->f6F0 == lbl_802AD090[(s32)o->f760]) {
			fn_8003EDA8(o->f760);
			o->team->f26C = 0;
			o->team->f270 = 0;
			o->team->f268 = 0;
			o->fB10       = 0;
			o->fB14       = 0;
			o->fB18       = 0;
			o->fA1C       = 0;
			switch (o->kind) {
				case 0:
					o->fA68 = 0;
					o->fA6C = 0;
					o->fA70 = 0;
					o->fA74 = 0;
					o->fA78 = 0;
					o->fA7C = 0;
					o->fA80 = 0;
					EffBall::SetOriginalEffBallClumpPointer(3, NULL);
					EffBall::SetOriginalEffBallClumpPointer(4, NULL);
					if (o->fA90 != NULL) {
						fn_8005FD8C(o->fA90, -1);
						o->fA90 = NULL;
					}
					break;
				case 3:
					o->fA68 = 0;
					o->fA6C = 0;
					o->fA74 = 0;
					o->fA78 = 0;
					o->fA7C = 0;
					o->fA80 = 0;
					o->fA84 = 0;
					if (o->kind == 3) {
						if (o->fA88 != NULL) {
							fn_8005FD8C(o->fA88, -1);
							o->fA88 = NULL;
						}
						if (o->fA8C != NULL) {
							fn_8005FD8C(o->fA8C, -1);
							o->fA8C = NULL;
						}
					}
					break;
				case 6:
					o->fA68 = 0;
					o->fA6C = 0;
					o->fA70 = 0;
					o->fA74 = 0;
					o->fA78 = 0;
					break;
				case 9:
					o->fA68 = 0;
					o->fA6C = 0;
					o->fA70 = 0;
					o->fA74 = 0;
					o->fA78 = 0;
					o->fA7C = 0;
					o->fA80 = 0;
					fn_8011AA70();
					fn_80122B74();
					break;
			}
			fn_8003F678(o);
			o->f8E0 = 0;
			fn_8003F308(o);
			fn_801A46D0(o->f5D4);
			o->f5D4 = NULL;
		}
		if ((u8*)o + 0xA48 != NULL) {
			__dt__7EffWinkFv((u8*)o + 0xAE8, -1);
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
