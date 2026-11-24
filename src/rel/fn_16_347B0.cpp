extern "C" {
void* memset(void*, int, unsigned long);
void fn_16_347B0(register char* p)
{
	if (*(void**)(p + 0x30) != 0) {
		memset(*(void**)(p + 0x30), 0, 0x14);
	}
}
}
