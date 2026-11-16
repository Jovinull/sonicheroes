typedef unsigned int u32;
typedef int s32;
extern "C" {
void* fn_80131020(void*, s32, void*);
void fn_8004D9B8(void*);
extern void* lbl_8042C1F8;
void fn_16_4A5D0(char* self)
{
	if (lbl_8042C1F8 != 0 && *(void**)(self + 0xD4) == 0) {
		*(void**)(self + 0xD4) = fn_80131020(*(void**)(self + 0xC8), 0xA, self);
		fn_8004D9B8(lbl_8042C1F8);
	}
}
}
