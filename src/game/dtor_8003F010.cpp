// PLAYERWK::~PLAYERWK() (CORROBORATED: PS2 metadata __dt__8PLAYERWKFv references
// __dt__8mtnmanwkFv; it is the member destructor in TObjOldPlayer's constructor's exception
// table). Destroys the two members at +0x1BC and +0x14C (dtor_800F1618) and frees the object when
// flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void dtor_800F1618(void*, int);

void* __dt__8PLAYERWKFv(unsigned char* o, short flags)
{
	if (o != 0) {
		dtor_800F1618(o + 0x1bc, -1);
		dtor_800F1618(o + 0x14c, -1);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
