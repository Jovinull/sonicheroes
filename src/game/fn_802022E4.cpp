// Reserves a buffer through two helpers and copies the given data into it when present; returns the first helper's result or -1.
extern "C" {
int fn_8019469C();
void* fn_80194510(int a, int b);
void* memcpy(void* d, const void* s, unsigned int n);

int fn_802022E4(int a, void* b, int c)
{
	int r   = fn_8019469C();
	void* p = fn_80194510(a, c);
	if (p == 0) {
		return -1;
	}
	if (b != 0) {
		memcpy(p, b, c);
	}
	return r;
}
}
