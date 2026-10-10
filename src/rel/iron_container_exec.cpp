// TObjContIron's Disp (empty) and Exec, which hands the frame to the
// container's own Exec (TObjContainer::Exec, called directly). The class is
// shared through iron_container_class.inc.

#define IRON_CONTAINER_CTOR inline
#define IRON_CONTAINER_DTOR_FIRST
#include "src/rel/iron_container_class.inc"

void TObjContIron::Disp() { }

void TObjContIron::Exec()
{
	TObjContainer::Exec();
}
