#include "types.h"

struct RwV3d {
	float x;
	float y;
	float z;
};

struct RpDMorphAnimation;

struct CALC_DLINIAR_TABLE {
	float time;
	RwV3d point;
};

struct DANIM_KEY {
	s32 startFrame;
	s32 endFrame;
	float startTime;
	float endTime;
};

enum DANIM_LOOPTYPE {
	DANIM_LOOP_STOP   = 0,
	DANIM_LOOP_REPEAT = 1,
	DANIM_LOOP_HOLD   = 2,
};

extern "C" {
u32 RpDMorphAnimationGetNumDMorphTargets(RpDMorphAnimation*);
s32 RpDMorphAnimationGetNumFrames(RpDMorphAnimation*, s32);
float RpDMorphAnimationFrameGetDuration(RpDMorphAnimation*, s32, s32);
}

class DAnimClass
{
	u32 unk0;
	u32 unk4;

public:
	DAnimClass() { }
	~DAnimClass();

	float GetTotalFrame(RpDMorphAnimation*);
	s32 GetLinearPoint(RwV3d*, CALC_DLINIAR_TABLE*, float);
	float GetDAnimTimePoint(RpDMorphAnimation*, s32, s32);
	float GetDAnimKeyPoint(RpDMorphAnimation*, s32, float);
	s32 DAnimMotion(float*, DANIM_KEY*, float, DANIM_LOOPTYPE);
	float GetDAnimKeyList(DANIM_KEY*, s32, s32, RpDMorphAnimation*);
};

float DAnimClass::GetTotalFrame(RpDMorphAnimation* animation)
{
	if (animation == 0) {
		return -1.0f;
	}

	u32 targetCount = RpDMorphAnimationGetNumDMorphTargets(animation);
	float maximum   = 0.0f;
	for (u32 target = 0; target < targetCount; target++) {
		float total    = 0.0f;
		u32 frameCount = RpDMorphAnimationGetNumFrames(animation, target);
		for (u32 frame = 0; frame < frameCount; frame++) {
			total += RpDMorphAnimationFrameGetDuration(animation, target, frame);
		}
		if (total > maximum) {
			maximum = total;
		}
	}
	return maximum;
}

s32 DAnimClass::GetLinearPoint(RwV3d* point, CALC_DLINIAR_TABLE* table, float time)
{
	if (time <= 0.0f) {
		*point = table->point;
		return 0;
	}

	CALC_DLINIAR_TABLE* previous = 0;
	while (table->time >= 0.0f) {
		if (time < table->time) {
			float ratio = (time - previous->time) / (table->time - previous->time);
			point->x    = previous->point.x + ratio * (table->point.x - previous->point.x);
			point->y    = previous->point.y + ratio * (table->point.y - previous->point.y);
			point->z    = previous->point.z + ratio * (table->point.z - previous->point.z);
			return 1;
		}
		previous = table;
		table++;
	}

	*point = previous->point;
	return 0;
}

#pragma opt_propagation off
float DAnimClass::GetDAnimTimePoint(RpDMorphAnimation* animation, s32 target, s32 frame)
{
	s32 frameIndex = frame;
	s32 frameCount;
	float total;
	register s32 targetIndex;
	register s32 i;

	frameCount = RpDMorphAnimationGetNumFrames(animation, targetIndex = target);
	total      = 0.0f;
	for (i = 0; i < frameCount; i++) {
		if (frameIndex == i) {
			return total;
		}
		total += RpDMorphAnimationFrameGetDuration(animation, targetIndex, i);
	}
	return total;
}

float DAnimClass::GetDAnimKeyPoint(RpDMorphAnimation* animation, s32 target, float time)
{
	float total    = 0.0f;
	float previous = total;
	if (time < 0.0f) {
		return -1.0f;
	}

	register s32 targetIndex;
	register s32 i;
	s32 frameCount = RpDMorphAnimationGetNumFrames(animation, targetIndex = target);
	for (i = 0; i < frameCount; i++) {
		float duration = RpDMorphAnimationFrameGetDuration(animation, targetIndex, i);
		total += duration;
		if (total > time) {
			return (float)i + (time - previous) / duration;
		}
		previous = total;
	}
	return -1.0f;
}
#pragma opt_propagation on

s32 DAnimClass::DAnimMotion(float* motion, DANIM_KEY* key, float delta, DANIM_LOOPTYPE loop)
{
	s32 result;

	if (delta == 0.0f) {
		return 0;
	}

	*motion += delta;
	if (delta > 0.0f) {
		result = 1;
		if (*motion <= key->startTime) {
			*motion = key->startTime;
			return 1;
		}
		if (*motion >= key->endTime) {
			switch (loop) {
				case DANIM_LOOP_STOP:
					*motion = key->endTime;
					return -1;
				case DANIM_LOOP_REPEAT:
					*motion = key->startTime;
					return 1;
				case DANIM_LOOP_HOLD:
					*motion = key->endTime;
					return 0;
			}
		}
	} else {
		result = -1;
		if (*motion >= key->endTime) {
			*motion = key->endTime;
			return -1;
		}
		if (*motion <= key->startTime) {
			switch (loop) {
				case DANIM_LOOP_STOP:
					*motion = key->startTime;
					return 1;
				case DANIM_LOOP_REPEAT:
					*motion = key->endTime;
					return -1;
				case DANIM_LOOP_HOLD:
					*motion = key->startTime;
					return 0;
			}
		}
	}
	return result;
}

float DAnimClass::GetDAnimKeyList(
    DANIM_KEY* keys, s32 keyCount, s32 target, RpDMorphAnimation* animation)
{
	s32 keyIndex;
	s32 frameCount;
	float total;

	{
		s32 frame;
		u32 animationBits = (u32)animation;
		RpDMorphAnimation* targetBits;

		total = 0.0f;

		frameCount = RpDMorphAnimationGetNumFrames(
		    (RpDMorphAnimation*)animationBits, (s32)(targetBits = (RpDMorphAnimation*)target));
		for (frame = 0; frame <= frameCount; frame++) {
			for (s32 keyIndex = 0; keyIndex < keyCount; keyIndex++) {
				DANIM_KEY* key = &keys[keyIndex];
				if (key->startFrame == -1) {
					key->startFrame = frameCount;
				}
				if (frame == key->startFrame) {
					key->startTime = total;
				}
				if (key->endFrame == -1) {
					key->endFrame = frameCount;
				}
				if (frame == key->endFrame) {
					key->endTime = total;
				}
			}
			if (frame != frameCount) {
				total += RpDMorphAnimationFrameGetDuration(
				    (RpDMorphAnimation*)animationBits, (s32)targetBits, frame);
			}
		}
	}

	for (keyIndex = 0; keyIndex < keyCount; keyIndex++) {
		if (keys[keyIndex].endFrame == frameCount) {
			keys[keyIndex].endTime -= 0.00001f;
		}
	}
	return total;
}
DAnimClass::~DAnimClass() { }

DAnimClass lbl_8042C340;
