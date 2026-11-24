extern "C" void* __nw__10TObjSampleFUl(unsigned long);
extern "C" void* fn_16_7570(void*, int);
extern int lbl_8042C110;
extern "C" void fn_16_7894(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p != 0) {
		p = fn_16_7570(p, lbl_8042C110);
	}
}
