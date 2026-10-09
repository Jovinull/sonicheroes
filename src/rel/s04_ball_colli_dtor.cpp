// TObjS04BallColli's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through s04_ball_colli_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define S04_BALL_COLLI_CTOR inline
#include "src/rel/s04_ball_colli_class.inc"

TObjS04BallColli::~TObjS04BallColli() { }
