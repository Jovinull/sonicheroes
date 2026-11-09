// Registers the callbacks fn_800B8D68 and fn_800B8D98 for the object with fn_80159E9C and fn_80159E18.

extern "C" {
void fn_800B8D68();
void fn_800B8D98();
void fn_80159E9C(int, void (*)(), int);
void fn_80159E18(int, void (*)(), int);

void fn_800B8D1C(int a)
{
	fn_80159E9C(a, fn_800B8D68, 0);
	fn_80159E18(a, fn_800B8D98, 0);
}
}
