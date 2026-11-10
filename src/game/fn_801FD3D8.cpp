// Builds the screen object, hooks its update callback, publishes it in the global and returns the argument.
struct N801FD3D8 {
	unsigned char pad0[0x2C];
	int f2C;
	int f30;
};

extern "C" {
extern N801FD3D8* lbl_8042CF50;
N801FD3D8* fn_801B3984();
int fn_801B4EB4();
int* fn_8015D4B8();
void fn_801B52BC(int a, int b, int* c, int d, ...);
void fn_801B43EC();
int fn_801B51B8(N801FD3D8* o, int a, int b, int c);
void fn_801FDADC();
void fn_8015C388(int a, void (*f)());
void fn_8015C358(int a, int b);
void fn_8015C370(int a, int b);

int fn_801FD3D8(int a)
{
	N801FD3D8* o;
	int s;
	int* p;
	o      = fn_801B3984();
	o->f2C = 0x12F;
	o->f30 = 0;
	int t  = fn_801B4EB4();
	p      = fn_8015D4B8();
	fn_801B52BC(t, 0, p, 0);
	fn_801B43EC();
	s = fn_801B51B8(o, *p, 0, 0);
	fn_8015C388(s, fn_801FDADC);
	fn_8015C358(s, 0);
	fn_8015C370(s, 0);
	lbl_8042CF50 = o;
	return a;
}
}
