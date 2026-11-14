// Unlinks `target` from a list (see game/audio_system.h), passes it to fn when given and frees it
// to the audio heap (fn_80205C10). Nothing happens when the node is not in the list.
#include "game/audio_system.h"

extern "C" {
void fn_80205C10(void* p);

void fn_8020641C(PoolListNode* target, PoolListNode** list, void (*fn)(PoolListNode* node))
{
	PoolListNode* prev = *list;
	PoolListNode* node;
	if (prev == target) {
		node = prev->next;
		if (fn != 0) {
			fn(prev);
		}
		fn_80205C10(prev);
		*list = node;
		return;
	}
	for (; prev != 0; prev = node) {
		node = prev->next;
		if (node == 0) {
			return;
		}
		if (node == target) {
			prev->next = node->next;
			if (fn != 0) {
				fn(node);
			}
			fn_80205C10(node);
			return;
		}
	}
}
}
