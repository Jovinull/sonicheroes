// When the entry is idle (+0x2C clear, +0x58 == -1) and fn_80110FC4 accepts (arg1, arg2), starts it with fn_80110CC8; returns whether it started.

extern "C" {
struct Obj80111260 {
	unsigned char pad[0x2c];
	unsigned f2c;
	unsigned char pad1[0x58 - 0x30];
	int f58;
};
int fn_80110FC4(void*, int, int, int);
void fn_80110CC8(void*, int, int, int);

int fn_80111260(Obj80111260* o, int a, int b)
{
	if (o->f2c != 0 || o->f58 != -1) {
		return 0;
	}
	if (fn_80110FC4(o, a, b, 0) != 0) {
		fn_80110CC8(o, a, b, 0);
		return 1;
	}
	return 0;
}
}
