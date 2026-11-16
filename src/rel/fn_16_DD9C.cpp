extern "C" void setFlagBits(void* word, unsigned int bits);

struct Obj {
	char* p;
};

extern "C" void fn_16_DD9C(register Obj* arg0, unsigned int arg1)
{
	setFlagBits(arg0->p + 0x18, arg1);
}
