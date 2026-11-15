struct Obj80090A98 {
	unsigned char pad0[0x122];
	signed char f122[3];
	signed char f125[3];
};

extern "C" int fn_80090A98(Obj80090A98* o)
{
	return (o->f122[0] != o->f125[0]) ? 1
	    : (o->f122[1] != o->f125[1])  ? 1
	    : (o->f122[2] != o->f125[2])  ? 1
	                                  : 0;
}
