extern "C" void fn_80150958(void*);
extern "C" void fn_16_1B0C8(register char* obj)
{
	if (*(void**)(obj + 0xEC) != 0) {
		fn_80150958(*(void**)(obj + 0xEC));
		*(void**)(obj + 0xEC) = 0;
	}
}
