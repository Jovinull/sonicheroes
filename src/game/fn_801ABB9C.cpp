// Advances the frame-buffer flip queue when a flip is pending: moves the queue head (arming or disarming the GX breakpoint), wakes the waiting thread and updates the vsync/ready flags.
struct Flip801ABB9C {
	unsigned int f0;
	int f4;
};

extern "C" {
extern Flip801ABB9C lbl_803EDB38[];
extern int lbl_8042BE7C;
extern int lbl_8042C9E0;
extern int lbl_8042C9F8;
extern int lbl_8042C9FC;
extern int lbl_8042CA08;
extern int lbl_8042CA0C;
extern int lbl_8042CA10;
extern int lbl_8042CA14;
extern int lbl_8042CA18;
extern int lbl_8042CA20[2];
void GXDisableBreakPt();
void GXEnableBreakPt(int a);
void OSWakeupThread(int* q);

void fn_801ABB9C()
{
	int next;
	if (lbl_8042CA10 != 0 && lbl_8042CA14 != 0) {
		next = (lbl_8042C9F8 + 1) % lbl_8042BE7C;
		if ((unsigned int)next == (unsigned int)lbl_8042C9FC) {
			GXDisableBreakPt();
			lbl_8042CA08 = 0;
		} else {
			GXEnableBreakPt(lbl_803EDB38[next].f4);
		}
		lbl_8042C9F8 = next;
		OSWakeupThread(lbl_8042CA20);
		if (lbl_8042C9E0 == 0) {
			lbl_8042CA0C = 1;
		} else if (lbl_8042CA18 == 1) {
			lbl_8042CA0C = 1;
			lbl_8042CA18 = 0;
		} else {
			lbl_8042CA18 = 1;
		}
		lbl_8042CA10 = 0;
	}
	lbl_8042CA14 = 0;
}
}
