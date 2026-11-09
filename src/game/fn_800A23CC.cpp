// Clears the result word (0xC) of the second argument, calls fn_800A2404 and returns the word.

extern "C" {
struct Obj800A23CC {
	unsigned char pad[0xc];
	int c;
};
void fn_800A2404(int, Obj800A23CC*);

int fn_800A23CC(int a, Obj800A23CC* b)
{
	b->c = 0;
	fn_800A2404(a, b);
	return b->c;
}
}
