// Empties a list (see game/audio_system.h): each node is passed to fn, when given, and then
// freed to the audio heap (fn_80205C10).
#include "game/audio_system.h"

extern "C" {
void fn_80205C10(void* p);

void fn_802063A0(PoolListNode** list, void (*fn)(PoolListNode* node))
{
	PoolListNode* next;
	PoolListNode* node;
	while ((node = *list) != 0) {
		next = node->next;
		if (fn != 0) {
			fn(node);
		}
		fn_80205C10(node);
		*list = next;
	}
}
}
