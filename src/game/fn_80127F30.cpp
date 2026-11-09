// When fn_801281AC accepts state 5, copies the name (0x20 bytes) into the buffer at +4, stores the two values at 0x24/0x28, marks busy and records state 3; returns whether it was accepted.

extern "C" {
struct Card80127F30 {
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

int fn_80127F30(Card80127F30* o, const char* s, int a, int b)
{
	if (fn_801281AC(o, 5) != 0) {
		strncpy(o->p + 4, s, 0x20);
		o->f24 = a;
		o->f28 = b;
		o->f10 = 1;
		o->fc  = 3;
		return 1;
	}
	return 0;
}
}
