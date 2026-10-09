// TObjHawkGunFlash::Create, the static factory the PS2 build names
// Create__16TObjHawkGunFlashFP7TObjectP5RwV3dP6sAngle: the muzzle flash of the
// Egg Hawk's gun, in stage01D and stage07D. It returns the new object.
//
// The allocation is a real new-expression of the C++ class with its
// constructor inlined; the arguments live in saved registers across the
// allocation, which is why this one keeps the object in r28. The class has a
// single base and sets neither a class name nor a size.
//
// The constructor takes the flash's model from the enemy database (the common
// set, entry 9) through TEnemyDataBase::GetInstance, which creates the database
// on first use, makes it ignore lights, keeps its first two atomics, and copies
// the position and angle it is given. The running flag is cleared twice, once
// at the top and once at the end, as the original does.

#define HAWK_GUN_FLASH_CTOR inline
#include "src/rel/hawk_gun_flash_class.inc"

TObjHawkGunFlash* TObjHawkGunFlash::Create(TObject* parent, RwV3d* position, sAngle* angle)
{
	return new TObjHawkGunFlash(parent, position, angle);
}
