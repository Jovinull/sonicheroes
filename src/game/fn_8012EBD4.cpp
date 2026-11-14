// Copies a zero-terminated 16-bit string; the destination is cleared first so a null source leaves it empty.
extern "C" {
void fn_8012EBD4(unsigned short* dst, unsigned short* src)
{
	if (dst == 0) {
		return;
	}
	*dst = 0;
	if (src != 0) {
		while (*src != 0) {
			*dst++ = *src++;
		}
	}
	*dst = 0;
}
}
