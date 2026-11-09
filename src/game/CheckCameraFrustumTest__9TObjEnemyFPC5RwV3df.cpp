// Tests the sphere (position p, radius r) against the camera frustum (fn_8019CE34 on the camera at *lbl_8042C9A4), stores the result flag at +0x22C and returns it.

extern "C" {
struct Sphere9TObjEnemy {
	float a;
	float b;
	float c;
	float d;
};
struct Vec9TObjEnemy {
	float x;
	float y;
	float z;
};
struct Obj9TObjEnemy {
	unsigned char pad[0x22c];
	int f22c;
};
extern int* lbl_8042C9A4;
int fn_8019CE34(int, Sphere9TObjEnemy*);

int CheckCameraFrustumTest__9TObjEnemyFPC5RwV3df(Obj9TObjEnemy* o, const Vec9TObjEnemy* p, float r)
{
	Sphere9TObjEnemy sp8;
	sp8.a = p->x;
	sp8.b = p->y;
	sp8.c = p->z;
	sp8.d = r;
	if (fn_8019CE34(*lbl_8042C9A4, &sp8) == 0) {
		o->f22c = 0;
	} else {
		o->f22c = 1;
	}
	return o->f22c;
}
}
