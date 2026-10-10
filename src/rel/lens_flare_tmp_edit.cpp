// TObjEFLensTmp's EditOnChange, which only waits while it has no parameters
// (`while (param == NULL) { }`): the loop's head is the function's first
// instruction. It is the class's key function in the other units, so this one
// declares Exec first and does not emit the vtable. The classes are in
// lens_flare_class.inc.

#define LENS_FLARE_TMP_EXEC_FIRST
#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

void TObjEFLensTmp::EditOnChange(SETDATA_PARAM* param)
{
	while (param == NULL) {
	}
}
