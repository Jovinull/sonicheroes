// Calls fn_8016F084 and then the default MObject close-down on the object.

extern "C" {
void fn_8016F084(int);
void DefaultCloseDown__7MObjectFv(int);

void fn_800C8C28(int a)
{
	fn_8016F084(a);
	DefaultCloseDown__7MObjectFv(a);
}
}
