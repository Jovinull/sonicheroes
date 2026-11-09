// Stores the result of fn_8017BC74(0, 0, 0) in the object at 0xD0.

extern "C" {
struct Obj8017BECC {
	unsigned char pad[0xd0];
	int d0;
};
int fn_8017BC74(int, int, int);

void fn_8017BECC(Obj8017BECC* o)
{
	o->d0 = fn_8017BC74(0, 0, 0);
}
}
