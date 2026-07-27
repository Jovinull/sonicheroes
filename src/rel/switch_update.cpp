#include "types.h"

// The state machine of TObjSwitch, called once a frame from the class Exec.
//
// The claim is .text 0x321C to 0x3940. The run is the same in all thirteen
// stage modules that share the engine core.
//
// The frame starts by asking the collision world three questions about the
// switch's own collider: two for specific hit kinds, one for anything at all.
// A hit of either specific kind means something is already being handled and
// the frame is dropped; otherwise the third answer decides whether the switch
// counts as pressed this frame.
//
// From there the placement record's type picks one of four behaviours, and the
// bodies are emitted in the order the original wrote them, which is 0, 1, 3, 2:
//
//   0  a toggle, and only on the frame the press begins
//   1  a hold: state follows the press directly
//   3  a hold that also completes when every switch in the group is active
//   2  a latch: presses set it, nothing clears it
//
// The tail publishes the state on the placement record's target, so that the
// group queries in rel/obj_group_query.c see it, and plays a sound when the
// state actually changed. Type 3 and the flagged variant get their own sound.
//
// The three helpers are inline because the original had them earlier in the
// same translation unit and the compiler folded every call. objGroupAllActive
// is the same function this module also keeps out of line at 0x3064, so the
// copy here is marked static and never emitted on its own.

typedef struct Target {
	u8 unk0[0x10]; // 0x00
	s32 state;     // 0x10
} Target;

typedef struct SetEntry {
	u8 unk0[0x18];         // 0x00
	u32 flags;             // 0x18
	u8 unk1C[0xC];         // 0x1C
	u16 kind;              // 0x28
	u8 group;              // 0x2A
	u8 unk2B[0x1];         // 0x2B
	u8 unk2C[0x4];         // 0x2C
	Target* target;        // 0x30
	u8 unk34[0x4];         // 0x34
	struct SetEntry* next; // 0x38
} SetEntry;

typedef struct Manager {
	u8 unk0[0x30];       // 0x00
	SetEntry* groups[1]; // 0x30
} Manager;

typedef struct Hit {
	u8 unk0[0x4]; // 0x00
	u32 count;    // 0x04
} Hit;

typedef struct Draw {
	s32 mode; // 0x00
} Draw;

typedef struct Collider {
	u8 unk0[0x8C]; // 0x00
} Collider;

typedef struct Switch {
	u8 unk0[0x28];      // 0x00
	SetEntry* entry;    // 0x28
	u8 unk2C[0x4];      // 0x2C
	Collider collision; // 0x30
	s32 state;          // 0xBC
	s8 type;            // 0xC0
	s8 pressed;         // 0xC1
	u8 unkC2[0x26];     // 0xC2
	s32 loud;           // 0xE8
	u8 unkEC[0x4];      // 0xEC
	void* model0;       // 0xF0
	u8 unkF4[0x4];      // 0xF4
	void* model1;       // 0xF8
} Switch;

extern "C" Manager* lbl_8042C298;
extern "C" void* lbl_8042C388;
extern "C" u8 lbl_8042C1A4[];

extern "C" void fn_80021824(void* world);
extern "C" Hit* fn_80020BD8(Collider* collision, s32 kind);
extern "C" Hit* fn_800211A8(Collider* collision);
extern "C" Draw* fn_8005F490(void* model);
extern "C" void fn_800B52E8(void* handle, s32 sound, s32 a, s32 b);

static inline u32 switchHitCount(Hit* hit)
{
	if (hit != NULL) {
		return hit->count;
	}
	return 0;
}

// State zero draws with the palette the placement record asks for; the two
// pressed states share the one lit palette.
static inline void switchApplyDrawMode(Switch* object)
{
	Draw* draw;

	switch (object->state) {
		case 0:
			draw       = fn_8005F490(object->model0);
			draw->mode = ((object->entry->flags & 0x1C0000) >> 18) + 4;
			draw       = fn_8005F490(object->model1);
			draw->mode = ((object->entry->flags & 0x1C0000) >> 18) + 4;
			break;
		case 1:
		case 2:
			draw       = fn_8005F490(object->model0);
			draw->mode = 0x10;
			draw       = fn_8005F490(object->model1);
			draw->mode = 0x10;
			break;
	}
}

static inline s32 objGroupAllActive(u8 group)
{
	u16 kind;
	SetEntry* node;
	SetEntry* head = lbl_8042C298->groups[group];

	node = head;
	if (head == NULL) {
		return 0;
	}

	while (node != NULL) {
		kind = node->kind;
		if (kind == 5 || (u16)(kind - 6) <= 1 || kind == 0x1104) {
			Target* target = node->target;

			if (target == NULL) {
				return 0;
			}
			if (target->state == 0) {
				return 0;
			}
		}
		node = node->next;
	}
	return 1;
}

extern "C" void switchUpdate(Switch* object)
{
	s32 previous;
	s32 state;

	previous = object->pressed;

	fn_80021824(lbl_8042C1A4);
	if (switchHitCount(fn_80020BD8(&object->collision, 1)) != 0) {
		return;
	}

	fn_80021824(lbl_8042C1A4);
	if (switchHitCount(fn_80020BD8(&object->collision, 0x13)) != 0) {
		return;
	}

	fn_80021824(lbl_8042C1A4);
	if (switchHitCount(fn_800211A8(&object->collision)) != 0) {
		object->pressed = 1;
	} else {
		object->pressed = 0;
	}

	state = object->state;

	switch (object->type) {
		case 0:
			if (object->pressed == 1 && previous == 0) {
				if (state == 0) {
					object->state = 2;
					switchApplyDrawMode(object);
				} else {
					object->state = 0;
					switchApplyDrawMode(object);
				}
			}
			break;

		case 1:
			if (object->pressed == 1) {
				object->state = 2;
				switchApplyDrawMode(object);
			} else {
				object->state = 0;
				switchApplyDrawMode(object);
			}
			break;

		case 3:
			if (object->pressed == 1) {
				object->state = 1;
				switchApplyDrawMode(object);
			} else {
				object->state = 0;
				switchApplyDrawMode(object);
			}
			if (objGroupAllActive(object->entry->group)) {
				object->state = 2;
				switchApplyDrawMode(object);
			}
			break;

		case 2:
			if (object->pressed == 1) {
				object->state = 2;
				switchApplyDrawMode(object);
			}
			break;
	}

	if (object->entry->target != NULL) {
		object->entry->target->state = object->state;
	}

	if (object->state == state) {
		return;
	}

	if (object->state == 1) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1007, 0, 0);
		}
		return;
	}
	if (object->state != 2) {
		return;
	}

	if (object->type == 3 || object->loud != 0) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1064, 0, 0);
		}
	} else {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1007, 0, 0);
		}
	}
}
