// Packs nine fields of arg1 into one word of *arg0 (shifts 0, 2, 4, 7, 11, 14, 17, 18, 19).

extern "C" {
struct Bits801439E0 {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	unsigned char g;
	unsigned char h;
	unsigned char pad[2];
	int i;
};

void fn_801439E0(int* out, Bits801439E0* p)
{
	int u = p->a;
	u |= p->b << 2;
	u |= p->c << 4;
	u |= p->d << 7;
	u |= p->e << 11;
	u |= p->f << 14;
	u |= p->g << 17;
	u |= p->h << 18;
	u |= p->i << 19;
	*out = u;
}
}
