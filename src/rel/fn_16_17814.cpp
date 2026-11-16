struct S {
	char pad[0x35];
	char a[3];
};
extern "C" int fn_16_17814(S* p, char c)
{
	int i;
	for (i = 0; i < 3; i++) {
		if (c == p->a[i]) {
			return 1;
		}
	}
	return 0;
}
