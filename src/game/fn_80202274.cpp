// Returns the word that fn_8019472C(object->4) points at.

extern "C" {
struct Obj80202274 {
	int f0;
	int f4;
};
int* fn_8019472C(int);

int fn_80202274(Obj80202274* s)
{
	return *fn_8019472C(s->f4);
}
}
