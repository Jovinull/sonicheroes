#include "types.h"

// TObjEnemyCapture::EditOnChange (the PS2 build's name), the same in stage03D,
// stage05D, stage07D, stage09D and stage26D (stage13D's copy is another
// revision, and stage11D's is part of rel/e_capture.cpp): on an edit each of
// the capture's parameters is clamped to its range, and the type and appear
// field labels are set to the names of the chosen ones. It is the body of
// TObjEnemyTurtle::EditOnChange (rel/e_turtle_stage11.cpp) over the capture's
// own bounds, written here with the bounds as the module's named constants.

typedef struct SETDATA_PARAM {
	u8 unk00[0x2C];
	void* setBuffer; // 0x2C
} SETDATA_PARAM;

typedef struct sCaptureSetParam {
	/* 0x00 */ s8 captureType;
	/* 0x01 */ s8 appearType;
	/* 0x02 */ u8 pad2[2];
	/* 0x04 */ f32 moveRange;
	/* 0x08 */ f32 scopeRange;
	/* 0x0C */ f32 scopeOffset;
	/* 0x10 */ s32 attackInterval;
	/* 0x14 */ f32 weaponSpeed;
} sCaptureSetParam;

template <class T> static inline const T& Clamp(const T& value, const T& lo, const T& hi)
{
	if (value < lo) {
		return lo;
	}
	if (value > hi) {
		return hi;
	}
	return value;
}

class TObjEnemyCapture
{
public:
	void EditOnChange(SETDATA_PARAM*);
};

extern "C" {
extern char* captureObjectFieldNames[];
extern char* captureTypeNames[];
extern char* captureAppearNames[];
extern const s8 captureTypeMin;
extern const s8 captureTypeMax;
extern const s8 captureAppearMin;
extern const s8 captureAppearMax;
extern const f32 captureMoveRangeMin;
extern const f32 captureMoveRangeMax;
extern const f32 captureScopeRangeMin;
extern const f32 captureScopeRangeMax;
extern const s32 captureIntervalMin;
extern const s32 captureIntervalMax;
extern const f32 captureWeaponSpeedMin;
extern const f32 captureWeaponSpeedMax;
}

void TObjEnemyCapture::EditOnChange(SETDATA_PARAM* data)
{
	sCaptureSetParam* param = (sCaptureSetParam*)data->setBuffer;

	param->captureType    = Clamp(param->captureType, captureTypeMin, captureTypeMax);
	param->appearType     = Clamp(param->appearType, captureAppearMin, captureAppearMax);
	param->moveRange      = Clamp(param->moveRange, captureMoveRangeMin, captureMoveRangeMax);
	param->scopeRange     = Clamp(param->scopeRange, captureScopeRangeMin, captureScopeRangeMax);
	param->attackInterval = Clamp(param->attackInterval, captureIntervalMin, captureIntervalMax);
	param->weaponSpeed    = Clamp(param->weaponSpeed, captureWeaponSpeedMin, captureWeaponSpeedMax);
	captureObjectFieldNames[0] = captureTypeNames[param->captureType];
	captureObjectFieldNames[1] = captureAppearNames[param->appearType];
}
