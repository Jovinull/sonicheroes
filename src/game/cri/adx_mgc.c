// CRI ADXM thread manager for GameCube (adx_mgc).
//
// .text 0x8021ABC0..0x8021B274 (14 functions, ADXM_IsSetupThrd..ADXM_WaitVsync),
// .rodata 0x8023E8E8..0x8023E949 (banner, its pointer, the border error string),
// .data 0x8029B798..0x8029B7B8 (saved thread parameters, idle sleep callback),
// .bss 0x80414B80..0x8041C830 (one pooled block: counters, four OSThreads,
// thread stacks).
//
// Boundary: the unit opens with the "ADXGC Ver.1.21" banner; every data label
// above is used only by these functions; function set and order match MKD's
// adx_mgc.o (ADXM_ShutdownThrd is not linked in Heroes). The next banner
// (ADXGCSDK) starts adx_sugc.
//
// Built with -inline deferred like the rest of the CRI library: functions are
// emitted in reverse source order and uninitialized statics are laid out in
// reverse declaration order, so both are written reversed here.

#include "types.h"

typedef void (*SvmErrorFunc)(void* object, const char* message);
extern void fn_80221A64(const char* build);                         /* SVM_Init */
extern s32 fn_80221AFC(void);                                       /* SVM_ExecSvrMwIdle */
extern s32 fn_80221B8C(void);                                       /* SVM_ExecSvrMain */
extern s32 fn_80221C1C(void);                                       /* SVM_ExecSvrFs */
extern s32 fn_80221CAC(void);                                       /* SVM_ExecSvrVsync */
extern void fn_80221D3C(void (*func)(void* obj), void* obj);        /* SVM_SetCbUnlock */
extern void fn_80221D4C(void (*func)(void* obj), void* obj);        /* SVM_SetCbLock */
extern void fn_80221D5C(SvmErrorFunc func, void* obj);              /* SVM_SetCbErr */
extern void fn_80221E90(s32 id, s32 (*func)(void* obj), void* obj); /* SVM_SetCbBdr */
extern void fn_8022240C(const char* msg);                           /* SVM_CallErr1 */
extern void fn_8022291C(void);                                      /* SVM_Unlock */
extern void fn_802229AC(void);                                      /* SVM_Lock */

/* Dolphin OS thread object; only its size (0x318) matters here. */
typedef struct OSThread {
	u8 opaque[0x318];
} OSThread;

typedef void* (*OSThreadFunc)(void* arg);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern BOOL OSCreateThread(OSThread* thread, OSThreadFunc func, void* param, void* stack,
    u32 stackSize, s32 prio, u16 attr);
extern OSThread* OSGetCurrentThread(void);
extern s32 OSResumeThread(OSThread* thread);
extern s32 OSSuspendThread(OSThread* thread);
extern BOOL OSSetThreadPriority(OSThread* thread, s32 prio);
extern s32 OSGetThreadPriority(OSThread* thread);
extern void VIWaitForRetrace(void);
extern s32 adxt_vsync_cnt; /* adxt_vsync_cnt */

typedef struct ADXM_TPRM {
	s32 prio_lock;
	s32 prio_safe;
	s32 prio_vsync;
	s32 prio_fs;
	s32 prio_usr;
	s32 prio_mwidle;
} ADXM_TPRM;

typedef struct ADXM_CB {
	void (*func)(void* obj);
	void* obj;
} ADXM_CB;

static const char adxgc_build_str[] = "\nADXGC Ver.1.21 Build:May  9 2003 17:11:17\n";
const char* const adxgc_build       = adxgc_build_str;

static ADXM_TPRM adxm_save_tprm = { 0, 0, 0, 0, 0, 0 };
ADXM_CB adxm_mwidle_sleep_cb    = { 0, 0 };

static void* adxgc_exec_svr         = 0;
static s32 adxm_init_level          = 0;
static volatile s32 adxm_lock_level = 0;
static s32 adxm_goto_border_flag    = 0;
static volatile s32 adxm_safe_cnt   = 0;
static s32 adxm_vsync_cnt           = 0;
static s32 adxm_fs_cnt              = 0;
static s32 adxm_mwidle_cnt          = 0;
static s32 adxm_mwidle_exec_flag    = 0;
static OSThread* adxm_main_thread   = 0;
/* -inline deferred lays uninitialized statics out in reverse declaration order */
static u8 adxm_stack_safe[0x1000];
static u8 adxm_stack_vsync[0x2000];
static u8 adxm_stack_fs[0x2000];
static u8 adxm_stack_mwidle[0x2000];
static volatile s32 adxm_safe_act;
static volatile s32 adxm_safe_end;
static volatile s32 adxm_mwidle_act;
static volatile s32 adxm_mwidle_end;
static volatile s32 adxm_vsync_act;
static volatile s32 adxm_vsync_end;
static volatile s32 adxm_fs_act;
static volatile s32 adxm_fs_end;
static s32 adxm_set_prio;
static s32 adxm_cur_prio;
static OSThread adxm_safe_thread;
static OSThread adxm_fs_thread;
static OSThread adxm_vsync_thread;
static OSThread adxm_mwidle_thread;

void adxm_mwidle_proc(void* arg);
void adxm_fs_proc(void* arg);
void adxm_vsync_proc(void* arg);
void adxm_safe_proc(void* arg);
void adxm_goto_mwidle_border(void* obj);
void adxm_unlock(void* obj);
void adxm_lock(void* obj);

void ADXM_WaitVsync(void)
{
	VIWaitForRetrace();
}

void ADXM_ExecMain(void)
{
	fn_80221B8C();
}

void ADXM_Lock(void)
{
	fn_802229AC();
}

void ADXM_Unlock(void)
{
	fn_8022291C();
}

void adxm_lock(void* obj)
{
	BOOL intr;
	OSThread* thrd;
	s32 prio;

	if (adxm_lock_level == 0) {
		intr = OSDisableInterrupts();
		OSDisableScheduler();
		adxm_set_prio = 1;
		thrd          = OSGetCurrentThread();
		prio          = OSGetThreadPriority(thrd);
		OSSetThreadPriority(thrd, adxm_save_tprm.prio_lock);
		adxm_cur_prio = prio;
		adxm_set_prio = 0;
		OSEnableScheduler();
		OSRestoreInterrupts(intr);
		OSResumeThread(&adxm_safe_thread);
	}
	adxm_lock_level++;
}

void adxm_unlock(void* obj)
{
	OSThread* thrd;

	adxm_lock_level--;
	if (adxm_lock_level == 0) {
		thrd = OSGetCurrentThread();
		OSSuspendThread(&adxm_safe_thread);
		OSSetThreadPriority(thrd, adxm_cur_prio);
	}
}

void adxm_goto_mwidle_border(void* obj)
{
	s32 i;

	if (adxm_mwidle_end != 1) {
		adxm_goto_border_flag = 1;
		OSSetThreadPriority(&adxm_mwidle_thread, adxm_save_tprm.prio_lock);
		for (i = 0; i < 200000000; i++) {
			OSResumeThread(&adxm_mwidle_thread);
			if (adxm_goto_border_flag == 0) {
				break;
			}
		}
		if (i == 200000000) {
			fn_8022240C("1060102: Internal Error: adxm_goto_mwidle_border");
		}
		OSSetThreadPriority(&adxm_mwidle_thread, adxm_save_tprm.prio_mwidle);
	}
}

void adxm_safe_proc(void* arg)
{
	while (adxm_safe_act == 1) {
		adxm_safe_cnt++;
	}
	adxm_safe_end = 1;
}

void adxm_vsync_proc(void* arg)
{
	while (adxm_vsync_act == 1) {
		VIWaitForRetrace();
		adxm_vsync_cnt++;
		adxt_vsync_cnt++;
		fn_80221CAC();
		if (adxm_mwidle_end == 0) {
			OSResumeThread(&adxm_mwidle_thread);
			if (adxm_mwidle_sleep_cb.func != NULL) {
				adxm_mwidle_sleep_cb.func(adxm_mwidle_sleep_cb.obj);
			}
		}
	}
	adxm_vsync_end = 1;
}

void adxm_fs_proc(void* arg)
{
	while (adxm_fs_act == 1) {
		VIWaitForRetrace();
		adxm_fs_cnt++;
		fn_80221C1C();
	}
	adxm_fs_end = 1;
}

void adxm_mwidle_proc(void* arg)
{
	while (adxm_mwidle_act == 1) {
		adxm_mwidle_cnt++;
		if (fn_80221AFC() == 0 || adxm_goto_border_flag == 1) {
			if (adxm_goto_border_flag == 1) {
				adxm_goto_border_flag = 0;
				OSSetThreadPriority(&adxm_mwidle_thread, adxm_save_tprm.prio_mwidle);
			}
			if (adxm_mwidle_sleep_cb.func != NULL) {
				adxm_mwidle_sleep_cb.func(adxm_mwidle_sleep_cb.obj);
			}
			OSSuspendThread(&adxm_mwidle_thread);
		}
	}
	adxm_mwidle_end = 1;
}

void ADXM_SetCbErr(SvmErrorFunc func, void* obj)
{
	fn_80221D5C(func, obj);
}

void ADXM_SetupThrd(ADXM_TPRM* tprm)
{
	const char* build = adxgc_build;

	if (adxm_init_level == 0) {
		fn_80221A64(build);
		fn_80221D4C(adxm_lock, 0);
		fn_80221D3C(adxm_unlock, 0);
		if (tprm == NULL) {
			adxm_save_tprm.prio_usr    = 16;
			adxm_save_tprm.prio_lock   = 1;
			adxm_save_tprm.prio_safe   = 8;
			adxm_save_tprm.prio_vsync  = 12;
			adxm_save_tprm.prio_fs     = 14;
			adxm_save_tprm.prio_mwidle = 24;
		} else {
			adxm_save_tprm = *tprm;
		}
		OSCreateThread(&adxm_safe_thread, (OSThreadFunc)adxm_safe_proc, 0,
		    adxm_stack_safe + sizeof(adxm_stack_safe), sizeof(adxm_stack_safe),
		    adxm_save_tprm.prio_safe, 1);
		OSCreateThread(&adxm_vsync_thread, (OSThreadFunc)adxm_vsync_proc, 0,
		    adxm_stack_vsync + sizeof(adxm_stack_vsync), sizeof(adxm_stack_vsync),
		    adxm_save_tprm.prio_vsync, 1);
		OSCreateThread(&adxm_fs_thread, (OSThreadFunc)adxm_fs_proc, 0,
		    adxm_stack_fs + sizeof(adxm_stack_fs), sizeof(adxm_stack_fs), adxm_save_tprm.prio_fs,
		    1);
		OSCreateThread(&adxm_mwidle_thread, (OSThreadFunc)adxm_mwidle_proc, 0,
		    adxm_stack_mwidle + sizeof(adxm_stack_mwidle), sizeof(adxm_stack_mwidle),
		    adxm_save_tprm.prio_mwidle, 1);
		adxm_main_thread = OSGetCurrentThread();
		adxm_fs_act      = 1;
		adxm_mwidle_act  = 1;
		adxm_vsync_act   = 1;
		adxm_safe_act    = 1;
		adxm_fs_end      = 0;
		adxm_mwidle_end  = 0;
		adxm_vsync_end   = 0;
		adxm_safe_end    = 0;
		adxm_set_prio    = 0;
		OSResumeThread(&adxm_vsync_thread);
		OSResumeThread(&adxm_fs_thread);
		OSResumeThread(&adxm_mwidle_thread);
		fn_80221E90(6, (s32 (*)(void*))adxm_goto_mwidle_border, 0);
	}
	adxm_init_level++;
}

s32 ADXM_IsSetupThrd(void)
{
	return adxm_init_level != 0;
}
