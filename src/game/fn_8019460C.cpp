#include "types.h"

// Returns field 0 when the signed word at offset 4 is nonzero, otherwise 0.
extern "C" {
struct Record8019460C {
	s32 field0;
	s32 field4;
};

s32 fn_8019460C(Record8019460C* record)
{
	if (record->field4 != 0) {
		return record->field0;
	}
	return 0;
}
}
