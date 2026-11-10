// Runs the handler for the player slot b with the character data selected by a.
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

int fn_80137B00(int self, int a, int b)
{
	Pl137B00* p = lbl_80303DC8[b];
	if (p == 0) {
		return -1;
	}
	return fn_80137D0C(self, p->pcs[a]->c761, p->c110[a]);
}
}
