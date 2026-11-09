// Like fn_80111260 but with slot -1: when idle and fn_80110FC4 accepts (-1, arg1), starts it with fn_80110CC8; returns whether it started.

extern "C" {
struct Obj801112F0 {
	unsigned char pad[0x2c];
	unsigned f2c;
	unsigned char pad1[0x58 - 0x30];
	int f58;
};
int fn_80110FC4(void*, int, int, int);
void fn_80110CC8(void*, int, int, int);

int fn_801112F0(Obj801112F0* o, int b)
{
	if (o->f2c != 0 || o->f58 != -1) {
		return 0;
	}
	if (fn_80110FC4(o, -1, b, 0) != 0) {
		fn_80110CC8(o, -1, b, 0);
		return 1;
	}
	return 0;
}
}
