// Scans the list's ids for the first one that passes the checks and whose name matches the query's name, storing it in the query (an already-set candidate id is cleared when it is met first); returns the object.
struct List800F47B0 {
	unsigned char pad0[0x20];
	unsigned int* f20;
	int f24;
};
struct Obj800F47B0 {
	unsigned char pad0[0x18];
	List800F47B0* f18;
};
struct Query800F47B0 {
	unsigned int f0;
	unsigned int f4;
	char* f8;
};

extern "C" {
unsigned int fn_80146918();
unsigned int fn_80146BC8(unsigned int a, int b);
char* fn_80147910();
int strcmp(const char* a, const char* b);

Obj800F47B0* fn_800F47B0(Obj800F47B0* o, Query800F47B0* q)
{
	int off;
	List800F47B0* l;
	int i;
	unsigned int id;
	l = o->f18;
	if (q->f0 != 0) {
		return o;
	}
	i   = 0;
	off = 0;
	for (; i < l->f24; off += 4, i++) {
		id = *(unsigned int*)((char*)l->f20 + off);
		if (q->f4 != 0) {
			if (q->f4 == id) {
				q->f4 = 0;
			}
			continue;
		}
		if (fn_80146BC8(id, 6) != 0 && fn_80146918() != 0 && strcmp(fn_80147910(), q->f8) == 0) {
			q->f0 = id;
			break;
		}
	}
	return o;
}
}
