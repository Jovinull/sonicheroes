typedef unsigned long u32;
class TObjSample;
extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(u32 size);
extern "C" void* fn_16_1C464(void* object, void* owner);

extern "C" void fn_16_1C844(void)
{
	void* p = __nw__10TObjSampleFUl(0xFC);
	if (p) {
		p = fn_16_1C464(p, lbl_8042C110);
	}
}
