typedef int s32;

typedef struct Obj {
	char unk0[0x174];
	s32 unk174;
	s32 unk178;
} Obj;

extern "C" void fn_16_4A63C(Obj* arg0);
extern "C" void fn_16_4A684(Obj* arg0);
extern "C" void fn_16_4A7C8(Obj* arg0);

extern "C" void fn_16_4ABD0(Obj* arg0)
{
	switch (arg0->unk174) {
		case 1:
			fn_16_4A7C8(arg0);
			break;
		case 2:
			fn_16_4A684(arg0);
			break;
		case 3:
			fn_16_4A63C(arg0);
			break;
		default:
			return;
	}
	arg0->unk178 = arg0->unk178 + 1;
}
