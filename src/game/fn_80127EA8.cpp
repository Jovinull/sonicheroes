// When fn_801281AC accepts state 7, copies the name (0x20 bytes) into the buffer at +4, clears two fields of it (0xA8/0xAC), marks busy and records state 3; returns whether it was accepted.

extern "C" {
struct Buf80127EA8 {
	unsigned char pad[0xa8];
	int fa8;
	int fac;
};
struct Card80127EA8 {
	Buf80127EA8* p;
	int f4;
	int f8;
	int fc;
	int f10;
};
int fn_801281AC(void*, int);
char* strncpy(char*, const char*, unsigned);

int fn_80127EA8(Card80127EA8* o, const char* s)
{
	if (fn_801281AC(o, 7) != 0) {
		strncpy((char*)o->p + 4, s, 0x20);
		o->p->fa8 = 0;
		o->p->fac = 0;
		o->f10    = 1;
		o->fc     = 3;
		return 1;
	}
	return 0;
}
}
