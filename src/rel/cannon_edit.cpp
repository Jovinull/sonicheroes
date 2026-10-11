#include "types.h"

// The cannon object's EditOnChange (cannonEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct CannonParams {
	s16 f00; // 0x00
	s16 f02; // 0x02
	s16 f04; // 0x04
	s16 f06; // 0x06
	s16 f08; // 0x08
	s16 f0A; // 0x0A
	s16 f0C; // 0x0C
	s16 f0E; // 0x0E
	s16 f10; // 0x10
	s16 f12; // 0x12
	s16 f14; // 0x14
	s16 f16; // 0x16
} CannonParams;

typedef struct CannonEdit {
	u8 unk00[0x2C];
	CannonParams* params; // 0x2C
} CannonEdit;

extern "C" void cannonEditOnChange(void* object, CannonEdit* edit)
{
	CannonParams* params = edit->params;

	if (params->f00 < -180) {
		params->f00 = -180;
	}
	if (params->f00 > 0) {
		params->f00 = 0;
	}
	if (params->f08 < -180) {
		params->f08 = -180;
	}
	if (params->f08 > 0) {
		params->f08 = 0;
	}
	if (params->f10 < -180) {
		params->f10 = -180;
	}
	if (params->f10 > 0) {
		params->f10 = 0;
	}
	if (params->f02 < -180) {
		params->f02 = -180;
	}
	if (params->f02 > 180) {
		params->f02 = 180;
	}
	if (params->f0A < -180) {
		params->f0A = -180;
	}
	if (params->f0A > 180) {
		params->f0A = 180;
	}
	if (params->f12 < -180) {
		params->f12 = -180;
	}
	if (params->f12 > 180) {
		params->f12 = 180;
	}
	if (params->f04 < 0) {
		params->f04 = 0;
	}
	if (params->f04 > 32767) {
		params->f04 = 32767;
	}
	if (params->f0C < 0) {
		params->f0C = 0;
	}
	if (params->f0C > 32767) {
		params->f0C = 32767;
	}
	if (params->f14 < 0) {
		params->f14 = 0;
	}
	if (params->f14 > 32767) {
		params->f14 = 32767;
	}
	if (params->f06 > 450) {
		params->f04 = 450;
	}
	if (params->f06 < -30) {
		params->f04 = -30;
	}
	if (params->f0E > 450) {
		params->f0C = 450;
	}
	if (params->f0E < -30) {
		params->f0C = -30;
	}
	if (params->f16 > 450) {
		params->f14 = 450;
	}
	if (params->f16 < -30) {
		params->f14 = -30;
	}
}
