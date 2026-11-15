// Loads an animation and wraps it with a one-node interpolator (HYPOTHESIS: a game helper around
// RtAnim; names inferred): allocates the 0xC-byte wrapper, reads the animation (fn_8020C398),
// creates an interpolator for one node with the animation's key-frame size (fn_8020C658), clears
// the wrapper's time and sets the animation as current (fn_8020C72C). Returns the wrapper, or null
// when either the wrapper or the animation is missing (the other one is not released).
#include "game/rw_engine.h"

struct AnimInfo8011B654 {
	s32 typeID;       // 0x0
	s32 keyFrameSize; // 0x4
};

struct Animation8011B654 {
	AnimInfo8011B654* interpInfo; // 0x0
};

struct AnimHandle8011B654 {
	Animation8011B654* animation; // 0x0
	void* interpolator;           // 0x4
	s32 time;                     // 0x8
};

extern "C" {
// HYPOTHESIS: RtAnimAnimationRead, RtAnimInterpolatorCreate and RtAnimInterpolatorSetCurrentAnim.
Animation8011B654* fn_8020C398(const char* name);
void* fn_8020C658(s32 numNodes, s32 keyFrameSize);
void* fn_8020C72C(void* interpolator, Animation8011B654* animation);

AnimHandle8011B654* fn_8011B654(const char* name)
{
	AnimHandle8011B654* handle
	    = (AnimHandle8011B654*)lbl_8042C9A4->rwmalloc(sizeof(AnimHandle8011B654));
	Animation8011B654* animation = fn_8020C398(name);

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
