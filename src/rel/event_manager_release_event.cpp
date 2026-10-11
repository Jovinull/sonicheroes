// EventManager::ReleaseEvent (the PS2 build's name), out of line: it ends the
// loaded event. It stops the event's sound when one plays, releases the script
// and every scene with its files and textures (releaseSceneAll, inlined), the
// event's file, and resets the manager (Init, inlined); then it puts the game
// back: the mode switch 0x32 off, the players, the camera and the sound. With
// no event loaded it only turns the mode switch off and answers 0. LoadEvent
// inlines it (event_manager_class.inc).

#define EVENT_RELEASE_EVENT_INLINE

#include "src/rel/event_manager_class.inc"
