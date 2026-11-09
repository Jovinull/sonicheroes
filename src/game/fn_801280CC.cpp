// When fn_801281AC accepts state 2, copies the name (0x20 bytes) into the buffer at +4, stores the three values at 0x24/0x28/0x2C, marks busy and records state 3; returns whether it was accepted.

extern "C" {
struct Card801280CC {
	char* p;
	int f4;
	int f8;
	int fc;
	int f10;
	unsigned char pad[0x24 - 0x14];
	int f24;
	int f28;
	int f2c;
};
int fn_801281AC(void*, int);
char* strncpy(char*, const char*, unsigned);

int fn_801280CC(Card801280CC* o, const char* s, int a, int b, int c)
{
	if (fn_801281AC(o, 2) != 0) {
		strncpy(o->p + 4, s, 0x20);
		o->f24 = a;
		o->f28 = b;
		o->f2c = c;
		o->f10 = 1;
		o->fc  = 3;
		return 1;
	}
	return 0;
}
}
