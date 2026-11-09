// Allocates size bytes with malloc and, on failure, reports it through fn_8017C5A8; returns the pointer.

extern "C" {
int malloc(int);
void fn_8017C5A8(int, void*);
extern unsigned char lbl_8028ECB8[];

int fn_8017CE20(int a, int size)
{
	int p = malloc(size);
	if (p == 0) {
		fn_8017C5A8(a, lbl_8028ECB8);
	}
	return p;
}
}
