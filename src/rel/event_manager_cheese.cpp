// An EventManager function only the GameCube build has, with no caller: it
// puts Cheese's model (the second of main's two cheese clumps) on the frame of
// the body model in slot 13, moved by eventCheeseOffset, and updates the
// clump. The PS2 build has only TObjCheese::GetCheeseClump at this place, so
// the name setCheeseFrame is ours.

#include "src/rel/event_manager_class.inc"

extern "C" struct RpClump* lbl_8042B708[2];
extern "C" RwV3d eventCheeseOffset;
extern "C" void* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019ECCC(RwFrame* frame, void* matrix, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8014FF2C(struct RpClump* clump);

void EventManager::setCheeseFrame()
{
	SceneMemPlayerObj* player = (SceneMemPlayerObj*)&slots[13];
	if (player->body != NULL) {
		void* matrix   = fn_8019E8EC((RwFrame*)((RwObject*)player->body)->parent);
		RwFrame* frame = (RwFrame*)((RwObject*)lbl_8042B708[1])->parent;
		fn_8019ECCC(frame, matrix, 0);
		fn_8019EB94(frame, &eventCheeseOffset, 2);
		fn_8014FF2C(lbl_8042B708[1]);
	}
}
