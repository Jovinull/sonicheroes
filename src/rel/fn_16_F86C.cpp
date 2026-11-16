struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_F454(void*, int);
extern int lbl_8042C110;
void fn_16_F86C(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p != 0) {
		p = fn_16_F454(p, lbl_8042C110);
	}
}
}
