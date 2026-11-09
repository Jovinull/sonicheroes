// Runs fn_8017E708, then fn_8017BF08 with the three arguments.

extern "C" {
void fn_8017E708();
void fn_8017BF08(int, int, int);

void fn_80185F6C(int a, int b, int c)
{
	fn_8017E708();
	fn_8017BF08(a, b, c);
}
}
