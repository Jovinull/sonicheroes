// Tests whether slot t (index 0x28-0x2E, or 0x50-0x56 shifted down) of the 12-byte entries is set; returns 0 for an index outside both ranges.

extern "C" {
int fn_80116A8C(int base, int i)
{
	int t;
	if (i >= 0x28 && i <= 0x2e) {
		t = i - 0x28;
	} else if (i >= 0x50 && i <= 0x56) {
		t = i - 0x49;
	} else {
		return 0;
	}
	if (*(unsigned*)(base + t * 0xc) != 0) {
		return 1;
	}
	return 0;
}
}
