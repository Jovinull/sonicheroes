extern "C" void setFlagBits(void* word, unsigned int bits);
struct S {
	char* p;
};
extern "C" void fn_16_74B8(register S* arg0)
{
	setFlagBits(arg0->p + 0x18, 0x10000);
}
