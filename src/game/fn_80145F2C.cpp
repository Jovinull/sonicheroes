// Initialises the 0x129 plugin chain (fn_80146778, fn_801467E4, fn_80143818, fn_80145EB4), returning 0 as soon as one stage fails.

extern "C" {
int fn_80146778(void);
int fn_801467E4(int, int, int);
int fn_80143818(void);
int fn_80145EB4(void);

int fn_80145F2C(void)
{
	if (fn_80146778() == 0) {
		return 0;
	}
	if (fn_801467E4(6, 0x129, 0xc) == 0) {
		return 0;
	}
	if (fn_80143818() == 0) {
		return 0;
	}
	return fn_80145EB4();
}
}
