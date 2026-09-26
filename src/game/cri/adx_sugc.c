// CRI ADXGC SDK glue: DVD file system setup (adx_sugc).
//
// .text 0x8021B274..0x8021B358 (ADXGC_SetupDvdFs, adxgc_err_dvd),
// .rodata 0x8023E950..0x8023E998 ("ADXGCSDK Ver.05Sep2002Patch2" banner, its
// volatile pointer, "MFS", "GCD"). No .data/.bss.
//
// Boundary: own banner; MKD adx_sugc.o holds the same two functions; the next
// word (0x8023E998) is adx_dcd5's table.

#include "types.h"

typedef struct ADXGC_DVDFS_PRM {
	s32 rdmode;
} ADXGC_DVDFS_PRM;

typedef void* (*CvFsGetIfFn)(void);
typedef void (*CvFsErrFn)(void* obj, const char* msg, void* hn);

extern void cvFsEntryErrFunc(CvFsErrFn func, void* obj);
extern void cvFsAddDev(const char* name, CvFsGetIfFn getif, void* work);
extern void cvFsSetDefDev(const char* name);
extern void* fn_80223410(void);                           /* mfCiGetInterface */
extern void* fn_8021F398(void);                           /* gcCiGetInterface */
extern void fn_8021F404(s32 a, s32 b, s32 c, s32 rdmode); /* gcCiSetRdMode */
extern void fn_8021357C(const char* msg);                 /* ADXERR_CallErrFunc1 */

const char* const volatile adxgcsdk_build
    = "\nADXGCSDK Ver.05Sep2002Patch2 Build:May  9 2003 17:11:18\n";

void adxgc_err_dvd(void* obj, const char* msg, void* hn);

void adxgc_err_dvd(void* obj, const char* msg, void* hn)
{
	fn_8021357C(msg);
}

void ADXGC_SetupDvdFs(ADXGC_DVDFS_PRM* prm)
{
	adxgcsdk_build;
	cvFsEntryErrFunc(adxgc_err_dvd, 0);
	cvFsAddDev("MFS", fn_80223410, 0);
	cvFsEntryErrFunc(adxgc_err_dvd, 0);
	cvFsAddDev("GCD", fn_8021F398, 0);
	cvFsSetDefDev("GCD");
	if (prm != NULL) {
		fn_8021F404(0, 0, 0, prm->rdmode);
	} else {
		fn_8021F404(0, 0, 0, 0);
	}
}
