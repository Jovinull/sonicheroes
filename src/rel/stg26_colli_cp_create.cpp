// stg26ColliCpCreate, the factory of the Cp collision marker's editor record:
// a new TObjStg26Colli (rel/stg26_colli_class.inc) under the module's second
// parent object. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp).

#include "src/rel/stg26_colli_class.inc"

extern "C" TObject* stg26ColliCcObject1;

extern "C" void stg26ColliCpCreate(void)
{
	new TObjStg26Colli(stg26ColliCcObject1);
}
