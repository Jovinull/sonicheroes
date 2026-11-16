typedef int s32;
extern "C" void* lbl_8042C180;
extern "C" s32 fn_16_F20(void*, s32);

extern "C" void fn_16_24BD0(void)
{
	if (fn_16_F20(lbl_8042C180, 0x20) != 0) {
		return;
	}
}
