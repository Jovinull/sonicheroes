extern "C" {
int fn_16_F20(void* game, int flag);
extern void* lbl_8042C180;

struct Obj {
	char pad[0xBA];
	short sBA;
	char pad2[0xCC - 0xBC];
	int iCC;
};

int fn_16_1CE40(register Obj* obj)
{
	if (fn_16_F20(lbl_8042C180, 0x1F)) {
		return 0;
	}
	if (obj->iCC > obj->sBA) {
		return 1;
	}
	return 0;
}
}
