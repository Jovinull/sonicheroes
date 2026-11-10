// Creates the eleven free lists of the table lbl_8040EB50 (element sizes 0x1C..0x408) and marks the table as ready; the table and flag are volatile to keep the stores in order.
extern "C" {
extern volatile int lbl_8040EB50[];
extern volatile int lbl_8042CF58;
int RwFreeListCreate(int size, int a, int b);

void fn_80205624()
{
	lbl_8040EB50[0]  = RwFreeListCreate(28, 0x14, 0x10);
	lbl_8040EB50[1]  = RwFreeListCreate(144, 0x14, 0x10);
	lbl_8040EB50[2]  = RwFreeListCreate(344, 0x14, 0x10);
	lbl_8040EB50[3]  = RwFreeListCreate(16, 0x14, 0x10);
	lbl_8040EB50[4]  = RwFreeListCreate(16, 0x14, 0x10);
	lbl_8040EB50[5]  = RwFreeListCreate(1032, 0x14, 0x10);
	lbl_8040EB50[6]  = RwFreeListCreate(156, 0x14, 0x10);
	lbl_8040EB50[7]  = RwFreeListCreate(12, 0x14, 0x10);
	lbl_8040EB50[8]  = RwFreeListCreate(16, 0x14, 0x10);
	lbl_8040EB50[9]  = RwFreeListCreate(8, 0x14, 0x10);
	lbl_8040EB50[10] = RwFreeListCreate(16, 0x14, 0x10);
	lbl_8042CF58     = 1;
}
}
