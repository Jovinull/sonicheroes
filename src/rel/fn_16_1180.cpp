#include "types.h"

struct C_COLLI {
	void Entry();
};
extern "C" void copyVec3(void* dst, void* src);
extern "C" void fn_16_900(void* dst, void* src);

extern "C" void fn_16_1180(char* self, void* volatile a, void* volatile b)
{
	copyVec3(self + 0x7C, self + 0x60);
	copyVec3(self + 0x60, a);
	fn_16_900(self + 0x6C, b);
	((C_COLLI*)self)->Entry();
}
