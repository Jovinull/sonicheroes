// Clears the busy bit of the object when it is set.
extern "C" {
void fn_80205560(unsigned int* o)
{
	unsigned int t = o[1];
	if (t & 1) {
		o[1] = t & ~1u;
	}
}
}
