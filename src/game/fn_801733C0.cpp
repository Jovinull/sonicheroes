// Sets or clears flag 4 of the word at 8 depending on whether the argument is 1.

extern "C" {
struct Obj801733C0 {
	unsigned char pad[8];
	unsigned f8;
};

void fn_801733C0(Obj801733C0* o, int v)
{
	if (v == 1) {
		o->f8 |= 4;
		return;
	}
	o->f8 &= ~4u;
}
}
