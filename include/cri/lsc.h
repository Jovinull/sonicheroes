#ifndef CRI_LSC_H
#define CRI_LSC_H

#include "cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSC_STM_MAX 16

typedef struct LscStm {
	/* 0x00 */ s32 id;
	/* 0x04 */ const char* fname;
	/* 0x08 */ s32 filenameChecksum;
	/* 0x0C */ void* dir;
	/* 0x10 */ s32 ofst;
	/* 0x14 */ s32 numSectors;
	/* 0x18 */ s32 stat;
	/* 0x1C */ s32 rdsct;
} LscStm;

typedef struct LscObj {
	/* 0x00 */ s8 used;
	/* 0x01 */ s8 stat;
	/* 0x02 */ s8 streamStarted;
	/* 0x03 */ s8 lpflg;
	/* 0x04 */ s8 unk4;
	/* 0x08 */ CriStream* sj;
	/* 0x0C */ s32 unkC;
	/* 0x10 */ s32 unk10;
	/* 0x14 */ s32 flowlimit;
	/* 0x18 */ s32 nsct;
	/* 0x1C */ s32 rdsct;
	/* 0x20 */ s32 head;
	/* 0x24 */ s32 numstm;
	/* 0x28 */ void* stmhndl;
	/* 0x2C */ s32 requestedSectors;
	/* 0x30 */ u8 unknown30[4];
	/* 0x34 */ s32 unk34;
	/* 0x38 */ LscStm stm[LSC_STM_MAX];
} LscObj;

typedef void (*LscStatFunc)(void* obj, s32 stat);

#define LSC_OBJ_MAX 16

typedef void (*LscErrorCallback)(void* object, char* message);
void fn_8021F410(const char* format, ...);
void fn_8021F4D0(LscErrorCallback callback, void* object);
void fn_8021F504(void* crs);
void fn_8021F524(void* crs);
void LSC_SetLpFlg(LscObj* lsc, s8 flag);
void LSC_CallStatFunc(void);
s32 LSC_GetFlowLimit(LscObj* lsc);
void LSC_SetFlowLimit(LscObj* lsc, s32 min);
s32 LSC_GetNumStm(LscObj* lsc);
s32 LSC_GetStat(LscObj* lsc);
void LSC_SetStmHndl(LscObj* lsc, void* hndl);
void LSC_ResetEntry(LscObj* lsc);
void LSC_ExecServer(void);
void LSC_EntryFname(LscObj* lsc, const char* fname);
s32 LSC_GetStmId(LscObj* lsc, s32 no);
s32 LSC_GetStmRdSct(LscObj* lsc, s32 id);
s32 LSC_GetStmStat(LscObj* lsc, s32 id);
const char* LSC_GetStmFname(LscObj* lsc, s32 id);

void fn_8021FAE4(LscObj* lsc);
void fn_8021FBA0(LscObj* lsc);
void fn_8021FF7C(LscObj* lsc);
LscObj* LSC_Create(CriStream* sj);
s32 LSC_EntryFileRange(LscObj* lsc, const char* fname, void* dir, s32 offset, s32 numSectors);
void fn_802201E0(void);
void fn_80220284(void);
void fn_802202FC(LscObj* lsc);
extern LscObj lsc_ObjTbl[LSC_OBJ_MAX];

#ifdef __cplusplus
}
#endif

#endif
