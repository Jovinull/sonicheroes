// Walks list number i of the table in lbl_8042C298 and, for each record without flag 4, sets flags 4 and 0x02000000.

extern "C" {
struct Rec80137F54 {
	unsigned char pad[0x18];
	volatile unsigned f18;
	unsigned char pad1[0x38 - 0x1c];
	Rec80137F54* next;
};
struct Tab80137F54 {
	unsigned char pad[0x30];
	Rec80137F54* heads[4];
};
extern Tab80137F54* lbl_8042C298;

void fn_80137F54(unsigned char i)
{
	Rec80137F54* p = lbl_8042C298->heads[i];
	for (; p != 0; p = p->next) {
		if ((p->f18 & 4) == 0) {
			p->f18 |= 4;
			p->f18 |= 0x02000000;
		}
	}
}
}
