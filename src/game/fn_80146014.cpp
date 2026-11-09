// Trivial accessor.

extern "C" {
struct S4 {
	unsigned char pad[0x6c];
	int f6c;
	unsigned char pad1[0x84 - 0x70];
	int f84;
};

void fn_80146014(int a, int b)
{
	*(int*)(a + b) = 0;
}
}
