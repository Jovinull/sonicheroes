// Runs the three init stages in order; if one fails, rolls back with fn_8015CA74, fn_8015CB68 and fn_8015C9D0 and returns 0, otherwise 1.

extern "C" {
int fn_8015C9C8(void);
int fn_8015CAC8(void);
int fn_8015C9D4(void);
void fn_8015CA74(void);
void fn_8015CB68(void);
void fn_8015C9D0(void);

int fn_8015BFA4(void)
{
	int r = fn_8015C9C8();
	if (r != 0) {
		r = fn_8015CAC8();
	}
	if (r != 0) {
		r = fn_8015C9D4();
	}
	if (r != 0) {
		return 1;
	}
	fn_8015CA74();
	fn_8015CB68();
	fn_8015C9D0();
	return 0;
}
}
