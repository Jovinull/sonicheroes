struct Obj {
	char pad[0xBA];
	short a;
	char pad2[0x10];
	int b;
};
extern "C" int fn_16_F20(void*, int);
extern void* lbl_8042C180;

extern "C" int fn_16_1F4F8(register Obj* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x1F)) {
		return 0;
	}
	if (obj->b > obj->a) {
		return 1;
	}
	return 0;
}
