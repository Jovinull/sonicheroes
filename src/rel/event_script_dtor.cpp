// EventScript's destructor (the PS2 build's name): it deletes the script's
// message board. EndEventManager deletes the script. The class is in
// event_manager_class.inc.

#include "src/rel/event_manager_class.inc"

EventScript::~EventScript()
{
	if (message != NULL) {
		delete message;
		message = NULL;
	}
}
