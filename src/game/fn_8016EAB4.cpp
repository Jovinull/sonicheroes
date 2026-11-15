// Resets the matrix on top of the stack held in lbl_803EC968 (pointer table at +0x234, top index at
// +0x2B4) to identity, flags it as an orthonormal identity matrix and clears the words at +0x388
// and +0x39C; returns 1. HYPOTHESIS: inlined RwMatrixSetIdentity on a RenderWare-style matrix
// stack.

struct V3d8016EAB4 {
	float x;
	float y;
	float z;
};

struct Matrix8016EAB4 {
	V3d8016EAB4 right;
	unsigned int flags;
	V3d8016EAB4 up;
	unsigned int pad1C;
	V3d8016EAB4 at;
	unsigned int pad2C;
	V3d8016EAB4 pos;
	unsigned int pad3C;
};

struct Glob8016EAB4 {
	unsigned char pad0[0x234];
	Matrix8016EAB4* stack[32]; // 0x234
	int top;                   // 0x2B4
	unsigned char pad2B8[0x388 - 0x2B8];
	int f388; // 0x388, UNKNOWN
	unsigned char pad38C[0x39C - 0x38C];
	int f39c; // 0x39C, UNKNOWN
};

extern "C" {
extern Glob8016EAB4 lbl_803EC968;
// The constants live in .sdata2 but are declared non-const: retail reloads them after each store
// group.
extern float lbl_8042F460; // 1.0f
extern float lbl_8042F464; // 0.0f

int fn_8016EAB4(void)
{
	lbl_803EC968.stack[lbl_803EC968.top]->right.x    = lbl_803EC968.stack[lbl_803EC968.top]->up.y
	    = lbl_803EC968.stack[lbl_803EC968.top]->at.z = lbl_8042F460;
	lbl_803EC968.stack[lbl_803EC968.top]->right.y    = lbl_803EC968.stack[lbl_803EC968.top]->right.z
	    = lbl_803EC968.stack[lbl_803EC968.top]->up.x = lbl_8042F464;
	lbl_803EC968.stack[lbl_803EC968.top]->up.z       = lbl_803EC968.stack[lbl_803EC968.top]->at.x
	    = lbl_803EC968.stack[lbl_803EC968.top]->at.y = lbl_8042F464;
	lbl_803EC968.stack[lbl_803EC968.top]->pos.x      = lbl_803EC968.stack[lbl_803EC968.top]->pos.y
	    = lbl_803EC968.stack[lbl_803EC968.top]->pos.z = lbl_8042F464;
	lbl_803EC968.stack[lbl_803EC968.top]->flags |= 0x20003;
	lbl_803EC968.f388 = 0;
	lbl_803EC968.f39c = 0;
	return 1;
}
}
