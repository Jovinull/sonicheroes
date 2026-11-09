// Follows the three-step lookup (arg1's table by arg2, its sub-table by arg3, arg0's table by the found key) and stores the final value into *arg4; returns arg1, or 0 if any step fails.

extern "C" {
struct Obj80205578 {
	unsigned char pad[0x10];
	int f10;
};
int* fn_8019472C(int, int);

int* fn_80205578(Obj80205578* o, int* a1, int a2, int a3, int* out)
{
	int* t;
	int* u;
	int* v;
	t = fn_8019472C(*a1, a2);
	if (t == 0) {
		return 0;
	}
	u = fn_8019472C(t[2], a3);
	if (u == 0) {
		return 0;
	}
	v = fn_8019472C(o->f10, *u);
	if (v == 0) {
		return 0;
	}
	*out = *v;
	return a1;
}
}
