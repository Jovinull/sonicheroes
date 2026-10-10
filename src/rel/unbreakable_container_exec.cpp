// TObjContUnbreakable's Disp (empty) and Exec, which hands the frame to the
// container's own Exec (TObjContainer::Exec, called directly). The class is
// shared through unbreakable_container_class.inc.

#define UNBREAKABLE_CONTAINER_CTOR inline
#define UNBREAKABLE_CONTAINER_DTOR_FIRST
#include "src/rel/unbreakable_container_class.inc"

void TObjContUnbreakable::Disp() { }

void TObjContUnbreakable::Exec()
{
	TObjContainer::Exec();
}
