#include "types.h"

// TObjPropeller::checkCollision (the PS2 build's name, by its place in the
// PS2 order; propellerCheckCollision here). A propeller too small to grab
// (size below 1) only clears its collision. At rest (state 0) a touch of kind
// 10 starts it (state 1, 600 frames; flagged when the game is paused). Started,
// the first player that touches it hangs on by the team's leader (state 2,
// action 0x15/0x3D), whose team is kept. Carrying (state 2), a hit of the
// hook against the ground makes the team react and sets the drop speed from
// the path the propeller follows. Then the collision follows the propeller.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PropellerPathEntry {
	u8 unk0[0x8];
	f32 speed; // 0x8
} PropellerPathEntry;

typedef struct PropellerFrame {
	u8 unk00[0x30];
	s16* path; // 0x30
} PropellerFrame;

typedef struct PropellerHit {
	u8 unk00[0x78];
	void* owner; // 0x78
} PropellerHit;

typedef struct PropellerHitLink {
	u8 unk0[0x4];
	PropellerHit* colli; // 0x04
} PropellerHitLink;

typedef struct PropellerTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4]; // 0x110
	u8 unk114[0x38];
	s8 index; // 0x14C
} PropellerTeam;

typedef struct PropellerPlayer {
	u8 unk000[0x258];
	PropellerTeam* team; // 0x258
	u8 unk25C[0x2];      // 0x25C
	s8 teamNo;           // 0x25E
} PropellerPlayer;

typedef struct Propeller {
	u8 unk00[0x28];
	PropellerFrame* frame; // 0x28, the set object's
	u8 unk2C[0x4];         // 0x2C
	u8 colli[0x60];        // 0x30 (C_COLLI)
	RwV3d colliPos;        // 0x90
	s32 colliAng[3];       // 0x9C
	u8 unkA8[0x4];         // 0xA8
	RwV3d colliPrePos;     // 0xAC
	s32 state;             // 0xB8
	s8 holder;             // 0xBC
	u8 unkBD[0x3];         // 0xBD
	RwV3d pos;             // 0xC0
	s32 ang[3];            // 0xCC
	f32 size;              // 0xD8
	u8 unkDC[0x20];        // 0xDC
	RwV3d hook;            // 0xFC
	u8 unk108[0x38];       // 0x108
	f32 dropSpeed;         // 0x140
	u8 unk144[0x8];        // 0x144
	s32 time;              // 0x14C
	u8 unk150[0xC];        // 0x150
	s32 paused;            // 0x15C
	s32 team;              // 0x160
} Propeller;

struct ColliPolyLinearList;

extern "C" u8 lbl_8042C1A4[];
extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C150;
extern "C" PropellerPlayer* lbl_802AD0D0[];
extern "C" PropellerTeam* lbl_80303DC8[];
extern "C" PropellerPathEntry propellerPathEntries[];
extern "C" f32 propellerHookRadius;
extern "C" const f32 propellerOne[1];
extern "C" const f32 propellerDropScale[1];

extern "C" void ClearInfo__7C_COLLIFv(void* colli);
extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void fn_80021824(void* collision);
extern "C" void* fn_80020BD8(void* colli, s32 kind);
extern "C" PropellerHitLink* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(void* owner);
extern "C" void fn_800E1208(s32 player, s32 action, s32 arg);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg);
extern "C" ColliPolyLinearList* DetectSphereCollisionWithPolygons__6OCTREEFP5RwV3dfPFP8POLYDATA_i(
    void* octree, RwV3d* center, f32 radius, void* callback);
extern "C" void __dt__19ColliPolyLinearListFv(ColliPolyLinearList* list, s32 flags);

// the next collision that touched the propeller, if any
static inline PropellerHit* propellerNextHit(Propeller* object)
{
	PropellerHitLink* link = fn_800211A8(object->colli);

	return link != NULL ? link->colli : NULL;
}

extern "C" void propellerCheckCollision(Propeller* object)
{
	s16* path = object->frame->path;

	switch (object->state) {
		case 0:
			if (object->size < propellerOne[0]) {
				ClearInfo__7C_COLLIFv(object->colli);
				return;
			}
			fn_80021824(lbl_8042C1A4);
			while (fn_80020BD8(object->colli, 10) != NULL) {
				object->state = 1;
				object->time  = 600;
				if ((s8)lbl_8042C180[0x1F] != 0) {
					object->paused = 1;
				}
				break;
			}
			break;
		case 1: {
			PropellerHit* hit;

			fn_80021824(lbl_8042C1A4);
			while ((hit = propellerNextHit(object)) != NULL) {
				s32 player = fn_80041B64(hit->owner);
				if (player == -1) {
					continue;
				}
				PropellerTeam* team = lbl_802AD0D0[player]->team;
				s32 leader          = team->members[team->leader];
				object->state       = 2;
				object->team        = lbl_802AD0D0[leader]->teamNo;
				fn_800E1208(leader, 0x15, 0x3D);
				object->holder = leader;
				break;
			}
			break;
		}
		case 2: {
			ColliPolyLinearList* list
			    = DetectSphereCollisionWithPolygons__6OCTREEFP5RwV3dfPFP8POLYDATA_i(
			        lbl_8042C150, &object->hook, propellerHookRadius, NULL);
			if (list != NULL) {
				if (object->team >= 0 && lbl_80303DC8[object->team] != NULL) {
					fn_8001F674(lbl_80303DC8[object->team]->index, 4, 0xF, 0);
				}
				object->dropSpeed = propellerDropScale[0] * propellerPathEntries[*path].speed;
				__dt__19ColliPolyLinearListFv(list, 1);
			}
			break;
		}
	}
	object->colliPrePos = object->colliPos;
	object->colliPos    = object->pos;
	object->colliAng[0] = object->ang[0];
	object->colliAng[1] = object->ang[1];
	object->colliAng[2] = object->ang[2];
	Entry__7C_COLLIFv(object->colli);
}
