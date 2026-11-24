extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_27504(void*, int);
extern int lbl_8042C110;
void fn_16_27ABC(void)
{
	void* p = __nw__10TObjSampleFUl(0x100);
	if (p != 0) {
		p = fn_16_27504(p, lbl_8042C110);
	}
}
}
