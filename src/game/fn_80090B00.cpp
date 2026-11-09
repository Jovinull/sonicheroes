// Saves the time of the position record at 0x28 of the object, then increments and returns the counter at 0x23C.

extern "C" {
struct Obj80090B00 {
	unsigned char pad[0x23c];
	int f23c;
};
void saveTime__18PARAM_SAVEPOSITIONFv(void*);

int fn_80090B00(Obj80090B00* o)
{
	saveTime__18PARAM_SAVEPOSITIONFv((char*)o + 0x28);
	return o->f23c += 1;
}
}
