struct Item {
	char pad[0x34];
};
struct Obj {
	char pad[0x68];
	Item* items;
};
extern "C" void fn_16_1704C(Item*);
extern "C" void fn_16_17914(Obj* o)
{
	int i;
	if (o->items) {
		for (i = 0; i < 3; i++)
			fn_16_1704C(&o->items[i]);
	}
}
