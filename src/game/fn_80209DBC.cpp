// Re-enables interrupts for the update path, advances the frame counter and refreshes the mixer settings.
struct Mgr80209DBC {
	int f0;
	unsigned char pad4[0x3C];
	int f40;
	unsigned char pad44[0x139F4];
	unsigned char f13A38;
	unsigned char f13A39;
};

extern "C" {
extern Mgr80209DBC* lbl_8042CF6C;
void MIXUpdateSettings();
void OSDisableInterrupts();
void OSEnableInterrupts(int e);
void fn_80209EC4();

void fn_80209DBC()
{
	if (lbl_8042CF6C != 0 && lbl_8042CF6C->f13A38 != 0) {
		unsigned char t      = lbl_8042CF6C->f13A39;
		lbl_8042CF6C->f13A39 = t + 1;
		OSEnableInterrupts(t);
		if (lbl_8042CF6C != 0 && lbl_8042CF6C->f0 != 0) {
			fn_80209EC4();
			lbl_8042CF6C->f40++;
		}
		OSDisableInterrupts();
		MIXUpdateSettings();
		return;
	}
	if (lbl_8042CF6C != 0 && lbl_8042CF6C->f0 != 0) {
		fn_80209EC4();
	}
	MIXUpdateSettings();
}
}
