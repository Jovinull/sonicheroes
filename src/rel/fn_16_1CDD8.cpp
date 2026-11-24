extern "C" {
int fn_16_F20(void* game, int flag);
extern void* lbl_8042C180;
struct S {
	char pad[0xBC];
	short a;
	char pad2[0xE];
	int b;
};
int fn_16_1CDD8(S* p)
{
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return 0;
	if (p->b > p->a)
		return 1;
	return 0;
}
}
