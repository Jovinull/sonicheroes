// adx_errs: ADX error message formatting and callback dispatch.
// .text 0x80213020-0x80213670 (5 functions), .rodata 0x8023DFD8-0x8023DFDA (" "),
// .bss 0x80411230-0x80411358 (func, obj, ItoA scratch, message buffer).
// Boundary: MKD adx_errs.o (ItoA2, CallErrFunc2, CallErrFunc1, Finish, Init);
// all its .bss is used only by these functions.

#include "types.h"
#include "MSL_C/string.h"

typedef void (*AdxErrFunc)(void* object, const char* message);

extern char* strncat(char* destination, const char* source, u32 size);
extern void fn_80222464(const char* message, ...); /* SVM_CallErr */

AdxErrFunc adxerr_func = NULL;
void* adxerr_obj       = NULL;
char adxerr_msg[256];

static inline void adxerr_itoa(s32 value, s8* string, s32 length)
{
	static s8 buf[32];
	s32 i;
	s32 n;
	s32 l;

	for (i = 0; i < 32; i++) {
		string[i] = value % 10;
		value /= 10;
		if (value == 0) {
			string[i] = '\0';
			break;
		}
	}
	l = strlen((const char*)buf);
	n = length - 1;
	if (l < n) {
		n = l;
	}
	for (i = 0; i < n; i++) {
		string[i] = buf[n - 1 - i];
	}
	string[i] = '\0';
}

void ADXERR_Init(void)
{
	memset(adxerr_msg, 0, sizeof(adxerr_msg));
	adxerr_func = NULL;
	adxerr_obj  = NULL;
}

void ADXERR_Finish(void)
{
	memset(adxerr_msg, 0, sizeof(adxerr_msg));
	adxerr_func = NULL;
	adxerr_obj  = NULL;
}

void ADXERR_CallErrFunc1(const char* msg)
{
	strncpy(adxerr_msg, msg, sizeof(adxerr_msg) - 1);
	if (adxerr_func != NULL) {
		adxerr_func(adxerr_obj, adxerr_msg);
	}
	fn_80222464(adxerr_msg);
}

void ADXERR_CallErrFunc2(const char* msg1, const char* msg2)
{
	strncpy(adxerr_msg, msg1, sizeof(adxerr_msg) - 1);
	strncat(adxerr_msg, msg2, sizeof(adxerr_msg) - 1);
	if (adxerr_func != NULL) {
		adxerr_func(adxerr_obj, adxerr_msg);
	}
	fn_80222464(adxerr_msg);
}

void ADXERR_ItoA2(s32 value1, s32 value2, s8* string, s32 length)
{
	adxerr_itoa(value1, string, length);
	strncat((char*)string, " ", length - strlen((const char*)string) - 1);
	adxerr_itoa(value2, string + strlen((const char*)string), 4 - strlen((const char*)string));
}
