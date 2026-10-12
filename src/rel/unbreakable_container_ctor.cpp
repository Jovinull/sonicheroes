// TObjContUnbreakable's constructor, out of line: the copy each module keeps
// although rel/unbreakable_container_create.cpp inlines it (no caller;
// force_active). The constructor is in unbreakable_container_class.inc.

#define UNBREAKABLE_CONTAINER_CTOR
#include "src/rel/unbreakable_container_class.inc"
