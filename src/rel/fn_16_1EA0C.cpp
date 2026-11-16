typedef struct {
	char pad[0xC0];
	float a[3];
	char pad2[0x18];
	float b[3];
} Obj;
extern "C" void copyVec3(float*, float*);
extern "C" void fn_16_1EA0C(register Obj* obj)
{
	copyVec3(obj->a, obj->b);
}
