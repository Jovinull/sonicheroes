// Creates a pathname, runs fn_80198000(2, 1, path) on it, destroys it and returns the result.

extern "C" {
int RsPathnameCreate();
void RsPathnameDestroy(int);
int fn_80198000(int, int, int);

int fn_80041FF4()
{
	int p = RsPathnameCreate();
	int r = fn_80198000(2, 1, p);
	RsPathnameDestroy(p);
	return r;
}
}
