// Clears word 0x0C of each of the count (word 0x04) 16-byte entries of the array at 0x10.
struct E8013F448 {
	int f0;
	int f4;
	int f8;
	int fC;
};
struct O8013F448 {
	int pad0;
	int count;
	int pad8;
	int padC;
	E8013F448* arr;
};
extern "C" {
void fn_8013F448(O8013F448* o)
{
	int i;
	for (i = 0; i < o->count; i++) {
		o->arr[i].fC = 0;
	}
}
}
