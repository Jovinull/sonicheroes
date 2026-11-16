class TObjSample
{
public:
	char pad[0x110];
	void* operator new(unsigned long);
};
extern "C" {
extern int lbl_8042C110;
TObjSample* fn_16_2AA4(TObjSample*, int);
void fn_16_3234()
{
	TObjSample* p = new TObjSample;
	if (p != 0) {
		p = fn_16_2AA4(p, lbl_8042C110);
	}
}
}
