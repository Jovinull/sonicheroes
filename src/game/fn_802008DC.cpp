// Starts the shutdown job for the object, frees its handle and clears it.
extern "C" {
void fn_80194628(int);
void fn_80200874();
void fn_802011F8(int* p, void (*cb)(), int b, int* a);

int* fn_802008DC(int* p, int b)
{
	int sp = 1;
	fn_802011F8(p, fn_80200874, b, &sp);
	fn_80194628(*p);
	*p = 0;
	return p;
}
}
