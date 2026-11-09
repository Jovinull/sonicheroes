// Records whether arg0 is non-zero in the audio state (lbl_8042CF6C +0xFDFB) and sets the AX mode to 2 (non-zero) or 0.

extern "C" {
struct Audio80209E58 {
	unsigned char pad[0xfdfb];
	signed char cfdfb;
};
extern Audio80209E58* lbl_8042CF6C;
void AXSetMode(int);

void fn_80209E58(int a)
{
	lbl_8042CF6C->cfdfb = (a != 0);
	if (a != 0) {
		AXSetMode(2);
		return;
	}
	AXSetMode(0);
}
}
