// Destroys the eleven free lists held in the table lbl_8040EB50.

extern "C" {
struct Lists8020577C {
	int a0;
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	int a7;
	int a8;
	int a9;
	int a10;
};
extern Lists8020577C lbl_8040EB50;
void RwFreeListDestroy(int);

void fn_8020577C(void)
{
	RwFreeListDestroy(lbl_8040EB50.a0);
	RwFreeListDestroy(lbl_8040EB50.a1);
	RwFreeListDestroy(lbl_8040EB50.a2);
	RwFreeListDestroy(lbl_8040EB50.a3);
	RwFreeListDestroy(lbl_8040EB50.a4);
	RwFreeListDestroy(lbl_8040EB50.a5);
	RwFreeListDestroy(lbl_8040EB50.a6);
	RwFreeListDestroy(lbl_8040EB50.a7);
	RwFreeListDestroy(lbl_8040EB50.a8);
	RwFreeListDestroy(lbl_8040EB50.a9);
	RwFreeListDestroy(lbl_8040EB50.a10);
}
}
