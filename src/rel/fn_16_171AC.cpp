extern "C" void fn_80150958(void* clump);

struct Obj {
	char pad[0x28];
	void* model;
};

extern "C" void fn_16_171AC(register Obj* o)
{
	if (o->model) {
		fn_80150958(o->model);
		o->model = 0;
	}
}
