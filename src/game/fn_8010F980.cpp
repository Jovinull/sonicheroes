// Steps a set object with timed hits (HYPOTHESIS; names inferred): kills it (signal bit 0) when it
// is out of range (lbl_8042E928) or idle (mode 0), or, with its collision flagged (attr 0x10), when
// its parent is gone. While alive (fn_80017800) it runs the mode-1 update (fn_8010FF6C), drops the
// timers that reached the limit (moving the entry past the end into the slot), advances the rest
// by lbl_8042E92C and updates the collision range; in mode 1 it registers the collision at its
// position and angles, or clears it while lbl_8029C310 (0x18) is set. Counts its frames (0xEA).
#include "game/setObj.h"

struct CCL_INFO8010F980 {
	u8 kind, form, push, damage;
	u32 attr; // 0x4
};

struct CCL_HIT_INFO8010F980 {
	s8 my_num, hit_num;
	u16 flag;
	void* hit_ccl;
};

// Collision of an object (only the members used here).
class C_COLLI
{
public:
	void ClearInfo();
	void Entry();
	void CalcRange();
	u16 id;
	s16 nbHit, strength, vitality;
	u16 flag, nbInfo;
	f32 colli_range;
	CCL_INFO8010F980* info;           // 0x10
	CCL_HIT_INFO8010F980 hit_info[8]; // 0x14
	RwV3d normal, pos;                // 0x54, 0x60
	sAngle ang;                       // 0x6C
	s32 character_id;                 // 0x78
	RwV3d pre_pos;                    // 0x7C
};

struct Object8010F980 {
	u8 pad0[0x4];
	u16 signal; // 0x4
	u8 pad6[0x10 - 0x6];
	void* parent; // 0x10
	u8 pad14[0x60 - 0x14];
	C_COLLI colli; // 0x60
	u8 padE8[0xEA - 0xE8];
	s16 frame;       // 0xEA
	RwV3d pos;       // 0xEC
	RwV3d direction; // 0xF8
	sAngle ang;      // 0x104
	u8 pad110[0x114 - 0x110];
	f32 limit; // 0x114
	u8 pad118[0x11C - 0x118];
	s32 count; // 0x11C
	u8 pad120[0x124 - 0x120];
	f32 times[1]; // 0x124
	u8 pad128[0x1A8 - 0x128];
	s32 mode; // 0x1A8
};

struct GameState8010F980 {
	u8 pad0[0x18];
	s32 unk18; // 0x18
};

extern "C" {
extern f32 lbl_8042E928;
extern const f32 lbl_8042E92C;
extern GameState8010F980 lbl_8029C310;
s32 fn_80017800(void* object);
void fn_8010FF6C(Object8010F980* self);

void fn_8010F980(Object8010F980* self)
{
	s32 i;
	f32* time;

	if (setobjCheckRangeOut2(&self->pos, lbl_8042E928) != 0 || self->mode == 0) {
		self->signal |= 1;
		return;
	}
	if (fn_80017800(self->parent) == 0) {
		self->colli.info->attr |= 0x10;
		self->signal |= 1;
		return;
	}
	if (fn_80017800(self) != 0) {
		if (self->mode == 1) {
			fn_8010FF6C(self);
		}
		time = self->times;
		for (i = 0; i < self->count; i++, time++) {
			// Retail tests the comparison as a signed int flag.
			if ((s32)(*time >= self->limit) != 0) {
				*time = self->times[self->count];
				self->count--;
			}
		}
		time = self->times;
		for (i = 0; i < self->count; i++, time++) {
			*time += lbl_8042E92C;
		}
		self->colli.CalcRange();
		if (self->mode == 1) {
			if (lbl_8029C310.unk18 == 0) {
				self->colli.pre_pos = self->colli.pos;
				self->colli.pos     = self->pos;
				self->colli.ang     = self->ang;
				self->colli.Entry();
			} else {
				self->colli.ClearInfo();
			}
		}
	}
	self->frame++;
}
}
