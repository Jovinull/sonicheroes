// Walks the two nested entry lists and runs the per-entry handler for every populated child.
struct Item80206770 {
	unsigned char pad0[4];
	unsigned int f4;
};

extern "C" {
#pragma opt_loop_invariants off
Item80206770* fn_80206328(int a, Item80206770* p);
void fn_80206FB0(unsigned int a);

void fn_80206770(int a)
{
	Item80206770* p;
	unsigned int c;
	Item80206770* q;
	p = 0;
	while ((p = fn_80206328(a, p)) != 0) {
		c = p->f4;
		if (c != 0) {
			q = 0;
			while ((q = fn_80206328(c + 0x10, q)) != 0) {
				if (q->f4 != 0) {
					fn_80206FB0(q->f4);
				}
			}
		}
	}
}
#pragma opt_loop_invariants reset
}
