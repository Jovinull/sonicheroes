struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_23AA0(void*, int);
extern int lbl_8042C110;
void fn_16_23D4C(void)
{
	void* p = __nw__10TObjSampleFUl(0xF4);
	if (p != 0) {
		p = fn_16_23AA0(p, lbl_8042C110);
	}
}
}
