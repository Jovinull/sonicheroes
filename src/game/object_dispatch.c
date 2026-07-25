#include "types.h"

// A one-function translation unit from fn_80012E5C through 0x80012EA0.
// Its boundary is exact: the function has its own extab entry at 0x80005768
// and extabindex entry at 0x8000BD1C, and the next function begins at
// 0x80012EA0.

typedef struct ObjectDispatch {
	void* unk0;
	void (*destroy)(void*);
} ObjectDispatch;

extern ObjectDispatch* fn_801971A4(void);

void fn_80012E5C(void* object)
{
	if (object != NULL) {
		fn_801971A4()->destroy(object);
	}
}
