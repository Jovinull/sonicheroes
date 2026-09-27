// CRI ADXF init/finish (adx_fini).
//
// .text 0x8021BCF0..0x8021BE38 (ADXF_Finish, ADXF_Init),
// .rodata 0x8023E9D8..0x8023EA0C ("ADXF/GC Ver.7.07" banner and its volatile
// pointer; the next 4 bytes are alignment),
// .bss 0x8041C830..0x8041D1A8 (all ADXF globals: init count, partition-load
// state, command history, OCBI switch, partition table, 16 handles).
//
// Boundary: own banner; MKD adx_fini.o holds the same functions and defines
// the ADXF globals. The globals are uninitialized, so -inline deferred lays
// them out in reverse declaration order; they are declared reversed here.

#include "types.h"
#include "MSL_C/string.h"

typedef struct ADXF_CMD_HSTRY {
	u8 cmdid;
	u8 fg;
	u16 ncall;
	void* obj;
	s32 prm1;
	s32 prm2;
} ADXF_CMD_HSTRY;

typedef struct ADXF_OBJ {
	u8 used;
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

extern void ADXF_CloseAll(void);

/* -inline deferred lays uninitialized data out in reverse declaration order */
ADXF_OBJ adxf_obj[16];
void* adxf_ptinfo[256];
s32 adxf_ocbi_fg;
ADXF_CMD_HSTRY adxf_cmd_hstry[16];
u16 adxf_cmd_ncall[16];
s32 adxf_hstry_no;
s32 adxf_flno;
void* adxf_ldptnw_hn;
s32 adxf_ldptnw_ptid;
s32 adxf_init_cnt;

static const char adxf_build_str[]    = "\nADXF/GC Ver.7.07 Build:May  9 2003 17:10:05\n";
const char* const volatile adxf_build = adxf_build_str;

void ADXF_Init(void)
{
	adxf_build;
	if (adxf_init_cnt == 0) {
		memset(adxf_obj, 0, sizeof(adxf_obj));
		memset(adxf_ptinfo, 0, sizeof(adxf_ptinfo));
		memset(adxf_cmd_hstry, 0xFF, sizeof(adxf_cmd_hstry));
		memset(adxf_cmd_ncall, 0, sizeof(adxf_cmd_ncall));
		adxf_hstry_no    = 0;
		adxf_ocbi_fg     = 0;
		adxf_flno        = 0;
		adxf_ldptnw_hn   = NULL;
		adxf_ldptnw_ptid = -1;
	}
	adxf_init_cnt++;
}

void ADXF_Finish(void)
{
	if (--adxf_init_cnt == 0) {
		ADXF_CloseAll();
		adxf_ldptnw_ptid = -1;
		adxf_ldptnw_hn   = NULL;
		adxf_flno        = 0;
		adxf_ocbi_fg     = 0;
		adxf_hstry_no    = 0;
		memset(adxf_cmd_ncall, 0, sizeof(adxf_cmd_ncall));
		memset(adxf_cmd_hstry, 0xFF, sizeof(adxf_cmd_hstry));
		memset(adxf_ptinfo, 0, sizeof(adxf_ptinfo));
		memset(adxf_obj, 0, sizeof(adxf_obj));
	}
}
