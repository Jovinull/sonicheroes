typedef signed int s32;
typedef unsigned char u8;
extern "C" {
void fn_8003E2E4(s32, u8, s32, s32);
static inline void helper(s32 a, u8 b, s32 c, s32 d)
{
	fn_8003E2E4(a, b, c, d);
}
void fn_16_1E40(void* self, s32 arg1, u8 arg2, s32 arg3, s32 arg4)
{
	helper(arg1, arg2, arg3, arg4);
}
}
