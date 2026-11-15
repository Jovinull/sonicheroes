// Loads an animation file and wraps it with a one-node interpolator, like fn_8011B654 but reading
// the animation by file name (fn_8020C314): allocates the 0xC-byte wrapper, creates an
// interpolator for one node with the animation's key-frame size (fn_8020C658), clears the
// wrapper's time and sets the animation as current (fn_8020C72C). Returns the wrapper, or null when
// either the wrapper or the animation is missing (the other one is not released).
#include "game/rw_engine.h"

struct AnimInfo8011B6F0 {
	s32 typeID;       // 0x0
	s32 keyFrameSize; // 0x4
};

struct Animation8011B6F0 {
	AnimInfo8011B6F0* interpInfo; // 0x0
};

struct AnimHandle8011B6F0 {
	Animation8011B6F0* animation; // 0x0
	void* interpolator;           // 0x4
	s32 time;                     // 0x8
};

extern "C" {
// HYPOTHESIS: RtAnimAnimationRead, RtAnimInterpolatorCreate and RtAnimInterpolatorSetCurrentAnim.
Animation8011B6F0* fn_8020C314(const char* fileName);
void* fn_8020C658(s32 numNodes, s32 keyFrameSize);
void* fn_8020C72C(void* interpolator, Animation8011B6F0* animation);

AnimHandle8011B6F0* fn_8011B6F0(const char* fileName)
{
	AnimHandle8011B6F0* handle
	    = (AnimHandle8011B6F0*)lbl_8042C9A4->rwmalloc(sizeof(AnimHandle8011B6F0));
	Animation8011B6F0* animation = fn_8020C314(fileName);

	if (handle != 0 && animation != 0) {
		handle->interpolator = fn_8020C658(1, animation->interpInfo->keyFrameSize);
		handle->time         = 0;
		handle->animation    = animation;
		fn_8020C72C(handle->interpolator, animation);
		return handle;
	}
	return 0;
}
}
