// Resets the record at owner + lbl_8042C828: when it holds a list, clears word 0x0C of each of the
// list's entries (the loop of fn_8013F448, written out as retail inlines it), calls fn_8013EEE0 when the list
// belongs to this owner (word 0x14) and drops it; word 0 becomes -1. Returns the owner.
struct Entry8013E6F4 {
	int f0;
	int f4;
	int f8;
	int fC;
};

struct List8013E6F4 {
	int pad0;
	int count;
	int pad8;
	int padC;
	Entry8013E6F4* entries; // 0x10
	unsigned int owner;     // 0x14
};

struct Rec8013E6F4 {
	int f0;
	List8013E6F4* list;
};

extern "C" {
extern int lbl_8042C828;
void fn_8013EEE0(List8013E6F4* l);

unsigned int fn_8013E6F4(unsigned int owner)
{
	Rec8013E6F4* r  = (Rec8013E6F4*)(owner + lbl_8042C828);
	List8013E6F4* l = r->list;
	if (l != 0) {
		{
			int i;
			for (i = 0; i < l->count; i++) {
				l->entries[i].fC = 0;
			}
		}
		if (l->owner == owner) {
			fn_8013EEE0(l);
		}
		r->list = 0;
	}
	r->f0 = -1;
	return owner;
}
}
