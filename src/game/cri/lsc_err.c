#include "cri/lsc.h"
#include "cri/sjcrs.h"
#include "MSL_C/stdio.h"

// LSC error reporting and critical-section adapters: four surviving functions.
// The boundary is inferred; original source-file names are unavailable.

static LscErrorCallback lbl_80420770 = NULL;
static void* lsc_ErrObj              = NULL;
static char lsc_ErrMsg[0x100];

void fn_8021F410(const char* format, ...)
{
	__va_list args;
	LscErrorCallback callback;

	__builtin_va_info(args);
	vsprintf(lsc_ErrMsg, format, args);
	callback = lbl_80420770;

	if (callback != NULL) {
		callback(lsc_ErrObj, lsc_ErrMsg);
	}
}

void fn_8021F4D0(LscErrorCallback callback, void* object)
{
	if (callback == NULL) {
		lbl_80420770 = NULL;
		lsc_ErrObj   = NULL;
	} else {
		lbl_80420770 = callback;
		lsc_ErrObj   = object;
	}
}

void fn_8021F504(void* crs)
{
	fn_80220544();
}

void fn_8021F524(void* crs)
{
	fn_80220590();
}
