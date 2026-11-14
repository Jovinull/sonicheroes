// Releases the handle at 0x04 of a record (fn_8019E880) when it is set, stores value at
// record + lbl_8042C91C and returns value.
struct Rec8015B9CC {
	unsigned char pad0[0x4];
	void* f4;
};

extern "C" {
extern int lbl_8042C91C;
void fn_8019E880(void* h);

int fn_8015B9CC(int value, Rec8015B9CC* rec)
{
	int off = lbl_8042C91C;
	if (rec->f4 != 0) {
		fn_8019E880(rec->f4);
	}
	*(int*)((unsigned char*)rec + off) = value;
	return value;
}
}
