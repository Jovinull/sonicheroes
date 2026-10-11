// EventManager::loadEventToAMem (the PS2 build's name): it copies the event's
// scene files into ARAM, one EventObject each, keeping the length of each
// scene's camera motion (its first .TMB from file 2 on). It stops after three
// scene numbers in a row with no file and answers how many it kept.

#include "src/rel/event_manager_class.inc"

struct NJS_MOTION {
	void* mdata; // 0x00
	s32 nbFrame; // 0x04
};

// Main's allocator table, as in src/game/Memory.cpp.
struct MemoryAllocator {
	u8 pad[0x134];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;
extern "C" char eventSceneFormat[];
extern "C" char eventTmbExtension[];
extern "C" void* fn_800D082C(u32 size);
extern "C" void fn_800D06C0(void* source, void* aram, u32 size);
extern "C" char* strstr(const char* string, const char* pattern);

s32 EventManager::loadEventToAMem()
{
	char name[64];
	s32 count  = 0;
	s32 scene  = 0;
	s32 misses = 0;

	memset(objects, 0, sizeof(objects));
	for (;; scene++) {
		file->ReleaseOneFile();
		sprintf(name, eventSceneFormat, unk28, scene);
		if (file->LoadOneFile(name)) {
			objects[count].no    = count;
			objects[count].scene = scene;
			objects[count].aram  = fn_800D082C(file->memInfo.length);
			objects[count].size  = (file->memInfo.length + 0x1F) & ~0x1F;
			fn_800D06C0(file->memInfo.start, objects[count].aram, objects[count].size);
			for (s32 i = 2;; i++) {
				if (strstr(file->CheckFileName(i), eventTmbExtension) != NULL) {
					NJS_MOTION* motion    = file->LoadCameraTmbEx(i, NULL);
					objects[count].frames = motion->nbFrame;
					lbl_8042C9A4->Free(motion);
					break;
				}
			}
			file->ReleaseOneFile();
			misses = 0;
			count++;
		} else {
			misses++;
		}
		if (misses >= 3) {
			break;
		}
	}
	return count;
}
