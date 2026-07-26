#include "types.h"

// TObjSpring, as far as it has been carved: the contact pass that launches
// whatever is touching the spring, the two display hooks after it, and the
// class's vtable.
//
// The claim is .text 0x88C to 0xC70, the five constants in .rodata, and the
// class's vtable together with the jump table in .data. That is an island
// inside TObjSpring's translation unit rather than the whole of it: the
// constants and the table are read here and nowhere else in the module, which
// is what makes the run cuttable on its own. Exec, the constructor and the
// destructor are still assembly, and so is the clamp at 0x16CC, which sits far
// enough away to be its own island in rel/spring_clamp.c.
//
// Disp tints the spring: it recomputes a colour once per tick and writes it
// into the material the module keeps a pointer to, 192 plus 63 times a wave, so
// the ring pulses between 129 and 255. The tick it last ran on is cached beside
// that pointer, which is what the compare at the top is. Both of those live in
// the module's .bss and are reached as externals rather than claimed: they are
// not next to each other, so no single range covers them.
//
// The code is the same in thirteen of the fourteen stage modules; stage40D is a
// different revision of the source and is left out, as everywhere else. The
// addresses of the two data blocks move from module to module, so each one's
// splits.txt carries its own; only .text and .rodata line up everywhere, and
// stage13D moves the .rodata too.
//
// The jump table is not written out below: the compiler builds it for the
// switch at the end. Twelve entries pointing at three bodies, so the twelve
// player slots are read modulo three and the sound ids 0x1000, 0x1001 and
// 0x1002 are the speed, power and fly notes. The case order comes off the table
// rather than being guessed: the offsets put the speed body first, then power,
// then fly.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

// The node the collision iterator hands back, and what it was carrying.
typedef struct Contact {
	u8 unk0[0x78]; // 0x00
	void* owner;   // 0x78
} Contact;

typedef struct Node {
	u8 unk0[0x4];     // 0x00
	Contact* contact; // 0x04
} Node;

typedef struct Character {
	u8 unk0[0x3A];  // 0x00
	s8 lead;        // 0x3A
	u8 unk3B[0xD5]; // 0x3B
	s8 slots[0x3C]; // 0x110
	s8 unk14C;      // 0x14C
} Character;

typedef struct Actor {
	u8 unk0[0x1];    // 0x00
	s8 kind;         // 0x01
	u8 unk2[0x256];  // 0x02
	Character* team; // 0x258
} Actor;

typedef struct Spring {
	u8 unk0[0x30];  // 0x00
	u8 list[0x8];   // 0x30
	u16 flags;      // 0x38
	u8 unk3A[0x7E]; // 0x3A
	s32 state;      // 0xB8
	s8 hits[8];     // 0xBC
	s16 unkC4;      // 0xC4
	u8 unkC6[0xE];  // 0xC6
	u8 unkD4[0xC];  // 0xD4
	s32 unkE0;      // 0xE0
	f32 unkE4;      // 0xE4
	u8 unkE8[0x8];  // 0xE8
	f32 height;     // 0xF0
	u8 unkF4[0x4];  // 0xF4
	Node* unkF8;    // 0xF8
} Spring;

typedef struct Clock {
	u8 unk0[0x30]; // 0x00
	s32 tick;      // 0x30
} Clock;

extern "C" Clock* lbl_8042C180;
extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" void* lbl_802AD070[];
extern "C" Actor* lbl_802AD0D0[];

extern "C" void fn_8001F674(s32 a, s32 b, s32 c, s32 d);
extern "C" Node* fn_80020BD8(u8* list, s32 kind);
extern "C" Node* fn_800211A8(u8* list);
extern "C" void fn_80021824(u8* list);
extern "C" s32 fn_80041B64(void* owner);
extern "C" void fn_8005F3F0(s32* state, s32 player, s32 b, const Vec3* impulse, s32 c);
extern "C" s32 fn_80091F54(Character* team, s32 player);
extern "C" s32 fn_80091FAC(Character* team);
extern "C" s32 fn_800927D0(Character* team, s32 slot);
extern "C" s32 fn_800AB35C(void* actor);
extern "C" void fn_800B52E8(void* handle, s32 sound, s32 a, s32 b);
extern "C" void fn_800E0CC8(s32 player, f32 height, u8* a, s16 b);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void* fn_8019E8EC(void* a);
extern "C" void fn_8019941C(Vec3* out, const Vec3* in, s32 count, void* matrix);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" u8* springMaterial;
extern "C" s32 springTick;

// TObjSpring's vtable. It is claimed here rather than left to the module for a
// mechanical reason: a compiled object's .data is always eight byte aligned, so
// a claim has to start on an eight byte boundary, and the jump table sits at
// four. The vtable ends exactly where the table begins and does start on eight,
// so the two are claimed together and the compiler lays them out in that order.
//
// Nine of the fifteen slots are still assembly and are reached by the names
// each module's symbols.txt gives them. Four of those, the ones between PDisp
// and Render, are the base class defaults both sample objects point at as well.
extern "C" void springDtor(void);
extern "C" void springExec(void);
extern "C" void springDisp(Spring* object);
extern "C" void springTDisp(Spring* object);
extern "C" void objDefaultPDisp(void);
extern "C" void objDefaultImmAftSetRaster(void);
extern "C" void objDefaultDebug(void);
extern "C" void fn_80017854(void);
extern "C" void objDefaultRender(void);
extern "C" void springThunk(void);
extern "C" void springClamp(void* object, void* frame);

extern "C" void* springVtable[] = {
	NULL,
	NULL,
	(void*)springDtor,
	(void*)springExec,
	(void*)springDisp,
	(void*)springTDisp,
	(void*)objDefaultPDisp,
	(void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug,
	(void*)fn_80017854,
	(void*)objDefaultRender,
	NULL,
	NULL,
	(void*)springThunk,
	(void*)springClamp,
};

extern "C" void springLaunch(Spring* object)
{
	Vec3 world;
	Vec3 impulse;
	Vec3 out;
	Node* node;
	Contact* contact;
	s32 player;
	s32 partner;
	Character* team;

	fn_80021824(lbl_8042C1A4);
	node    = fn_80020BD8(object->list, 0x13);
	contact = node != NULL ? node->contact : NULL;
	if (contact != NULL) {
		object->flags &= ~0x40;
		return;
	}

	object->flags |= 0x40;
	fn_80021824(lbl_8042C1A4);

	while (node = fn_800211A8(object->list), contact = node != NULL ? node->contact : NULL,
	    contact != NULL) {
		player = fn_80041B64(contact->owner);
		if (object->hits[player] > 0) {
			continue;
		}

		world.z = 0.0f;
		world.x = 0.0f;
		world.y = 5.0f + object->height;

		fn_8019941C(&out, &world, 1, fn_8019E8EC(object->unkF8->contact));

		impulse.x = out.x;
		impulse.y = out.y;
		impulse.z = out.z;

		team = lbl_802AD0D0[player]->team;
		if (fn_80091FAC(team) == 2 && fn_80091F54(team, player) != 0) {
			player = team->slots[team->lead];

			partner = team->slots[fn_800927D0(team, 1)];
			if (fn_800AB35C(lbl_802AD070[partner]) == 1) {
				object->hits[partner] = 9;
			}

			partner = team->slots[fn_800927D0(team, 2)];
			if (fn_800AB35C(lbl_802AD070[partner]) == 1) {
				object->hits[partner] = 9;
			}
		}

		fn_8005F3F0(&object->state, player, 0, &impulse, 0);
		fn_800E0CC8(player, world.y, object->unkD4, object->unkC4);

		object->hits[player] = 9;
		object->unkE0        = 0;
		object->unkE4        = 0.5f;
		object->state        = 2;
		fn_8001F674(team->unk14C, 4, 0xF, 0);

		switch (lbl_802AD0D0[player]->kind) {
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

extern "C" void springTDisp(Spring* object) { }

extern "C" void springDisp(Spring* object)
{
	s32 tick = lbl_8042C180->tick;
	u8* material;
	u8 level;
	f32 wave;

	if (springTick == tick) {
		return;
	}

	wave     = fn_800D7B00(tick << 9);
	level    = (u8)(192.0f + 63.0f * wave);
	material = springMaterial;

	material[4] = level;
	material[5] = level;
	material[6] = level;
	material[7] = 0xFF;

	springTick = tick;
}
