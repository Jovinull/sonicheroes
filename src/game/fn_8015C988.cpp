// Returns 0 when fn_8015C648 returns 0, otherwise whether fn_8015DEB0 returns non-zero.

extern "C" {
int fn_8015C648();
int fn_8015DEB0();

int fn_8015C988()
{
	if (fn_8015C648() == 0) {
		return 0;
	}
	return fn_8015DEB0() != 0;
}
}
