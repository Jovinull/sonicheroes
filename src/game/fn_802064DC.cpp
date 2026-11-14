// Appends a new zeroed node of `size` bytes, allocated from the audio heap (fn_80205CBC), to a
// list (see game/audio_system.h) and passes it to init when given. Returns the node, or null when
// the heap is full.
#include "game/audio_system.h"

extern "C" {
void* memset(void* dst, int value, unsigned long n);
void* fn_80205CBC(unsigned int size);

PoolListNode* fn_802064DC(unsigned int size, PoolListNode** list, void (*init)(PoolListNode* node))
{
	PoolListNode* last = *list;
	PoolListNode* node = (PoolListNode*)fn_80205CBC(size);
	if (node == 0) {
		return 0;
	}
	memset(node, 0, size);
	if (*list == 0) {
		*list = node;
	} else {
		for (; last->next != 0; last = last->next) {
		}
		last->next = node;
	}
	if (init != 0) {
		init(node);
	}
	return node;
}
}
