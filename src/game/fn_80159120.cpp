// Allocates the list slot for the given index and links its two list heads to themselves.
struct G80159120 {
	int f0;
	int f4;
};
struct L80159120 {
	L80159120* next;
	L80159120* prev;
};
struct S80159120 {
	unsigned int f0;
};

extern "C" {
extern G80159120 lbl_8042C910;
extern char* lbl_8042C9A4;
extern char lbl_803EC630[];
int fn_8015BFA4();
int fn_801966CC(int a, int b, int c, int d, char* e);

int fn_80159120(int a, int b)
{
	lbl_8042C910.f0 = b;
	if (fn_8015BFA4() == 0) {
		return 0;
	}
	*(int*)(lbl_8042C9A4 + lbl_8042C910.f0) = fn_801966CC(0x10, 8, 4, 1, lbl_803EC630);
	S80159120* s                            = (S80159120*)(lbl_8042C9A4 + lbl_8042C910.f0);
	if (s->f0 == 0) {
		return 0;
	}
	L80159120* l     = (L80159120*)((char*)s + 4);
	l->next          = l;
	char* t          = lbl_8042C9A4 + lbl_8042C910.f0;
	*(char**)(t + 8) = t + 4;
	lbl_8042C910.f4++;
	return a;
}
}
