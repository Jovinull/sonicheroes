// Calls the per-entry handler for every pair of the two counted loops.
struct Obj8017DE6C {
	unsigned char pad0[0x8C];
	unsigned int f8C;
	unsigned int f90;
};

extern "C" {
int fn_80191104();
void fn_8017D944(Obj8017DE6C* o, int a, int b);

void fn_8017DE6C(Obj8017DE6C* o, int* arr)
{
	int cnt;
	unsigned int j;
	unsigned int n;
	int i;
	int* p;
	cnt    = fn_80191104();
	n      = o->f8C;
	i      = 0;
	o->f90 = n;
	for (; i < cnt; i++) {
		p = arr;
		j = 0;
		for (; j < n; j++) {
			fn_8017D944(o, *p, 0);
			p++;
		}
	}
}
}
