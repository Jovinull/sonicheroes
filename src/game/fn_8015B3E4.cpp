// Returns the object when the check on the id succeeds, null otherwise.
extern "C" {
unsigned int fn_8015E8A0(void* a, int c);

void* fn_8015B3E4(void* a, int b, int c)
{
	if (fn_8015E8A0(a, c) != 0) {
		return a;
	}
	return 0;
}
}
