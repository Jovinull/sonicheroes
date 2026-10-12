// TObjContIron's constructor, out of line: the copy each module keeps although
// rel/iron_container_create.cpp inlines it (no caller; force_active). The
// constructor is in iron_container_class.inc.

#define IRON_CONTAINER_CTOR
#include "src/rel/iron_container_class.inc"
