// Loads the texture dictionary file and fills every list entry's handle: from the dictionary (fn_801A4BBC) when it loaded, otherwise by name lookup with fn_801A4CF0 then fn_801AB834; returns the dictionary.
struct Ent8005FAE8 {
	unsigned int f0;
	int f4;
};
struct List8005FAE8 {
	Ent8005FAE8* f0;
	unsigned int f4;
};

extern "C" {
unsigned int texLoadTexDictionaryFile__FPc(char* path);
unsigned int fn_801A4CF0(int a, int b);
unsigned int fn_801AB834(int a, int b);
unsigned int fn_801A4BBC(unsigned int a, int b);

unsigned int fn_8005FAE8(char* path, List8005FAE8* l)
{
	unsigned int i;
	Ent8005FAE8* p;
	unsigned int t;
	t = texLoadTexDictionaryFile__FPc(path);
	if (t == 0) {
		p = l->f0;
		i = 0;
		while (i < l->f4) {
			p->f0 = fn_801A4CF0(p->f4, 0);
			if (p->f0 == 0) {
				p->f0 = fn_801AB834(p->f4, 0);
			}
			i++;
			p++;
		}
	} else {
		unsigned int j;
		Ent8005FAE8* q;
		q = l->f0;
		j = 0;
		while (j < l->f4) {
			q->f0 = fn_801A4BBC(t, q->f4);
			j++;
			q++;
		}
	}
	return t;
}
}
