// trainrolltunnelCreate, the factory rel/trainrolltunnel_register.cpp puts in
// the editor record for TObjTrainRollTunnel, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for 6 models, starting with
// "obj08_Tunnel.dff": each is cloned into its own part and added once to the
// world slot its file names.

#define TRAIN_ROLL_TUNNEL_CTOR inline
#include "src/rel/train_roll_tunnel_class.inc"

extern "C" void trainrolltunnelCreate(void)
{
	new TObjTrainRollTunnel(lbl_8042C110);
}
