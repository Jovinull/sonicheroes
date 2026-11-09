// Clears eleven global counters and the first word of each 8-byte entry of the table at lbl_80259C78.

extern "C" {
struct Entry800F6FDC {
	int a;
	int b;
};
extern int lbl_8042C4C0;
extern int lbl_8042C4C4;
extern int lbl_8042C4C8;
extern int lbl_8042C4CC;
extern int lbl_8042C4D0;
extern int lbl_8042C4D4;
extern int lbl_8042C4D8;
extern int lbl_8042C4DC;
extern int lbl_8042C4E0;
extern int lbl_8042C4E4;
extern int lbl_8042C4E8;
extern Entry800F6FDC lbl_80259C78[8];

void fn_800F6FDC(void)
{
	lbl_8042C4C0      = 0;
	lbl_8042C4C4      = 0;
	lbl_8042C4C8      = 0;
	lbl_8042C4CC      = 0;
	lbl_8042C4D0      = 0;
	lbl_8042C4D4      = 0;
	lbl_8042C4D8      = 0;
	lbl_8042C4DC      = 0;
	lbl_8042C4E0      = 0;
	lbl_8042C4E4      = 0;
	lbl_8042C4E8      = 0;
	lbl_80259C78[0].a = 0;
	lbl_80259C78[1].a = 0;
	lbl_80259C78[2].a = 0;
	lbl_80259C78[3].a = 0;
	lbl_80259C78[4].a = 0;
	lbl_80259C78[5].a = 0;
	lbl_80259C78[6].a = 0;
	lbl_80259C78[7].a = 0;
}
}
