// Sets the channel material color (channel 4) from a copy of the given color.

extern "C" {
void GXSetChanMatColor(int, int*);

void fn_8015EC3C(int unused, int* color)
{
	int c = *color;
	GXSetChanMatColor(4, &c);
}
}
