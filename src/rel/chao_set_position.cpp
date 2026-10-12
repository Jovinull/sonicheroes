// TObjChao::SetPosition (the PS2 build's name): the chao takes its position
// from the cage's work block when SearchCage made one, turns by its spin and
// places its frame there; away from a cage it also moves out by its offset and
// turns a quarter towards the side its spin goes. It then keeps the frame's
// position and scales the frame by the module's 0.75. Exec inlines it; this
// copy has no caller and is kept with force_active. The class is in
// chao_class.inc.

#define CHAO_SET_POSITION_INLINE

#include "src/rel/chao_class.inc"
#include "src/rel/chao_methods.inc"
