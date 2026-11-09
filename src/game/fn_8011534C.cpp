// Stores 1 at offset 0x34.

extern "C" {
struct Obj8011534C {
	unsigned char pad[0x34];
	int v;
};
void fn_8011534C(Obj8011534C* s)
{
	s->v = 1;
}
}
