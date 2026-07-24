#include "Runtime.PPCEABI.H/__va_arg.h"
#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// The formatter hands finished runs of characters to a write procedure along
// with an opaque object. For the string family that object is this control
// block: where to write, how much room is left, and how much has been used.
typedef struct {
	char* CharStr;
	s32 MaxCharCount;
	s32 CharsWritten;
} __OutStrCtrl;

s32 __StringWrite(const char* buffer, s32 n, void* object);
s32 __pformatter(s32 (*WriteProc)(const char*, s32, void*), void* object, const char* format,
    _va_list_struct* args);

s32 sprintf(char* s, const char* format, ...)
{
	__va_list args;
	__OutStrCtrl arg;
	s32 result;

	__builtin_va_info(args);

	arg.CharStr      = s;
	arg.MaxCharCount = -1;
	arg.CharsWritten = 0;

	result = __pformatter(__StringWrite, &arg, format, args);

	if (s) {
		s32 i = -2;
		if ((u32)result < 0xFFFFFFFF)
			i = result;
		s[i] = 0;
	}

	return result;
}
