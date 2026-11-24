#include "types.h"

struct sAngle {
	s16 x;
	s16 y;
	s16 z;
};

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Frame {
	u8 pad00[4];
	void* mat; // 0x04
};

class OBJ_ReplacePlayer
{
public:
	s32 mode;     // 0xB8
	s8 states[8]; // 0xBC
	s16 angle;    // 0xC4
	u8 padC6[0xD4 - 0xC6];
	sAngle ang; // 0xD4
	u8 padDA[0xE0 - 0xDA];
	s32 timer; // 0xE0
	f32 speed; // 0xE4
	u8 padE8[0xF0 - 0xE8];
	f32 height; // 0xF0
	u8 padF4[4];
	Frame* frame; // 0xF8
	void objSetPlayerPosition(int player, u8 flags, RwV3d* pos, sAngle* ang);
};

struct PlayerSlot {
	u8 pad00[1];
	s8 state; // 0x01
	u8 pad02[0x256];
	void* team; // 0x258
};

struct Obj {
	u8 pad00[0x30];
	u8 colli[0x88];            // 0x30
	OBJ_ReplacePlayer replace; // 0xB8
};

extern "C" u8 lbl_8042C1A4[];
extern "C" PlayerSlot* lbl_802AD0D0[];
extern "C" void* lbl_802AD070[];
extern "C" void* lbl_8042C388;

extern "C" void fn_80021824(void* list);
extern "C" void* fn_16_D10(void* colli);
extern "C" u32 fn_16_DC8(void* colli, s32 kind);
extern "C" void fn_16_DB4(void* colli);
extern "C" void fn_16_DA0(void* colli);
extern "C" s32 fn_16_D98(void* hit);
extern "C" s32 fn_80041B64(s32 type);
extern "C" void* fn_8019E8EC(void* frame);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 n, void* mat);
extern "C" void copyVec3(RwV3d* dst, RwV3d* src);
extern "C" s32 fn_80091FAC(void* team);
extern "C" s32 fn_80091F54(void* team, s32 member);
extern "C" s32 fn_16_D80(void* team);
extern "C" s32 fn_800927D0(void* team, s32 kind);
extern "C" s32 fn_16_D70(void* team, s32 member);
extern "C" s32 fn_800AB35C(void* task);
extern "C" void fn_800E0CC8(s32 player, f32 speed, sAngle* ang, s32 arg);
extern "C" s32 fn_16_D64(void* team);
extern "C" void fn_8001F674(s32 a, s32 b, s32 c, s32 d);
extern "C" void fn_800B52E8(void* obj, s32 a, s32 b, s32 c);

extern "C" void fn_16_9EC(Obj* obj)
{
	void* hit;
	s32 player;
	void* team;
	s32 member;
	RwV3d a;
	RwV3d c;
	RwV3d b;
	void* mat;

	fn_80021824(lbl_8042C1A4);
	if (fn_16_DC8(obj->colli, 0x13)) {
		fn_16_DB4(obj->colli);
		return;
	}
	fn_16_DA0(obj->colli);
	fn_80021824(lbl_8042C1A4);

	while ((hit = fn_16_D10(obj->colli)) != NULL) {
		player = fn_80041B64(fn_16_D98(hit));
		if (obj->replace.states[player] > 0) {
			continue;
		}
		a.x = a.z = 0.0f;
		a.y       = 5.0f + obj->replace.height;
		mat       = fn_8019E8EC(obj->replace.frame->mat);
		fn_8019941C(&b, &a, 1, mat);
		copyVec3(&c, &b);
		team = lbl_802AD0D0[player]->team;
		if (fn_80091FAC(team) == 2 && fn_80091F54(team, player)) {
			player = fn_16_D80(team);
			member = fn_16_D70(team, fn_800927D0(team, 1));
			if (fn_800AB35C(lbl_802AD070[member]) == 1) {
				obj->replace.states[member] = 9;
			}
			member = fn_16_D70(team, fn_800927D0(team, 2));
			if (fn_800AB35C(lbl_802AD070[member]) == 1) {
				obj->replace.states[member] = 9;
			}
		}
		obj->replace.objSetPlayerPosition(player, 0, &c, NULL);
		fn_800E0CC8(player, a.y, &obj->replace.ang, obj->replace.angle);
		obj->replace.states[player] = 9;
		obj->replace.timer          = 0;
		obj->replace.speed          = 0.5f;
		obj->replace.mode           = 2;
		fn_8001F674(fn_16_D64(team), 4, 0xF, 0);
		switch (lbl_802AD0D0[player]->state) {
			case 0:
			case 3:
			case 6:
			case 9:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1000, 0, 0);
				}
				break;
			case 2:
			case 5:
			case 8:
			case 11:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1001, 0, 0);
				}
				break;
			case 1:
			case 4:
			case 7:
			case 10:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x1002, 0, 0);
				}
				break;
		}
	}
}
