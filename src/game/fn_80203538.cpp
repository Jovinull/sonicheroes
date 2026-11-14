// Resolves the context value of a type-12 command for fn_8020366C (HYPOTHESIS): the command's
// depth (word 0x8) selects the base: for depth n > 0 the parent index (0x34) of the entry
// reached by n parent steps from the context entry (fn_8020407C), the context itself for depth 0
// and nothing for depth -1; the offset (word 0xC) is added either as an entry index whose
// value (word 0x8 of fn_8020277C's entry) is used, when the command value (0x4) is not negative,
// or directly. Other depths keep the context. Stores the result and returns the command.
#include "game/free_lists_8040EB50.h"

struct Entry80203538 {
	u8 pad0[0x34];
	s32 parent; // 0x34
};

struct ValueEntry80203538 {
	u8 pad0[0x8];
	s32 value; // 0x8
};

extern "C" {
Entry80203538* fn_8020407C(void* object, s32 index);
ValueEntry80203538* fn_8020277C(void* object, s32 index);

const BufferCommand8040EB50* fn_80203538(
    void* object, const BufferCommand8040EB50* command, s32 context, s32* current)
{
	s32 result = context;
	s32 depth;
	s32 steps;
	Entry80203538* entry;

	if (command->value >= 0) {
		depth = command->word8;
		if (depth > 0) {
			steps = depth - 1;
			entry = fn_8020407C(object, context);
			for (; steps > 0; steps--) {
				entry = fn_8020407C(object, entry->parent);
			}
			ValueEntry80203538* offset = fn_8020277C(object, command->wordC);
			result                     = entry->parent + offset->value;
		} else if (depth == 0) {
			result = context + fn_8020277C(object, command->wordC)->value;
		} else if (depth == -1) {
			result = fn_8020277C(object, command->wordC)->value;
		}
	} else {
		depth = command->word8;
		if (depth > 0) {
			steps = depth - 1;
			entry = fn_8020407C(object, context);
			for (; steps > 0; steps--) {
				entry = fn_8020407C(object, entry->parent);
			}
			result = entry->parent + command->wordC;
		} else if (depth == 0) {
			result = context + command->wordC;
		} else if (depth == -1) {
			result = command->wordC;
		}
	}
	*current = result;
	return command;
}
}
