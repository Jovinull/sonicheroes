// When fn_801281AC accepts state 3, copies the name (up to 0x20 bytes) into the buffer at +4, marks busy and records state 3; returns whether it was accepted.

extern "C" {
struct Card80128058 {
	char* p;
	int f4;
	int f8;
	int fc;
	int f10;
};
int fn_801281AC(Card80128058*, int);
char* strncpy(char*, const char*, unsigned);

int fn_80128058(Card80128058* o, const char* s)
{
	if (fn_801281AC(o, 3) != 0) {
		strncpy(o->p + 4, s, 0x20);
		o->f10 = 1;
		o->fc  = 3;
		return 1;
	}
	return 0;
}
}
