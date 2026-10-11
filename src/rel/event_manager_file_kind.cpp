// EventManager::checkFileKind (the PS2 build's name): it sorts a file of the
// event by its name. A name holding one of the 14 player kinds (eventFileKinds)
// answers 1 with that kind. Otherwise the file is an extra object: the entry
// already named after it, or the first unnamed one, which takes its name,
// answers 0 with the entry's index; with all 16 taken it answers 1.

#include "src/rel/event_manager_class.inc"

extern "C" char* eventFileKinds[14];
extern "C" char* strstr(const char* string, const char* pattern);
extern "C" char* strcpy(char* destination, const char* source);

s32 EventManager::checkFileKind(char* name, s32* kind)
{
	s32 i;

	for (i = 0; i < 14; i++) {
		if (strstr(name, eventFileKinds[i]) != NULL) {
			*kind = i;
			return 1;
		}
	}
	for (i = 0; i < 16; i++) {
		if (entries[i].name != NULL) {
			if (strstr(name, entries[i].name) != NULL) {
				*kind = i;
				return 0;
			}
		} else {
			strcpy(entries[i].name, name);
			*kind = i;
			return 0;
		}
	}
	return 1;
}
