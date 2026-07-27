#include "types.h"

// Three queries over one group's object list, used to decide whether a group
// of switches has been completed.
//
// The claim is .text 0x2FD0 to 0x3170. The run is the same in all thirteen
// stage modules that share the engine core. The adjustor thunk at 0x2FC8 just
// before is not included: it tail calls, which is not something the compiler
// emits from C.
//
// All three walk the same list and look at the same three fields, so they only
// differ in what they accept. A node is only interesting when its class is one
// of the four switch kinds; everything else in the group is skipped. An
// interesting node points at a target, and the target carries the state.
//
// The manager keeps one list head per group, and the group number arrives as a
// byte, so the index is masked before it is scaled.

typedef struct Target {
	u8 unk0[0x10]; // 0x00
	s32 state;     // 0x10
} Target;

typedef struct Node {
	u8 unk0[0x28];     // 0x00
	u16 kind;          // 0x28
	u8 unk2A[0x6];     // 0x2A
	Target* target;    // 0x30
	u8 unk34[0x4];     // 0x34
	struct Node* next; // 0x38
} Node;

typedef struct Manager {
	u8 unk0[0x30];   // 0x00
	Node* groups[1]; // 0x30
} Manager;

extern "C" Manager* lbl_8042C298;

// Every switch in the group has a target, and every target is at state two.
// An empty group is a failure rather than a trivial success.
extern "C" s32 objGroupAllSet(u8 group)
{
	u16 kind;
	Node* node;
	Node* head = lbl_8042C298->groups[group];

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
			if (target->state != 2) {
				return 0;
			}
		}
		node = node->next;
	}
	return 1;
}

// The same walk, but any non zero state counts. An empty group is again a
// failure.
extern "C" s32 objGroupAllActive(u8 group)
{
	u16 kind;
	Node* node;
	Node* head = lbl_8042C298->groups[group];

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

// The complement: nothing in the group is active. A switch without a target
// cannot be active, so it is skipped rather than rejected, and an empty group
// succeeds.
extern "C" s32 objGroupNoneActive(u8 group)
{
	u16 kind;
	Node* node = lbl_8042C298->groups[group];

	while (node != NULL) {
		kind = node->kind;
		if (kind == 5 || (u16)(kind - 6) <= 1 || kind == 0x1104) {
			Target* target = node->target;

			if (target != NULL && target->state != 0) {
				return 0;
			}
		}
		node = node->next;
	}
	return 1;
}
