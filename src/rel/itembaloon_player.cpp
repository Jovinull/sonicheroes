#include "types.h"

// TObjItembaloon::ItembaloonPlayer (the PS2 build's name, by its place in the
// PS2 order; itembaloonPlayer here). Each player that touches the balloon
// bursts it: unless it is invincible (state bit 0x4000), a player who is not
// already being thrown by the team's formation (mode 3, step 14) is either
// stopped (in the formation's modes 5 and 6, or in actions 0x45, 0x1F and
// 0x20) or bounced up facing back; the balloon's item goes to the team, once,
// and the burst sounds. A balloon that was whole ends, and it stops shaking.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct ItembaloonHit {
	u8 unk00[0x78];
	void* owner; // 0x78
} ItembaloonHit;

typedef struct ItembaloonHitLink {
	u8 unk0[0x4];
	ItembaloonHit* colli; // 0x04
} ItembaloonHitLink;

typedef struct ItembaloonTask {
	u8 unk00[0x10];
	s16 state; // 0x10
} ItembaloonTask;

typedef struct ItembaloonPlayerObj {
	u8 unk000[0x6F0];
	s16 action; // 0x6F0
	u8 unk6F2[0xE];
	s32 angY; // 0x700
	u8 unk704[0x2B8];
	s8 team; // 0x9BC
} ItembaloonPlayerObj;

typedef struct ItembaloonTeam {
	u8 unk000[0x140];
	s32 mode; // 0x140
	u8 unk144[0x10];
	s32 step; // 0x154
} ItembaloonTeam;

typedef struct ItembaloonFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} ItembaloonFrame;

typedef struct ItemBoxIcon {
	u8 unk0[0x8];
	s32 item;  // 0x8
} ItemBoxIcon; // 0xC

typedef struct Itembaloon {
	u8 unk00[0x28];
	ItembaloonFrame* frame; // 0x28, the set object's (TObjSetObj)
	u8 unk2C[0x4];          // 0x2C
	u8 colli[0x88];         // 0x30 (C_COLLI)
	s8 item;                // 0xB8
	u8 unkB9[0x3];          // 0xB9
	s32 state;              // 0xBC
	RwV3d pos;              // 0xC0
	u8 unkCC[0x1C];         // 0xCC
	f32 shake;              // 0xE8
	s32 shakeTime;          // 0xEC
} Itembaloon;

typedef enum EnumTypeItem { ITEM_COUNT = 13 } EnumTypeItem;

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" ItembaloonTask* lbl_802AD0D0[];
extern "C" ItembaloonPlayerObj* lbl_802AD070[];
extern "C" ItembaloonTeam* lbl_80303DC8[];
extern "C" ItemBoxIcon itemBoxIcons[];
extern "C" const f32 itembaloonOne[1];
extern "C" const f32 itembaloonBounce[1];

extern "C" void fn_80021824(void* collision);
extern "C" ItembaloonHitLink* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(void* owner);
extern "C" s32 fn_80091F54(ItembaloonTeam* team, s32 player);
extern "C" void fn_800AB42C(ItembaloonPlayerObj* player);
extern "C" void fn_800E0CC8(s32 player, f32 speed, sAngle* ang, s32 arg);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* a, s32 b, s32 c, s32 d);
extern "C" void SetEnd__10TObjSetObjFv(void* setObj);
void ExecuteAndDisplayItempanelEffectForAll(int group, int type, EnumTypeItem item, int data);

// the next collision that touched the balloon, if any
static inline ItembaloonHit* itembaloonNextHit(Itembaloon* object)
{
	ItembaloonHitLink* link = fn_800211A8(object->colli);

	return link != NULL ? link->colli : NULL;
}

extern "C" void itembaloonPlayer(Itembaloon* object)
{
	ItembaloonHit* hit;

	fn_80021824(lbl_8042C1A4);
	f32 one = itembaloonOne[0];
	while ((hit = itembaloonNextHit(object)) != NULL) {
		s32 player = fn_80041B64(hit->owner);
		if (player >= 0) {
			if (!(lbl_802AD0D0[player]->state & 0x4000)) {
				ItembaloonPlayerObj* body = lbl_802AD070[player];
				if (body != NULL) {
					ItembaloonTeam* team = lbl_80303DC8[body->team];
					if (fn_80091F54(team, player) && team->mode == 3 && team->step == 14) {
					} else if ((fn_80091F54(team, player) && (team->mode == 5 || team->mode == 6))
					    || body->action == 0x45 || body->action == 0x1F || body->action == 0x20) {
						fn_800AB42C(body);
					} else {
						sAngle ang;

						ang.x = 0;
						ang.y = 0x4000 - body->angY;
						ang.z = 0;
						fn_800E0CC8(player, itembaloonBounce[0], &ang, 0);
					}
					if (!(object->frame->flags & 0x10000)) {
						ExecuteAndDisplayItempanelEffectForAll(
						    body->team, player, (EnumTypeItem)itemBoxIcons[object->item].item, 0);
					}
				}
			}
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x1065, &object->pos, NULL, 1, 0x10, 0);
			}
		}
		if (object->state == 1) {
			object->state = 2;
			object->frame->flags |= 0x10000;
			SetEnd__10TObjSetObjFv(&object->frame);
		}
		object->shakeTime = 0;
		object->shake     = one;
	}
}
