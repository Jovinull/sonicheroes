// Dispatches on the mode word at *arg0 (1..4) to its handler and returns the handler's result; any other mode returns 0.

extern "C" {
int fn_801729BC(void);
int fn_80173644(void);
int fn_80173878(void);
int fn_801750B8(void);

int fn_80172F94(int* o)
{
	switch (*o) {
		case 0:
			return 0;
		case 1:
			return fn_80173878();
		case 2:
			return fn_801750B8();
		case 3:
			return fn_80173644();
		case 4:
			return fn_801729BC();
		default:
			return 0;
	}
}
}
