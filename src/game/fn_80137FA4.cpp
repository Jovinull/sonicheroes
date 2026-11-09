// Walks list number i of the table in lbl_8042C298 and clears flag 0x02000000 on each record that has it.

extern "C" {
struct Rec80137FA4 {
	unsigned char pad[0x18];
	volatile unsigned f18;
	unsigned char pad1[0x38 - 0x1c];
	Rec80137FA4* next;
};
struct Tab80137FA4 {
	unsigned char pad[0x30];
	Rec80137FA4* heads[4];
};
extern Tab80137FA4* lbl_8042C298;

void fn_80137FA4(unsigned char i)
{
	Rec80137FA4* p = lbl_8042C298->heads[i];
	for (; p != 0; p = p->next) {
		if ((p->f18 & 0x02000000) != 0) {
			p->f18 &= 0xFDFFFFFF;
		}
	}
}
}
