#include "types.h"

typedef struct SJ_IF {
	void* f0;
	void* f4;
	void* f8;
	void (*Destroy)(void*);
} SJ_IF;

typedef struct SJ_OBJ {
	SJ_IF* vtbl;
} SJ_OBJ;

typedef struct ADXF_OBJ {
	s8 used;
	s8 stat;
	s8 sjflag;
	s8 stopnw_flg;
	void* stm;
	SJ_OBJ* sj;
	s32 fnsct;
	s32 skpos;
	s32 pos;
	s32 rdsct;
	s32 rqrdsct;
	s32 delta;
	void* buf;
	s32 bsize;
	s32 ofst;
	s32 fsize;
	s32 fsctsize;
	s32 dir;
	s32 ptid;
	s32 flid;
} ADXF_OBJ;

extern "C" {
extern ADXF_OBJ adxf_obj[16];
extern s32 adxf_ocbi_fg[];
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
s32 ADXSTM_GetStat(void*);
s32 ADXSTM_Tell(void*);
void ADXF_Ocbi(void*, u32);

void ADXF_ExecServer(void)
{
	s32 i;
	SJ_OBJ* sj;

	ADXCRS_Lock();
	for (i = 0; i < 16; i++) {
		if (adxf_obj[i].used == 1) {
			if (adxf_obj[i].stat == 2) {
				adxf_obj[i].stat  = ADXSTM_GetStat(adxf_obj[i].stm);
				adxf_obj[i].delta = ADXSTM_Tell(adxf_obj[i].stm) - adxf_obj[i].pos;
				if (adxf_obj[i].stat == 3 || adxf_obj[i].stat == 4) {
					adxf_obj[i].pos += adxf_obj[i].delta;
					if (adxf_obj[i].sj != NULL && adxf_obj[i].sjflag == 0) {
						if (adxf_ocbi_fg[0] == 1) {
							ADXF_Ocbi(adxf_obj[i].buf, adxf_obj[i].bsize);
						}
						sj             = adxf_obj[i].sj;
						adxf_obj[i].sj = NULL;
						sj->vtbl->Destroy(sj);
					}
				}
			}
			if (adxf_obj[i].stopnw_flg == 1) {
				if (ADXSTM_GetStat(adxf_obj[i].stm) == 1) {
					adxf_obj[i].delta = ADXSTM_Tell(adxf_obj[i].stm) - adxf_obj[i].pos;
					if (adxf_obj[i].sj != NULL && adxf_obj[i].sjflag == 0) {
						if (adxf_ocbi_fg[0] == 1) {
							ADXF_Ocbi(adxf_obj[i].buf, adxf_obj[i].bsize);
						}
						sj             = adxf_obj[i].sj;
						adxf_obj[i].sj = NULL;
						sj->vtbl->Destroy(sj);
					}
					adxf_obj[i].stat       = 1;
					adxf_obj[i].stopnw_flg = 0;
				}
			}
		}
	}
	ADXCRS_Unlock();
}
}
