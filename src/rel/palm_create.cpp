// palmCreate, the factory rel/palm_register.cpp puts in the editor record for
// TObjPalm (rel/palm_class.inc), in stage09D: a real new-expression of the
// class, as rel/yajirusi_create.cpp has it.

#include "src/rel/palm_class.inc"

extern "C" void palmCreate(void)
{
	new TObjPalm(lbl_8042C110);
}
