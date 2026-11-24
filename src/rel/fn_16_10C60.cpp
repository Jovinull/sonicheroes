extern "C" {
extern void* lbl_8042C388;
void fn_800B52E8(void*, int, int, int);
void fn_16_10C60(void)
{
	if (lbl_8042C388 != 0) {
		fn_800B52E8(lbl_8042C388, 0x1048, 0, 0);
	}
}
}
