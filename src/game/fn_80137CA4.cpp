// Runs the handler for the player slot a with its current leader character data.
struct Pc137B00 {
	unsigned char pad[0x761];
	signed char c761;
};
struct Pl137B00 {
	unsigned char pad[0x3A];
	signed char c3a;
	unsigned char pad1[0x110 - 0x3B];
	signed char c110[4];
	Pc137B00* pcs[4];
};

extern "C" {
extern Pl137B00* lbl_80303DC8[];
int fn_80137D0C(int self, int a, int b);

int fn_80137CA4(int self, int a)
{
	Pl137B00* p = lbl_80303DC8[a];
	signed char k;
	if (p == 0) {
		return -1;
	}
	k = p->c3a;
	return fn_80137D0C(self, p->pcs[k]->c761, p->c110[k]);
}
}
