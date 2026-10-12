// TObjBobcontUnbreakable's Disp (empty) and Exec, which hands the frame to the
// bobsleigh container's own Exec (TObjBobcontainer::Exec, called directly). The
// class is shared through unbr_bobcont_class.inc.

#define UNBR_BOBCONT_CTOR inline
#define UNBR_BOBCONT_DTOR_FIRST
#include "src/rel/unbr_bobcont_class.inc"

void TObjBobcontUnbreakable::Disp() { }

void TObjBobcontUnbreakable::Exec()
{
	TObjBobcontainer::Exec();
}
