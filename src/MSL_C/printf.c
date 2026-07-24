#include "MSL_C/file_io.h"
#include "Runtime.PPCEABI.H/__va_arg.h"
#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// This compiler has no va_start: spelling it that way is taken as an implicit
// function and comes out as a call, which wrecks the frame. __builtin_va_info
// is the one that expands inline to the EABI gpr/fpr counts and the two area
// pointers.

// The formatter hands finished runs of characters to a write procedure along
// with an opaque object. For the string family that object is this control
// block: where to write, how much room is left, and how much has been used.
typedef struct {
	char* CharStr;
	u32 MaxCharCount;
	u32 CharsWritten;
} __OutStrCtrl;

// The formatter's write procedure returns the object on success and null on
// failure, so its result is only ever tested for being non null.
typedef void* (*__OutputProc)(void* object, const char* buffer, s32 n);

void* __StringWrite(void* object, const char* buffer, s32 n);
void* __FileWrite(void* object, const char* buffer, s32 n);
s32 __pformatter(__OutputProc WriteProc, void* object, const char* format, _va_list_struct* args);
void* memcpy(void* dst, const void* src, u32 n);
u32 fwrite(const void* ptr, u32 size, u32 count, FILE* file);

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

s32 snprintf(char* s, u32 n, const char* format, ...)
{
	__va_list args;
	__OutStrCtrl arg;
	s32 result;

	__builtin_va_info(args);

	arg.CharStr      = s;
	arg.MaxCharCount = n;
	arg.CharsWritten = 0;

	result = __pformatter(__StringWrite, &arg, format, args);

	if (s) {
		s32 i = n - 1;
		if ((u32)result < n)
			i = result;
		s[i] = 0;
	}

	return result;
}

s32 vsprintf(char* s, const char* format, __va_list args)
{
	__OutStrCtrl arg;
	s32 result;

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

s32 vprintf(const char* format, __va_list args)
{
	FILE* file = &__files[1];

	if (fwide(file, -1) >= 0)
		return -1;

	return __pformatter(__FileWrite, file, format, args);
}

s32 printf(const char* format, ...)
{
	__va_list args;
	FILE* file = &__files[1];

	if (fwide(file, -1) >= 0)
		return -1;

	__builtin_va_info(args);

	return __pformatter(__FileWrite, file, format, args);
}

void* __StringWrite(void* object, const char* buffer, s32 n)
{
	__OutStrCtrl* ctrl = (__OutStrCtrl*)object;
	u32 len            = ctrl->MaxCharCount - ctrl->CharsWritten;

	if (ctrl->CharsWritten + n <= ctrl->MaxCharCount)
		len = n;

	memcpy(ctrl->CharStr + ctrl->CharsWritten, buffer, len);
	ctrl->CharsWritten += len;
	return (void*)1;
}

void* __FileWrite(void* object, const char* buffer, s32 n)
{
	if (fwrite(buffer, 1, n, (FILE*)object) == n)
		return object;

	return 0;
}
