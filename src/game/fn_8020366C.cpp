// Appends commands to a buffer of an fn_802038AC object (HYPOTHESIS): fails (null) when they would
// not fit in its 64 slots; a type-12 command is expanded by fn_80203538 instead of being copied
// (failing when that fails), every other command is copied and its value at 0x4 is resolved: a
// negative value takes the current context (which fn_80203538 may update), otherwise the word at
// 0x8 of the object's entry with that index (fn_8020277C). Returns the buffer.
// NonMatching: the retail copy reuses the switch value from r3 and moves the command in word
// pairs; ours keeps the switch value in r0 (7 words differ).
#include "game/free_lists_8040EB50.h"

struct Entry8020366C {
	u8 pad0[0x8];
	s32 value; // 0x8
};

extern "C" {
void* fn_80203538(void* object, BufferCommand8040EB50* command, s32 context, s32* current);
Entry8020366C* fn_8020277C(void* object, s32 index);

Buffer8040EB50* fn_8020366C(
    void* object, Buffer8040EB50* buffer, BufferCommand8040EB50* commands, s32 count, s32 context)
{
	s32 current;
	s32 i;
	BufferCommand8040EB50* out;
	s32 used;

	used = buffer->count;
	if (used + count > 64) {
		return 0;
	}
	current = context;
	out     = &buffer->commands[used];
	for (i = 0; i < count; commands++, i++) {
		switch (commands->type) {
			case 12:
				if (!fn_80203538(object, commands, context, &current)) {
					return 0;
				}
				break;
			default:
				*out = *commands;
				buffer->count++;
				if (out->value < 0) {
					out->value = current;
				} else {
					out->value = fn_8020277C(object, out->value)->value;
				}
				out++;
				break;
		}
	}
	return buffer;
}
}
