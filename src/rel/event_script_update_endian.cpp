// UpdateEndianandOthers (the PS2 build's name), the event hook in slot 6 of
// main's table (set by EventScript's constructor): with a script it refreshes
// the manager's table in the script data and byte-swaps the data's words and
// halfwords for main.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

void ConvertU32Array(u8* data, s32 size);
void ConvertU16Array(u8* data, s32 size);

s32 UpdateEndianandOthers()
{
	if (lbl_8042C6E0 != NULL) {
		memcpy(EventScript::scriptData.info, lbl_8042C6E4->objects, 0x140);
		ConvertU32Array((u8*)&EventScript::scriptData, 0x150);
		ConvertU16Array(EventScript::scriptData.halves, 0x2000);
		ConvertU16Array(EventScript::scriptData.halves2, 0x8C00);
		ConvertU32Array(EventScript::scriptData.words, 0x38);
		return 1;
	}
	return 0;
}
