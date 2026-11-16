typedef unsigned int u32;
extern "C" {
void fn_800B52E8(u32, int, int, int);
extern u32 lbl_8042C388;
void fn_16_10348(void)
{
	if (lbl_8042C388 != 0) {
		fn_800B52E8(lbl_8042C388, 0x1046, 0, 0);
	}
}
}
