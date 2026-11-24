struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_BA40(void*, int);
extern int lbl_8042C110;
void fn_16_BE88(void)
{
	void* p = __nw__10TObjSampleFUl(0x6C);
	if (p != 0) {
		p = fn_16_BA40(p, lbl_8042C110);
	}
}
}
