// EventScript::startEventMessage (the PS2 build's name): it looks the subtitle
// `id` of the running event up in the language's table, which ends with a
// negative event number, and shows it for `time`; none shows otherwise.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

void EventScript::startEventMessage(u16 id, s16 time)
{
	s32 i       = 0;
	unk48       = 0;
	messageText = NULL;
	for (; subtitles[i].event >= 0; i++) {
		if (scriptData.unk000C == subtitles[i].event && id == subtitles[i].id) {
			unk48       = time;
			messageText = subtitles[i].text;
			return;
		}
	}
}
