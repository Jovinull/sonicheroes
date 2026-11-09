// Rotates the vector arg1 in place by the Z, X, Y angles held in arg2 (pushed matrix, then popped).

extern "C" {
struct Rot80051EF0 {
	int x;
	int y;
	int z;
};
void PushMatrix__FP11RwMatrixTag(int);
void RotateX__FP11RwMatrixTagi(int, int);
void RotateY__FP11RwMatrixTagi(int, int);
void RotateZ__FP11RwMatrixTagi(int, int);
void CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(int, void*, void*);
void PopMatrix__FUi(int);

void fn_80051EF0(int unused, void* v, Rot80051EF0* r)
{
	PushMatrix__FP11RwMatrixTag(0);
	RotateZ__FP11RwMatrixTagi(0, r->z);
	RotateX__FP11RwMatrixTagi(0, r->x);
	RotateY__FP11RwMatrixTagi(0, r->y);
	CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(0, v, v);
	PopMatrix__FUi(1);
}
}
