extern "C" {
void* memset(void*, int, unsigned long);
struct S {
	char pad[0x30];
	void* p;
};
void fn_16_2EB8(S* s)
{
	if (s->p != 0) {
		memset(s->p, 0, 1);
	}
}
}
