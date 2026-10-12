// EventManager::releaseScene (the PS2 build's name): with a scene loaded (the
// state 1 to 3), it releases the players' slots that `scenes` does not keep
// (all of them with NULL): their models leave the world (removeClump) and are
// destroyed with their animations, the eyelids too, and the body gets its own
// hierarchy back (getPlayerBodyClump, inlined). With NULL it also releases the
// extra objects (releaseSceneExtObjs, inlined) and frees the scene's buffer.
// It answers whether a scene was loaded.

#include "src/rel/event_manager_class.inc"

class HAnimClass
{
public:
	void SetHierarchyForAtomic(struct RpClump* clump, RpHAnimHierarchy* hierarchy);
};

// Main's allocator table, as in src/game/Memory.cpp.
struct MemoryAllocator {
	u8 pad[0x134];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern HAnimClass HAnim;
extern MemoryAllocator* lbl_8042C9A4;
extern "C" void fn_8013BD74(void* object);
extern "C" void fn_8013EEE0(RpHAnimHierarchy* hierarchy);
extern "C" void fn_8013F3A4(RpHAnimHierarchy* hierarchy);

s32 EventManager::releaseScene(s32* scenes)
{
	switch (unk3C) {
		case 1:
		case 2:
		case 3:
			for (s32 i = 0; i < 14; i++) {
				if (scenes != NULL && scenes[i] != 0) {
					continue;
				}
				SceneMemPlayerObj* player = (SceneMemPlayerObj*)&slots[i];
				if (player->body != NULL) {
					removeClump(player->body);
					fn_80150958(player->body);
				}
				if (player->bodyAnim != NULL) {
					fn_8020C2D8(player->bodyAnim);
				}
				if (player->head != NULL) {
					removeClump(player->head);
					fn_80150958(player->head);
				}
				if (player->unk20 != NULL) {
					fn_8013BD74(player->unk20);
				}
				for (s32 j = 0; j < player->mabutaCount; j++) {
					if (player->mabuta[j] != NULL && fn_8015BD78(player->mabuta[j]) != NULL) {
						removeClump(player->mabuta[j]);
					}
					fn_80150958(player->mabuta[j]);
				}
				player->mabutaNo = -1;
				if (player->modelAnim != NULL) {
					fn_8020C2D8(player->modelAnim);
					player->modelHierarchy->parentFrame = NULL;
					fn_8013EEE0(player->modelHierarchy);
					RpHAnimHierarchy* hierarchy = player->hierarchy;
					HAnim.SetHierarchyForAtomic(getPlayerBodyClump(i), hierarchy);
					fn_8013F3A4(player->hierarchy);
				}
				if (player->model != NULL) {
					if (player->modelPart != NULL) {
						removeClump(player->modelPart);
						fn_80150958(player->modelPart);
					}
					removeClump(player->model);
					fn_80150958(player->model);
				}
				memset(player, 0, sizeof(SceneMemPlayerObj));
			}
			if (scenes == NULL) {
				releaseSceneExtObjs();
				lbl_8042C9A4->Free((void*)unk44);
				unk44 = 0;
			}
			break;
		default:
			return 0;
	}
	return 1;
}
