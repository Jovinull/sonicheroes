extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_472FC(void*, int);
extern int lbl_8042C110;

void fn_16_47764(void)
{
	void* p = __nw__10TObjSampleFUl(0xF0);
	if (p != 0)
		p = fn_16_472FC(p, lbl_8042C110);
}
}
