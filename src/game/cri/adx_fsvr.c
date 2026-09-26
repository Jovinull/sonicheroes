// adx_fsvr: ADXT file-system server pass.
// .text 0x80213670-0x802136F4 (1 function), .bss 0x80411358-0x8041135C.
// Boundary: MKD adx_fsvr.o; adxt_fssvr_enter_cnt is private to it.

#include "types.h"

extern void ADXCRS_Lock(void);
extern void ADXCRS_Unlock(void);
extern void ADXSTM_ExecServer(void);
extern void cvFsExecServer(void);
extern void ADXF_ExecServer(void);

s32 adxt_fssvr_enter_cnt;

void ADXT_ExecFsSvr(void)
{
	ADXCRS_Lock();
	if (adxt_fssvr_enter_cnt != 0) {
		ADXCRS_Unlock();
		return;
	}
	adxt_fssvr_enter_cnt = 1;
	ADXCRS_Unlock();
	ADXSTM_ExecServer();
	adxt_fssvr_enter_cnt = 2;
	cvFsExecServer();
	adxt_fssvr_enter_cnt = 5;
	ADXSTM_ExecServer();
	adxt_fssvr_enter_cnt = 6;
	ADXF_ExecServer();
	adxt_fssvr_enter_cnt = 0;
}
