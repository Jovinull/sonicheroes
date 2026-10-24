#include "types.h"

// The item balloon's Unload and Load hooks (itembaloonObjectUnload and
// itembaloonObjectLoad here): the item panels end with the balloon's model;
// the model is read and the item panels start.

extern "C" void* itembaloonResource;
extern "C" char itembaloonModelName[];

void* objPointerReadFromClumpAnim(char* name);
void endObjItempanel();
void initObjItempanel();

extern "C" void itembaloonObjectUnload(void)
{
	endObjItempanel();
	itembaloonResource = NULL;
}

extern "C" void itembaloonObjectLoad(void)
{
	itembaloonResource = objPointerReadFromClumpAnim(itembaloonModelName);
	initObjItempanel();
}
