// stage05D's copy of the rinoliner (rel/e_rinoliner_stage11.cpp): the same unit
// without its own TEnemyStrategy vtable and destructor, which the module keeps
// only in the unit before it.

#define E_RINOLINER_SHARED_STRATEGY
#include "src/rel/e_rinoliner_stage11.cpp"
