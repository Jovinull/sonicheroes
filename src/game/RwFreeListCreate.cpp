// Creates a free list: forwards its three arguments to fn_8019650C with the trailing flags (1, 0).

extern "C" {
void fn_8019650C(int, int, int, int, int);

void RwFreeListCreate(int a, int b, int c)
{
	fn_8019650C(a, b, c, 1, 0);
}
}
