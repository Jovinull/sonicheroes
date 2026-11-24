typedef unsigned int u32;
extern "C" void* memset(void*, int, unsigned long);

extern "C" void fn_16_4540(char* p)
{
	if (*(void**)(p + 0x30) != 0) {
		memset(*(void**)(p + 0x30), 0, 0x14);
	}
}
