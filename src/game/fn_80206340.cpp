// Returns the first node of a list (see game/audio_system.h) for which pred returns 0, or null.
#include "game/audio_system.h"

extern "C" {
PoolListNode* fn_80206340(PoolListNode** list, int (*pred)(PoolListNode* node))
{
	PoolListNode* node;
	for (node = *list; node != 0; node = node->next) {
		if (pred(node) == 0) {
			break;
		}
	}
	return node;
}
}
