extern "C" {
extern int lbl_8042C180;
int fn_16_F20(int, int);
int fn_16_1F490(register char* arg0)
{
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return 0;
	if (*(int*)(arg0 + 0xCC) > *(short*)(arg0 + 0xBC))
		return 1;
	return 0;
}
}
