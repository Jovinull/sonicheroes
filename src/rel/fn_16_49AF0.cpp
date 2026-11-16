extern "C" void* __nw__10TObjSampleFUl(unsigned long);
extern "C" void* fn_16_49820(void*, int);
extern int lbl_8042C110;

extern "C" void fn_16_49AF0(void)
{
	void* p = __nw__10TObjSampleFUl(0x108);
	if (p != 0) {
		p = fn_16_49820(p, lbl_8042C110);
	}
}
