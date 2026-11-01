#include "types.h"

// A debug check of the event system's frame trees (eventCheckHierarchy here;
// the PS2 build has no such function), the same in the thirteen stage modules
// that share the engine core: under a rule line, it walks the given frame or
// the object's own (eventDumpFrame, still assembly, counts them into
// eventFrameCount and prints each), and reports the count against the
// object's node count, with the hierarchy's node count when there is one. It
// answers whether the counts agree; with no frame at all it only reports.

typedef struct EventFrameCheck {
	u8 unk00[0x4];
	s32 nodes; // 0x04
	u8 unk08[0xC];
	void* frame; // 0x14
	u8 unk18[0x8];
	void** hierarchy; // 0x20
} EventFrameCheck;

extern "C" s32 eventFrameCount;
extern "C" s32 eventFrameDepth;
extern "C" char eventCheckRule[];
extern "C" char eventCheckNullAnimFormat[];
extern "C" char eventCheckNullFormat[];
extern "C" char eventCheckAnimFormat[];
extern "C" char eventCheckNodeFormat[];

extern "C" void OSReport(const char* format, ...);
extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" s32 fn_8020C624(void* hierarchy);
extern "C" void eventDumpFrame(EventFrameCheck* check, void* frame);

extern "C" u8 eventCheckHierarchy(
    EventFrameCheck* check, void* frame, void* hierarchy, const char* name)
{
	char line[256];

	OSReport(eventCheckRule);
	eventFrameDepth = 0;
	eventFrameCount = 1;
	if (hierarchy == NULL) {
		hierarchy = *check->hierarchy;
	}
	if (frame != NULL) {
		eventDumpFrame(check, frame);
	} else if (check->frame != NULL) {
		eventDumpFrame(check, check->frame);
	} else {
		if (hierarchy != NULL) {
			sprintf(line, eventCheckNullAnimFormat, name, eventFrameCount, check->nodes,
			    fn_8020C624(hierarchy));
		} else {
			sprintf(line, eventCheckNullFormat, name, eventFrameCount, check->nodes);
		}
		OSReport(line);
		return 0;
	}
	if (hierarchy != NULL) {
		sprintf(line, eventCheckAnimFormat, name, eventFrameCount, check->nodes,
		    fn_8020C624(hierarchy));
	} else {
		sprintf(line, eventCheckNodeFormat, name, eventFrameCount, check->nodes);
	}
	OSReport(line);
	return eventFrameCount == check->nodes;
}
