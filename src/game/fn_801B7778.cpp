// Frees a container with the engine memory function: its buffer at +0xC, every node of the chain
// starting at +0x4 (linked through +0x8) and then the container itself. A null container is
// ignored. Field names are UNKNOWN.
#include "game/rw_engine.h"

struct Node801B7778 {
	u8 pad0[0x8];
	Node801B7778* next; // 0x8
};

struct Container801B7778 {
	s32 f0;
	Node801B7778* first; // 0x4
	s32 f8;
	void* buffer; // 0xC
};

extern "C" {
void fn_801B7778(Container801B7778* container)
{
	if (container != 0) {
		Node801B7778* node;
		if (container->buffer != 0) {
			lbl_8042C9A4->rwfree(container->buffer);
			container->buffer = 0;
		}
		node = container->first;
		while (node != 0) {
			Node801B7778* next = node->next;
			if (node != 0) {
				lbl_8042C9A4->rwfree(node);
			}
			node = next;
		}
		lbl_8042C9A4->rwfree(container);
	}
}
}
