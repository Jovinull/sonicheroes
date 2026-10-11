// EventScript::ScriptInit (the PS2 build's name), run by _eventRewind: with a
// script it resets the script's state and picks the event subtitles for the
// game's language (the byte at 0x13; table 0 is Japanese in Shift JIS, table 1
// English).

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" u8* lbl_8042C180;
extern "C" u8 eventSubtitles0[];
extern "C" u8 eventSubtitles1[];
extern "C" u8 eventSubtitles2[];
extern "C" u8 eventSubtitles3[];
extern "C" u8 eventSubtitles4[];
extern "C" u8 eventSubtitles5[];
extern "C" u8 eventSubtitles6[];

void EventScript::ScriptInit()
{
	if (lbl_8042C6E0 != NULL) {
		unk00 = -1;
		memset(unk04, 0, sizeof(unk04));
		unk3C = 0x1000;
		switch ((s8)lbl_8042C180[0x13]) {
			case 0:
				subtitles = eventSubtitles0;
				break;
			case 1:
				subtitles = eventSubtitles1;
				break;
			case 2:
				subtitles = eventSubtitles2;
				break;
			case 3:
				subtitles = eventSubtitles3;
				break;
			case 4:
				subtitles = eventSubtitles4;
				break;
			case 5:
				subtitles = eventSubtitles5;
				break;
			case 6:
				subtitles = eventSubtitles6;
				break;
		}
	}
}
