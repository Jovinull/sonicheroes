// TObjContWood's Disp (empty) and Exec, which hands the frame to the
// container's own Exec (TObjContainer::Exec, called directly). The class is
// shared through wood_container_class.inc.

#define WOOD_CONTAINER_CTOR inline
#define WOOD_CONTAINER_DTOR_FIRST
#include "src/rel/wood_container_class.inc"

void TObjContWood::Disp() { }

void TObjContWood::Exec()
{
	TObjContainer::Exec();
}
