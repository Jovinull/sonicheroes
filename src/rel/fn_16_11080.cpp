extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_10F04(void*, void*);
extern void* lbl_8042C110;
void fn_16_11080(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p != 0) {
		p = fn_16_10F04(p, lbl_8042C110);
	}
}
}
