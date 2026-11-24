extern "C" {
typedef signed char s8;
extern void* lbl_8042C180;
int fn_16_F20(void*, int);
int fn_16_1F5DC(void*);
int fn_16_1F608(void*);
int fn_16_1F634(char* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x1F)) {
		return 0;
	}
	switch ((s8)obj[0xB8]) {
		case 0:
		case 3:
			return 1;
		case 1:
		case 4:
			return fn_16_1F5DC(obj);
		case 2:
		case 5:
			return fn_16_1F608(obj);
		default:
			return 1;
	}
}
}
