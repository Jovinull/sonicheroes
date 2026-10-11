// EventManager::setAnimationExt (the PS2 build's name): it places an extra
// scene object at the script's origin (the first vector of the script data)
// and sets its animation time (setAnimation, inlined).

#include "src/rel/event_manager_class.inc"

extern "C" void fn_8019EE04(RwFrame* frame);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

void EventManager::setAnimationExt(SceneMemEtcObj* object, f32 time)
{
	RwFrame* frame = (RwFrame*)((RwObject*)object->clump)->parent;
	fn_8019EE04(frame);
	fn_8019EB94(frame, (RwV3d*)&EventScript::scriptData, 0);
	setAnimation(object->hierarchy, time);
}
