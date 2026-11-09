// Calls fn_80146D6C on the object, decrements the counter at lbl_8042BCE0 + 4 and returns the object.

extern "C" {
struct Counter80145FD4 {
	int f0;
	int f4;
};
extern Counter80145FD4 lbl_8042BCE0;
void fn_80146D6C(int);

int fn_80145FD4(int o)
{
	fn_80146D6C(o);
	lbl_8042BCE0.f4 = lbl_8042BCE0.f4 - 1;
	return o;
}
}
