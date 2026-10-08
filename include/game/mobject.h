#ifndef GAME_MOBJECT_H
#define GAME_MOBJECT_H
#include "types.h"
struct RwCamera;
struct RpWorld;
struct RpLight;
class MObject
{
public:
	virtual void Init();
	virtual s32 Loop();
	virtual void End();
	void DefaultCloseDown();
	void DefaultSetUp();
	static void DestroyDefaultCamera();
	RwCamera* CreateDefaultCamera();
	static RpWorld* CreateDefaultWorld();
	static RpLight* CreateDefaultAmbientLight();
	static RpWorld* pDefaultWorld;
	static RwCamera* pDefaultCamera;
	static RpLight* pDefaultAmbientLight;
	static RpLight* pDefaultDiffuseLight;
	static MObject* pCurrent_MObject;
	static s32 module_number;
	static MObject* mobject_table[4];
};
RwCamera* GetMObjectCameraPointer();
RpWorld* GetCurrentWorldPointer();
RwCamera* GetCurrentCameraPointer();
void getRidOfRwCameraMemoryLeakBugAndDefaultFontSet();
#endif
