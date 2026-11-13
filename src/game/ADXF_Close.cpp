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

typedef struct ADXF_CMD_HSTRY {
	u8 cmdid;
	u8 fg;
	u16 ncall;
	void* obj;
	s32 prm1;
	s32 prm2;
} ADXF_CMD_HSTRY;

extern "C" {
extern ADXF_CMD_HSTRY adxf_cmd_hstry[16];
extern u16 adxf_cmd_ncall[16];
extern s32 adxf_hstry_no[];
extern s32 adxf_ocbi_fg[];
extern char lbl_8023EB7C[];
extern char lbl_8023EBA0[];

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void ADXERR_CallErrFunc1(const char*);
void ADXF_Ocbi(void*, u32);
void ADXSTM_Destroy(void*);
void ADXSTM_ReleaseFile(void*);
void ADXSTM_Stop(void*);
s32 ADXSTM_Tell(void*);
void* memset(void*, int, u32);

void ADXF_Close(ADXF_OBJ* obj)
{
	s32 idx;
	u16 ncall;
	ADXF_CMD_HSTRY* h;
	SJ_OBJ* sj;
	void* stm;

	idx              = adxf_hstry_no[0] % 16;
	adxf_hstry_no[0] = idx;
	h                = &adxf_cmd_hstry[idx];
	ncall            = ++adxf_cmd_ncall[3];
	h->cmdid         = 3;
	h->fg            = 0;
	h->ncall         = ncall;
	h->obj           = obj;
	h->prm1          = -1;
	h->prm2          = -1;
	adxf_hstry_no[0] = idx + 1;

	if (obj == NULL) {
		return;
	}

	if (obj->stat == 2) {
		idx               = adxf_hstry_no[0] % 16;
		adxf_hstry_no[0]  = idx;
		h                 = &adxf_cmd_hstry[idx];
		ncall             = adxf_cmd_ncall[5] + 1;
		adxf_cmd_ncall[5] = ncall;
		h->cmdid          = 5;
		h->fg             = 0;
		h->ncall          = ncall;
		h->obj            = obj;
		h->prm1           = -1;
		h->prm2           = -1;
		adxf_hstry_no[0]  = idx + 1;

		if (obj == NULL) {
			ADXERR_CallErrFunc1(lbl_8023EB7C);
		} else if (obj->stat == 1) {
		} else if (obj->stat == 3) {
			obj->stat = 1;
		} else if (obj->stm == NULL) {
			ADXERR_CallErrFunc1(lbl_8023EBA0);
		} else {
			ADXSTM_Stop(obj->stm);
			ADXCRS_Lock();
			obj->delta = ADXSTM_Tell(obj->stm) - obj->pos;
			if (obj->sj != NULL && obj->sjflag == 0) {
				if (adxf_ocbi_fg[0] == 1) {
					ADXF_Ocbi(obj->buf, obj->bsize);
				}
				sj      = obj->sj;
				obj->sj = NULL;
				sj->vtbl->Destroy(sj);
			}
			obj->stat = 1;
			ADXCRS_Unlock();

			idx              = adxf_hstry_no[0] % 16;
			adxf_hstry_no[0] = idx;
			h                = &adxf_cmd_hstry[idx];
			h->cmdid         = 5;
			h->fg            = 1;
			h->ncall         = adxf_cmd_ncall[5];
			h->obj           = obj;
			h->prm1          = -1;
			h->prm2          = -1;
			adxf_hstry_no[0] = idx + 1;
		}
	}

	stm = obj->stm;
	if (stm != NULL) {
		obj->stm = NULL;
		ADXSTM_ReleaseFile(stm);
		ADXSTM_Destroy(stm);
	}
	memset(obj, 0, 0x44);

	idx              = adxf_hstry_no[0] % 16;
	adxf_hstry_no[0] = idx;
	h                = &adxf_cmd_hstry[idx];
	h->cmdid         = 3;
	h->fg            = 1;
	h->ncall         = adxf_cmd_ncall[3];
	h->obj           = obj;
	h->prm1          = -1;
	h->prm2          = -1;
	adxf_hstry_no[0] = idx + 1;
}
}
