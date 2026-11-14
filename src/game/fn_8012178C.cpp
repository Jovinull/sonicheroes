#include "types.h"

typedef struct Obj8012178C Obj8012178C;

struct Obj8012178C {
	u8 pad0[0xB4];
	s8 fB4; /* 0xB4 */
};

extern "C" {
void fn_8005FD8C(Obj8012178C* o, s16 speed);
void fn_8006228C(Obj8012178C* o);

void fn_8012178C(Obj8012178C* o)
{
	if (o->fB4 > 0) {
		if (--o->fB4 == 0) {
			fn_8005FD8C(o, 0xF);
			return;
		}
	}
	fn_8006228C(o);
}
}
