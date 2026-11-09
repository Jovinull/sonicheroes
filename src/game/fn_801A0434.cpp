// Runs fn_8019FE30(arg0, 0x14, fn_801A0334, &sp8) and returns the value it wrote to sp8 (initially 0).

extern "C" {
extern unsigned char fn_801A0334[];
int fn_8019FE30(int, int, void*, int*);

int fn_801A0434(int a)
{
	int sp8 = 0;
	fn_8019FE30(a, 0x14, fn_801A0334, &sp8);
	return sp8;
}
}
