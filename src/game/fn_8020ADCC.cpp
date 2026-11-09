// Runs the pending work with the manager's busy counter held.
struct Mgr8020ADCC {
	unsigned char pad0[8];
	int f8;
};

extern "C" {
extern Mgr8020ADCC* lbl_8042CF6C;
int OSDisableInterrupts();
void OSRestoreInterrupts(int e);
void fn_80209EC4();

int fn_8020ADCC()
{
	if (lbl_8042CF6C == 0) {
		return 0x0D000001;
	}
	int e = OSDisableInterrupts();
	lbl_8042CF6C->f8++;
	OSRestoreInterrupts(e);
	fn_80209EC4();
	e = OSDisableInterrupts();
	lbl_8042CF6C->f8--;
	OSRestoreInterrupts(e);
	return 0;
}
}
