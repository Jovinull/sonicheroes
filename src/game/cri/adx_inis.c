// adx_inis: ADXT library init/finish and the SVM server callbacks.
// .text 0x8020D1FC-0x8020D4A8 (8 functions), .rodata 0x8023D648-0x8023D67C,
// .data 0x8029B568-0x8029B56C, .bss 0x8040EEA8-0x8040FABC.
// Boundary: the unit's .rodata opens with the "ADXT/GC Ver.8.84" banner and the
// const pointer ADXT_Init reads; every .bss/.data label here is used only by
// ADXT_Init/ADXT_Finish (adxt_vsync_cnt/adxt_obj are shared with adx_tlk).
// Functions and order match MKD adx_inis.o; source order is the PS2 (reverse)
// order, emitted reversed by -inline deferred.

#include "types.h"
#include "MSL_C/string.h"

typedef void (*AdxErrFunc)(void* object, const char* message);
typedef s32 (*SvmCbFunc)(void* object);

extern void ADXRNA_Finish(void);
extern void ADXF_Finish(void);
extern void ADXSTM_Finish(void);
extern void fn_802201E0(void); /* LSC_Finish */
extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);
extern void ADXCRS_Init(void);
extern void fn_80222148(s32 svtype, s32 id); /* SVM_DelCbSvr */
extern void fn_802219BC(void);               /* SVM_Finish */
extern void ADXSJD_Finish(void);
extern void ADXERR_Finish(void);
extern void fn_80220B2C(void); /* SJMEM_Finish */
extern void fn_80221498(void); /* SJRBF_Finish */
extern void fn_80221574(void); /* SJUNI_Finish */
extern void fn_802215BC(void); /* SJUNI_Init */
extern void fn_802214E8(void); /* SJRBF_Init */
extern void fn_80220B74(void); /* SJMEM_Init */
extern void ADXERR_Init(void);
extern void ADXSTM_Init(void);
extern void ADXSJD_Init(void);
extern void ADXF_Init(void);
extern void ADXRNA_Init(void);
extern void fn_80220284(void); /* LSC_Init */
extern void fn_80221A64(void); /* SVM_Init */
extern void ADXRNA_EntryErrFunc(AdxErrFunc func, void* object);
extern void fn_8021F4D0(AdxErrFunc func, void* object); /* LSC_EntryErrFunc */
extern s32 ADXM_IsSetupThrd(void);
extern void fn_80221F94(s32 svtype, s32 id, SvmCbFunc func, void* object); /* SVM_SetCbSvrId */
extern s32 fn_80222290(s32 svtype, SvmCbFunc func, void* object);          /* SVM_SetCbSvr */
extern void ADXT_ExecFsSvr(void);
extern void ADXT_ExecServer(void);
extern void LSC_ExecServer(void);
extern void ADXERR_CallErrFunc1(const char* message);

s32 adxt_init_cnt    = 0;
s32 adxt_svr_id      = 0;
s32 adxt_svr_main_id = 0;
s32 adxt_svr_fs_id   = 0;
s32 adxt_vsync_cnt   = 0;
u8 adxt_obj[16][0xC0];

s32 adxt_vsync_svr_flag = 1;

static const char adxt_build[]          = "\nADXT/GC Ver.8.84 Build:May  9 2003 17:11:01\n";
static const char* const cri_verstr_ptr = adxt_build;

s32 adxt_exec_fssvr(void* object);
s32 adxt_exec_tsvr(void* object);
s32 adxt_exec_main_nothrd(void* object);
s32 adxt_exec_main_thrd(void* object);
void adxini_lscerr_cbfn(void* object, const char* message);
void adxini_rnaerr_cbfn(void* object, const char* message);

void adxini_rnaerr_cbfn(void* object, const char* message)
{
	ADXERR_CallErrFunc1(message);
}

void adxini_lscerr_cbfn(void* object, const char* message)
{
	ADXERR_CallErrFunc1(message);
}

s32 adxt_exec_main_thrd(void* object)
{
	LSC_ExecServer();
	return 0;
}

s32 adxt_exec_main_nothrd(void* object)
{
	ADXT_ExecServer();
	ADXT_ExecFsSvr();
	LSC_ExecServer();
	return 0;
}

s32 adxt_exec_tsvr(void* object)
{
	ADXT_ExecServer();
	return 0;
}

s32 adxt_exec_fssvr(void* object)
{
	ADXT_ExecFsSvr();
	return 0;
}

void ADXT_Init(void)
{
	(void)*(const char* volatile*)&cri_verstr_ptr;
	if (adxt_init_cnt == 0) {
		ADXCRS_Init();
		ADXCRS_Lock();
		fn_802215BC();
		fn_802214E8();
		fn_80220B74();
		ADXERR_Init();
		ADXSTM_Init();
		ADXSJD_Init();
		ADXF_Init();
		ADXRNA_Init();
		fn_80220284();
		fn_80221A64();
		ADXRNA_EntryErrFunc(adxini_rnaerr_cbfn, NULL);
		fn_8021F4D0(adxini_lscerr_cbfn, NULL);
		memset(adxt_obj, 0, sizeof(adxt_obj));
		if (ADXM_IsSetupThrd() == 1 && adxt_vsync_svr_flag == 1) {
			fn_80221F94(2, 1, adxt_exec_tsvr, NULL);
			adxt_svr_fs_id   = fn_80222290(4, adxt_exec_fssvr, NULL);
			adxt_svr_main_id = fn_80222290(5, adxt_exec_main_thrd, NULL);
		} else {
			adxt_svr_main_id = fn_80222290(5, adxt_exec_main_nothrd, NULL);
		}
		adxt_vsync_cnt = 0;
		ADXCRS_Unlock();
	}
	adxt_init_cnt++;
}

void ADXT_Finish(void)
{
	if (--adxt_init_cnt == 0) {
		ADXRNA_Finish();
		ADXF_Finish();
		ADXSTM_Finish();
		fn_802201E0();
		ADXCRS_Lock();
		fn_80222148(2, 1);
		fn_80222148(4, adxt_svr_fs_id);
		fn_80222148(5, adxt_svr_main_id);
		fn_802219BC();
		ADXSJD_Finish();
		ADXERR_Finish();
		fn_80220B2C();
		fn_80221498();
		fn_80221574();
		ADXCRS_Unlock();
	}
}
