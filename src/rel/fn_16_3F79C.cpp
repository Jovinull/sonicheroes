extern "C" {
void* memset(void*, int, unsigned long);
void fn_16_3F1CC(void*, void*);
struct S {
	char pad[0x2C];
	void* a[0x200];
};
void fn_16_3F79C(S* p)
{
	int i;
	for (i = 0; i < 0x200; i++) {
		fn_16_3F1CC(p, p->a[i]);
	}
	memset(p->a, 0, 0x800);
}
}
