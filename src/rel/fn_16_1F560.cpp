typedef signed char s8;
typedef unsigned char u8;
typedef int s32;
extern "C" s32 fn_16_331C(u8 kind);
struct S {
	char pad[0xB8];
	s8 a;
	u8 b;
};
extern "C" s32 fn_16_1F560(register S* p)
{
	if (p->a == 0 || p->a == 1 || p->a == 2) {
		return 0;
	}
	if (fn_16_331C(p->b) != 0) {
		return 1;
	}
	return 0;
}
