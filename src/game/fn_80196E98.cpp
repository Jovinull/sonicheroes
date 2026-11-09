// Allocates a*b bytes with malloc, zeroes them and returns the pointer (0 when the allocation fails).

extern "C" {
int malloc(int);
void* memset(void*, int, int);

int fn_80196E98(int a, int b)
{
	int n = a * b;
	int p = malloc(n);
	if (p != 0) {
		memset((void*)p, 0, n);
	}
	return p;
}
}
