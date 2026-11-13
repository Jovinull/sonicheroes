// Opens an ADXF handle for a file name: the inlined adxf_CreateAdxf takes a free slot and creates
// its stream, the file is bound and sized, and the call is recorded in the command history
// through the inlined ADXF_SetCmdHstry/ADXF_SetCmdHstryEnd setters.

#include "types.h"

typedef struct ADXF_CMD_HSTRY {
	u8 cmdid;
	u8 fg;
	u16 ncall;
	void* obj;
	s32 prm1;
	s32 prm2;
} ADXF_CMD_HSTRY;

typedef struct ADXF_OBJ {
	s8 used;
	s8 stat;
	s8 sjflag;
	s8 stopnw_flg;
	void* stm;
	void* sj;
	s32 fnsct;
	s32 fsize;
	s32 pos;
	s32 rdsct;
	s32 rqrdsct;
	s32 delta;
	void* buf;
	s32 bsize;
	s32 maxsct;
	s32 fend;
	void* dir;
	char* fname;
	s32 rqsct;
	s32 rqrdsct2;
} ADXF_OBJ;

extern "C" {
extern ADXF_CMD_HSTRY adxf_cmd_hstry[16];
extern u16 adxf_cmd_ncall[16];
extern s32 adxf_hstry_no[];
extern ADXF_OBJ adxf_obj[16];
extern char lbl_8023ED9C[];
extern char lbl_8023EDD4[];

void ADXERR_CallErrFunc1(const char*);
void* ADXSTM_Create(void*, s32);
void ADXSTM_BindFile(void*, const char*, void*, s32, s32);
s32 ADXSTM_GetStat(void*);
void ADXSTM_ReleaseFile(void*);
s32 ADXSTM_GetFileLen(void*);
void ADXF_Close(ADXF_OBJ*);

static inline void ADXF_SetCmdHstry(s32 cmdid, s32 fg, void* obj, s32 prm1, s32 prm2)
{
	s32 n;
	ADXF_CMD_HSTRY* h;
	n                = adxf_hstry_no[0] % 16;
	adxf_hstry_no[0] = n;
	h                = &adxf_cmd_hstry[n];
	h->cmdid         = cmdid;
	h->fg            = fg;
	h->ncall         = ++adxf_cmd_ncall[cmdid];
	h->obj           = obj;
	h->prm1          = prm1;
	h->prm2          = prm2;
	adxf_hstry_no[0] = n + 1;
}

static inline void ADXF_SetCmdHstryEnd(s32 cmdid, s32 fg, void* obj, s32 prm1, s32 prm2)
{
	s32 n;
	ADXF_CMD_HSTRY* h;
	n                = adxf_hstry_no[0] % 16;
	adxf_hstry_no[0] = n;
	h                = &adxf_cmd_hstry[n];
	h->cmdid         = cmdid;
	h->fg            = fg;
	h->ncall         = adxf_cmd_ncall[cmdid];
	h->obj           = obj;
	h->prm1          = prm1;
	h->prm2          = prm2;
	adxf_hstry_no[0] = n + 1;
}

static inline ADXF_OBJ* adxf_CreateAdxf(void)
{
	s32 i;
	ADXF_OBJ* adxf;

	adxf = NULL;
	for (i = 0; i < 16; i++) {
		if (adxf_obj[i].used == 0) {
			adxf = &adxf_obj[i];
			break;
		}
	}
	if (adxf == NULL) {
		return NULL;
	}
	if ((adxf->stm = ADXSTM_Create(NULL, 0x100)) == NULL) {
		ADXERR_CallErrFunc1(lbl_8023ED9C);
		return NULL;
	}
	adxf->stat       = 1;
	adxf->rdsct      = 0;
	adxf->rqrdsct    = 0;
	adxf->delta      = 0;
	adxf->maxsct     = 0x200;
	adxf->sjflag     = 0;
	adxf->sj         = NULL;
	adxf->stopnw_flg = 0;
	adxf->used       = 1;
	return adxf;
}

ADXF_OBJ* ADXF_Open(const char* fname, void* dir)
{
	s32 i;
	s32 n;
	s32 r;
	ADXF_OBJ* adxf;
	ADXF_CMD_HSTRY* h;

	ADXF_SetCmdHstry(1, 0, (void*)fname, (s32)dir, -1);

	adxf = adxf_CreateAdxf();
	if (adxf != NULL) {
		if (fname == NULL) {
			ADXERR_CallErrFunc1(lbl_8023EDD4);
			r = -1;
		} else {
			adxf->dir   = dir;
			adxf->fname = (char*)fname;
			adxf->pos   = 0;
			ADXSTM_BindFile(adxf->stm, adxf->fname, adxf->dir, 0, 0xFFFFF);
			if (ADXSTM_GetStat(adxf->stm) == 4) {
				ADXSTM_ReleaseFile(adxf->stm);
				r = -1;
			} else {
				adxf->fsize = ADXSTM_GetFileLen(adxf->stm);
				adxf->fnsct = adxf->fsize / 2048;
				adxf->rqsct = r = 0;
				adxf->rqrdsct2  = adxf->fnsct;
			}
		}
		if (r < 0) {
			ADXF_Close(adxf);
			adxf = NULL;
		}
	}

	ADXF_SetCmdHstryEnd(1, 1, (void*)fname, (s32)dir, -1);
	return adxf;
}
}
