#include "types.h"

struct Fn80124924Data {
	u8 pad[0xBC];
	s32 fieldBC;
};

extern "C" s32 fn_80124924(Fn80124924Data* arg0)
{
	return arg0->fieldBC != 0;
}
