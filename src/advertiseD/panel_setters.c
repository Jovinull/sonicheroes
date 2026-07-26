#include "types.h"

// The three setters that change one field of the panel and redraw it, and the
// walk that clears the highlight from every child of the cursor.
//
// The translation unit runs from fn_1_9BB0 at 0x9BB0 to the end of fn_1_9C30
// at 0x9CA4. The only private data it reaches is the list at .data 0x11A4,
// which is left to the module and referenced here rather than emitted.

typedef struct Node {
	u8 unk0[0xC];   // 0x00
	Node* next;     // 0x0C
	void* unk10;    // 0x10
	Node* children; // 0x14
} Node;

typedef struct Panel {
	u8 unk0[0x224]; // 0x000
	s32 slot;       // 0x224
	s32 mode;       // 0x228
	s32 page;       // 0x22C
	void* cursor;   // 0x230
} Panel;

extern "C" void* lbl_1_data_11A4;

extern "C" s32 fn_1_86B0(Node* node, void* name);
extern "C" void fn_1_55A4(Node* node, s32 value);
extern "C" void fn_1_922C(Panel* panel);
extern "C" void fn_1_945C(Panel* panel);

extern "C" void fn_1_9BB0(Panel* panel, s32 page)
{
	panel->page = page;
	fn_1_945C(panel);
}

extern "C" void fn_1_9BD4(Panel* panel, s32 slot)
{
	panel->slot = slot;
	fn_1_945C(panel);
}

extern "C" void fn_1_9BF8(Panel* panel, s32 mode)
{
	panel->mode = mode;
	fn_1_922C(panel);
	fn_1_945C(panel);
}

extern "C" void fn_1_9C30(Panel* panel)
{
	Node* node;
	void** name;

	if (panel->cursor != NULL) {
		node = ((Node*)panel->cursor)->children;
		name = &lbl_1_data_11A4;
		while (node != NULL) {
			if (fn_1_86B0(node, *name) != 0) {
				fn_1_55A4(node, 1);
			}
			node = node->next;
		}
	}
}
