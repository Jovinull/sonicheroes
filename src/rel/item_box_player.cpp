#include "types.h"

// TObjItembox::ItemboxPlayer (the PS2 build's name), the same in the thirteen
// stage modules that share the engine core. While something touches the box as
// kind 0x13 or 1 it only stops being solid. Otherwise the first player whose
// collision touches it opens it, or, failing that, the first other collision
// (not of kinds 0xA and 0xB) that a player or a team's object owns. A player
// who is not invincible (state bit 0x4000) is stopped unless the team's
// formation is in mode 5 or 6, and, once, the box's item goes to the team with
// its burst effect above the box; the box sounds, a whole box ends, and its
// shake is reset. A box nobody opened returns early.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct ItemboxColliShape {
	u8 kind; // 0x00
	u8 unk01[0x2F];
} ItemboxColliShape; // 0x30

typedef struct ItemboxColli {
	u8 unk00[0x10];
	ItemboxColliShape* shapes; // 0x10
	u8 unk14[0x64];
	void* owner; // 0x78
} ItemboxColli;

typedef struct ItemboxHit {
	u8 unk0;
	s8 shape; // 0x01
	u8 unk2[0x2];
	ItemboxColli* other; // 0x04
} ItemboxHit;

typedef struct ItemboxHitLink {
	u8 unk0[0x4];
	ItemboxColli* colli; // 0x04
} ItemboxHitLink;

typedef struct ItemboxTask {
	u8 unk00[0x10];
	s16 state; // 0x10
} ItemboxTask;

typedef struct ItemboxPlayerObj {
	u8 unk000[0x9BC];
	s8 team; // 0x9BC
} ItemboxPlayerObj;

typedef struct ItemboxTeam {
	u8 unk000[0x140];
	s32 mode; // 0x140
} ItemboxTeam;

typedef struct ItemboxFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} ItemboxFrame;

typedef struct ItemBoxIcon {
	u8 unk0[0x8];
	s32 item;  // 0x8
} ItemBoxIcon; // 0xC

typedef struct Itembox {
	u8 unk00[0x28];
	ItemboxFrame* frame; // 0x28
	u8 unk2C[0x4];
	u8 colli[0x8];  // 0x30 (C_COLLI)
	u16 colliFlags; // 0x38
	u8 unk3A[0x7E];
	s8 item; // 0xB8
	u8 unkB9[0x3];
	s32 state;  // 0xBC
	RwV3d pos;  // 0xC0
	sAngle ang; // 0xCC
	s32 unkD8;  // 0xD8
	f32 unkDC;  // 0xDC
	u8 unkE0[0xC];
	s32 unkEC; // 0xEC
} Itembox;

typedef enum EnumTypeItem { ITEM_COUNT = 13 } EnumTypeItem;

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" ItemboxTask* lbl_802AD0D0[];
extern "C" ItemboxPlayerObj* lbl_802AD070[];
extern "C" ItemboxTeam* lbl_80303DC8[];
extern "C" ItemBoxIcon itemBoxIcons[];
extern "C" const f32 itemboxBurstLift;
extern "C" const f32 itemboxScaleReset;

extern "C" void fn_80021824(void* collision);
extern "C" ItemboxHitLink* fn_80020BD8(void* colli, s32 kind);
extern "C" ItemboxHitLink* fn_800211A8(void* colli);
extern "C" ItemboxHit* fn_800210C4(void* colli);
extern "C" s32 fn_80041B64(void* owner);
extern "C" s32 fn_80041AB0(void* owner);
extern "C" s32 fn_800418A8(void* owner);
extern "C" s32 fn_80091F54(ItemboxTeam* team, s32 player);
extern "C" void fn_800AB42C(ItemboxPlayerObj* player);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
extern "C" void* fn_8006298C(s32 type, RwV3d* pos, sAngle* ang);
extern "C" void SetEnd__10TObjSetObjFv(void* setObj);
void ExecuteAndDisplayItempanelEffectForAll(int group, int type, EnumTypeItem item, int data);

static inline ItemboxColli* itemboxHitter(ItemboxHitLink* link)
{
	return link != NULL ? link->colli : NULL;
}

extern "C" void ItemboxPlayer__11TObjItemboxFv(Itembox* object)
{
	ItemboxColli* hitter;
	ItemboxHit* hit;
	s32 player;
	s32 team;

	fn_80021824(lbl_8042C1A4);
	if (itemboxHitter(fn_80020BD8(object->colli, 0x13)) != NULL) {
		object->colliFlags &= ~0x40;
		return;
	}
	fn_80021824(lbl_8042C1A4);
	if (itemboxHitter(fn_80020BD8(object->colli, 1)) != NULL) {
		object->colliFlags &= ~0x40;
		return;
	}
	if (object->unkEC == 0) {
		object->colliFlags |= 0x40;
	}
	player = -1;
	team   = -1;
	while ((hitter = itemboxHitter(fn_800211A8(object->colli))) != NULL) {
		player = fn_80041B64(hitter->owner);
		if (player >= 0) {
			break;
		}
	}
	if (player < 0) {
		while ((hit = fn_800210C4(object->colli)) != NULL) {
			s32 kind = hit->other->shapes[hit->shape].kind;
			void* owner;

			if (kind < 0xC && kind >= 0xA) {
				continue;
			}
			owner  = hit->other->owner;
			player = fn_80041B64(owner);
			if (player >= 0) {
				break;
			}
			player = fn_80041AB0(owner);
			if (player < 0) {
				continue;
			}
			team = fn_800418A8(owner);
			break;
		}
	}
	if (player >= 0) {
		if (!(lbl_802AD0D0[player]->state & 0x4000)) {
			ItemboxPlayerObj* body = lbl_802AD070[player];

			if (team == -1 && body != NULL) {
				team = body->team;
				if (!fn_80091F54(lbl_80303DC8[team], player)
				    || (lbl_80303DC8[team]->mode != 5 && lbl_80303DC8[team]->mode != 6)) {
					fn_800AB42C(body);
				}
			}
			if (team != -1 && !(object->frame->flags & 0x10000)) {
				ExecuteAndDisplayItempanelEffectForAll(
				    team, player, (EnumTypeItem)itemBoxIcons[object->item].item, 0);
				RwV3d pos = object->pos;

				pos.y += itemboxBurstLift;
				fn_8006298C(0x15, &pos, &object->ang);
			}
		}
		if (!(object->frame->flags & 0x10000) && lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1033, 0, 0);
		}
	} else {
		return;
	}
	if (object->state == 1) {
		object->state = 2;
		object->frame->flags |= 0x10000;
		SetEnd__10TObjSetObjFv(&object->frame);
	}
	object->unkD8 = 0;
	object->unkDC = itemboxScaleReset;
}
