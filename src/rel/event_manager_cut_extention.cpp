// EventManager::cutExtention (the PS2 build's name): it copies the file name
// `path` into `name` up to its extension, which it cuts off; a name with no
// dot is copied without its terminator.

#include "src/rel/event_manager_class.inc"

void EventManager::cutExtention(char* name, char* path)
{
	char c;

	while ((c = *path) != '\0') {
		if (c == '.') {
			*name = '\0';
			return;
		}
		*name++ = c;
		path++;
	}
}
