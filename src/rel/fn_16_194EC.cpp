extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" void fn_80150958(void* clump);
extern char* lbl_8042C1D0;

extern "C" void fn_16_194EC(char* self)
{
	int i;
	for (i = 0; i < 2; i++) {
		if (*(void**)(self + 0x144 + i * 4) != 0) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7274), *(void**)(self + 0x144 + i * 4));
			fn_80150958(*(void**)(self + 0x144 + i * 4));
			*(void**)(self + 0x144 + i * 4) = 0;
		}
	}
}
