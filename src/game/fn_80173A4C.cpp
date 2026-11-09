// Returns the entry fn_8019472C gives for the id at 0xAC, dereferenced once more when flag 1 of the word at 8 is set.

extern "C" {
struct Obj80173A4C {
	unsigned char pad[8];
	int f8;
	unsigned char pad1[0xac - 0xc];
	int fac;
};
int* fn_8019472C(int);

int* fn_80173A4C(Obj80173A4C* o)
{
	if ((o->f8 & 1) == 1) {
		return (int*)*fn_8019472C(o->fac);
	}
	return fn_8019472C(o->fac);
}
}
