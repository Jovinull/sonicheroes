typedef unsigned long u32;
extern "C" {
void* __nw__10TObjSampleFUl(u32);
void* fn_16_1B1E4(void*, void*);
extern void* lbl_8042C110;
void fn_16_1B4E0(void)
{
	void* p = __nw__10TObjSampleFUl(0xF0);
	if (p)
		p = fn_16_1B1E4(p, lbl_8042C110);
}
}
