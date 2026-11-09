// Returns the index of the highest set bit of arg0 (-1 for 0).

extern "C" {
int fn_801A91E8(int a)
{
	int r = -1;
	while (a != 0) {
		a = a >> 1;
		r++;
	}
	return r;
}
}
