// Prints formatted text into a menu text object (HYPOTHESIS; names inferred): when the object has a
// string holder (0x4) and a format is given, formats into a 128-byte buffer, terminates it, and
// copies at most the object's length (0x8) characters into the holder's text (fn_80172A1C),
// terminating it there.
#include "types.h"
#include "Runtime.PPCEABI.H/__va_arg.h"

struct Text8012C858 {
	u8 pad0[0x4];
	void* holder; // 0x4
	s32 length;   // 0x8
};

extern "C" {
int vsprintf(char* buffer, const char* format, __va_list args);
char* strncpy(char* dst, const char* src, u32 size);
char* fn_80172A1C(void* holder);

void fn_8012C858(Text8012C858* text, const char* format, ...)
{
	__va_list args;
	char buffer[128];

	if (text->holder != 0 && format != 0) {
		char* dst;
		__builtin_va_info(args);
		vsprintf(buffer, format, args);
		buffer[127] = 0;
		dst         = fn_80172A1C(text->holder);
		if (dst != 0) {
			strncpy(dst, buffer, text->length);
			dst[text->length] = 0;
		}
	}
}
}
