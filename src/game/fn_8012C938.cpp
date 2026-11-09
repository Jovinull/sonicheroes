// Records the entry whose name matches, recursing through the children when the node has any.
struct Obj8012C938 {
	char* f0;
	unsigned int f4;
};

extern "C" {
const char* fn_80172A1C(unsigned int a);
int fn_8017361C();
int fn_80173630(unsigned int a);
void fn_80173D74(
    unsigned int a, unsigned int (*cb)(unsigned int, int, Obj8012C938*), Obj8012C938* o);
int strcmp(const char* a, const char* b);

unsigned int fn_8012C938(unsigned int a, int b, Obj8012C938* o)
{
	if (o->f4 == 0) {
		if (fn_8017361C() != 0) {
			fn_80173D74(a, fn_8012C938, o);
		} else if (fn_80173630(a) != 0) {
			const char* s = fn_80172A1C(a);
			if (s != 0 && strcmp(s, o->f0) == 0) {
				o->f4 = a;
			}
		}
	}
	return a;
}
}
