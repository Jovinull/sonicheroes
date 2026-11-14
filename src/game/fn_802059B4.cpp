// Synchronous form of fn_80205848: posts an ARAM transfer on the first free request of the audio
// system (see game/audio_system.h) with a completion callback and spins until fn_80205B08 clears
// the request's busy byte.
#include "game/audio_system.h"

extern "C" {
void fn_80205B08(u32 request);

void fn_802059B4(
    u32 source, u32 destination, u32 length, PoolRequestCallback callback, unsigned int arg)
{
	int i                               = FindFreeArqRequest();
	lbl_8042CF6C->busy[i]               = 1;
	lbl_8042CF6C->requestCallback[i]    = callback;
	lbl_8042CF6C->requestCallbackArg[i] = arg;
	ARQPostRequest(&lbl_8042CF6C->requests[i], lbl_8042CF6C->arqOwner, 0, 1, source, destination,
	    length, fn_80205B08);
	{
		volatile PoolSystem* sys     = lbl_8042CF6C;
		volatile unsigned char* busy = &sys->busy[i];
		while (*busy != 0) {
		}
	}
}
}
