#ifndef GAME_PATHCTRL_H
#define GAME_PATHCTRL_H
#include "types.h"
typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;
typedef struct sAngle {
	s32 x, y, z;
} sAngle;
typedef struct NJS_LINE {
	RwV3d p, v;
} NJS_LINE;
typedef struct PATHTBL_P {
	s16 slangx, slangz;
	f32 length;
	RwV3d pos;
} PATHTBL_P;
class CLASS_PATH;
typedef struct PATHTAG {
	s16 pathtype, points;
	f32 totallen;
	void* pathtbl;
	void (*pathtask)(CLASS_PATH*);
} PATHTAG;
class CLASS_PATH
{
public:
	s8 mode, flag;
	s16 timer;
	s16 player[8];
	sAngle ang;
	RwV3d maxpos, minpos, n;
	PATHTAG* tagptr;
	s32 useCopyData;
	CLASS_PATH *next, *last;
	void (*execfunc)(CLASS_PATH*);
	CLASS_PATH(void (*)(CLASS_PATH*));
	~CLASS_PATH();
	void Reset();
	void Exec();
};

void pathSpin1D(CLASS_PATH*);
void pathGliding(CLASS_PATH*);
void pathSeeingPath(CLASS_PATH*);

#endif
