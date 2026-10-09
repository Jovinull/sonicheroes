// TObjKey's constructor, out of line: the copy each module keeps beside the
// one inlined into the factory in rel/key_object_create.cpp. The class and the
// constructor's body are shared through key_object_class.inc.

#define KEY_OBJECT_CTOR
#include "src/rel/key_object_class.inc"
