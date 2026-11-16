struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_1528(void*, int);
extern int lbl_8042C110;
void fn_16_1874(void)
{
	void* p = __nw__10TObjSampleFUl(0xFC);
	if (p != 0) {
		p = fn_16_1528(p, lbl_8042C110);
	}
}
}
