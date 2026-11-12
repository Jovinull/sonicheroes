// Sets slot t (index 0x28-0x2E, or 0x50-0x56 shifted down) of the 12-byte entries to 1.

extern "C" {
void fn_80116A48(int base, int i)
{
	int t;
	if (i >= 0x28 && i <= 0x2e) {
		t = i - 0x28;
	} else if (i >= 0x50 && i <= 0x56) {
		t = i - 0x49;
	} else {
		return;
	}
	*(unsigned*)(base + t * 0xc) = 1;
}
}
