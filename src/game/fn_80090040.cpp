#include "types.h"

struct Fn80090040Data {
	u8 pad[0x604];
	f32 field604;
	f32 field608;
};

extern "C" u32 fn_80090040(Fn80090040Data* arg0)
{
	return arg0->field608 < arg0->field604;
}
