// EventManager::loadSceneFromAram (the PS2 build's name): if the event's file
// number `object` is kept in ARAM, it allocates a buffer, copies the file back
// into it and hands it to the manager's file reader, answering whether it did.

#include "src/rel/event_manager_class.inc"

// Main's allocator table, as in src/game/Memory.cpp.
struct MemoryAllocator {
	u8 pad[0x134];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;
extern "C" void fn_800D0624(void* buffer, void* aram, u32 size);

s32 EventManager::loadSceneFromAram(s32 object)
{
	EventObject* file = &objects[object];

	if (file->aram != NULL) {
		void* buffer = lbl_8042C9A4->Alloc(file->size);
		fn_800D0624(buffer, file->aram, file->size);
		this->file->SetOneFile(buffer, file->size, 1);
		return 1;
	}
	return 0;
}
