// For the player with byte 0x761 == 0xB: clears the handle at 0xA74, releasing it with fn_8005FD8C(handle, -1) when fn_80017800 says it is still live.

extern "C" {
struct Obj80072964 {
	unsigned char pad[0x761];
	signed char c761;
	unsigned char pad1[0xa74 - 0x762];
	unsigned fa74;
};
int fn_80017800(unsigned);
void fn_8005FD8C(unsigned, int);

void fn_80072964(Obj80072964* o)
{
	if (o->c761 == 0xb) {
		if (o->fa74 != 0 && fn_80017800(o->fa74) == 0) {
			o->fa74 = 0;
			return;
		}
		if (o->fa74 != 0) {
			fn_8005FD8C(o->fa74, -1);
			o->fa74 = 0;
		}
	}
}
}
