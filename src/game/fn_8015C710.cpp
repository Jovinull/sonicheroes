// Stores two signed bytes into the record at arg0+arg1 (+1 and +0xD).

extern "C" {
struct Rec8015C710 {
	signed char c0;
	signed char c1;
	unsigned char pad[0xb];
	signed char cd;
};

void fn_8015C710(int a, int b, signed char c, signed char d)
{
	Rec8015C710* t = (Rec8015C710*)(a + b);
	t->c1          = c;
	t->cd          = d;
}
}
