class TObjSample
{
public:
	char pad[0xF4];
	void* operator new(unsigned long);
};
extern "C" {
extern int lbl_8042C110;
TObjSample* fn_16_AA88(TObjSample*, int);
void fn_16_ADFC()
{
	TObjSample* p = new TObjSample;
	if (p != 0) {
		p = fn_16_AA88(p, lbl_8042C110);
	}
}
}
