// Returns the first word of the given list, or of the head when none is given.
extern "C" {
int fn_80206328(int* a, int* b)
{
	if (b == 0) {
		return *a;
	}
	return *b;
}
}
