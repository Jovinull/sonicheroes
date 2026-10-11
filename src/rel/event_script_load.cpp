// EventScript::LoadScript (the PS2 build's name): it loads the event's script
// for the game's language (the byte at 0x13 picks the file's suffix) into the
// script data, remembers the stream playing now, byte-swaps the data when the
// file was read (UpdateEndianandOthers, inlined), loads the language's font
// for the message board, saves main's light table and puts the script's in its
// place, and keeps the event's first voice. It answers what the file read did.

#define EVENT_SCRIPT_SOURCE
#define EVENT_UPDATE_ENDIAN_INLINE inline

#include "src/rel/event_manager_class.inc"

struct REGLIGHT_STRUCT;

class CLIGHT
{
public:
	void AssignData(REGLIGHT_STRUCT* data);
};

class EventVoiceList
{
public:
	s32 GetTopVoiceOffset(s32 eventNumber);
};

extern "C" u8* lbl_8042C180;
extern "C" u8 lbl_802D5E80[];
extern "C" EventVoiceList lbl_8042C6E8;
extern "C" char eventScriptFormat[];
extern "C" char* eventScriptSuffixes[];
extern "C" char eventFontFormat[];
extern "C" char* eventFontSuffixes[];
extern "C" char* fn_800CC300(void);
extern "C" s32 fn_80042048(const char* name, void* buffer);
extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" char* strcpy(char* destination, const char* source);

s32 EventScript::LoadScript(s32 event)
{
	char name[256];

	sprintf(name, eventScriptFormat, event, eventScriptSuffixes[(s8)lbl_8042C180[0x13]]);
	memset(&scriptData, 0, 0xB184);
	if (fn_800CC300() != NULL) {
		strcpy(bgmName, fn_800CC300());
	} else {
		bgmName[0] = 0;
	}
	s32 result = fn_80042048(name, &scriptData);
	if (result != 0) {
		UpdateEndianandOthers();
	}
	if (message != NULL) {
		sprintf(name, eventFontFormat, event, eventFontSuffixes[(s8)lbl_8042C180[0x13]]);
		message->LoadFontFile(name);
	}
	unk48 = 0;
	memcpy(saveLightBuffer, lbl_802D5E80 + 0x20, 0x340);
	((CLIGHT*)lbl_802D5E80)->AssignData((REGLIGHT_STRUCT*)scriptData.light);
	voiceOffset = lbl_8042C6E8.GetTopVoiceOffset(event);
	return result;
}
