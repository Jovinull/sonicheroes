// Sets *out to 1 when fn_80146BC8(self, 6) is non-zero; returns self.

extern "C" {
unsigned fn_80146BC8(int, int);

int fn_8003C6FC(int self, int* out)
{
	if (fn_80146BC8(self, 6) != 0) {
		*out = 1;
	}
	return self;
}
}
