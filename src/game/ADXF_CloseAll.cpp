// Closes every ADXF handle that is in use (used == 1). `used` must be signed here to match.

#include "types.h"

typedef struct ADXF_OBJ {
	s8 used;
	s8 stat;
	s8 sjflag;
	u8 stopnw_flg;
	void* stm;
	void* sj;
	s32 fnsct;
	s32 skpos;
	s32 rqsct;
	s32 rdsct;
	s32 rqrdsct;
	void* buf;
	s32 bsize;
	s32 trnsct;
	s32 ofst;
	s32 fsize;
	s32 fsctsize;
	s32 dir;
	s32 ptid;
	s32 flid;
} ADXF_OBJ;

extern "C" {
void ADXF_Close(ADXF_OBJ*);
extern ADXF_OBJ adxf_obj[16];

void ADXF_CloseAll(void)
{
	s32 i;

	for (i = 0; i < 16; i++) {
		if (adxf_obj[i].used == 1) {
			ADXF_Close(&adxf_obj[i]);
		}
	}
}
}
