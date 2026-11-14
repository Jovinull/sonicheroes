// Finds the entry of o whose first word is the node named name (looked up with fn_801A4BBC in the
// list fn_801A4C98 returns). A null o or name raises error 0x80000016 of plugin 0x185 through
// fn_8019408C/fn_80193FE8. Returns the entry, or null.
struct Entry80192BF8 {
	void* node;
};

struct Obj80192BF8 {
	unsigned char pad0[0x10];
	Entry80192BF8** entries; // 0x10
	int count;               // 0x14
};

struct Error80192BF8 {
	int plugin;
	int code;
};

extern "C" {
void* fn_801A4C98(void);
void* fn_801A4BBC(void* list, const char* name);
int fn_8019408C(int code, ...);
void fn_80193FE8(Error80192BF8* e);

Entry80192BF8* fn_80192BF8(Obj80192BF8* o, const char* name)
{
	if (o != 0 && name != 0) {
		void* node;
		int i;
		if (fn_801A4C98() == 0) {
			return 0;
		}
		node = fn_801A4BBC(fn_801A4C98(), name);
		if (node == 0) {
			return 0;
		}
		for (i = 0; i < o->count; i++) {
			Entry80192BF8* e = o->entries[i];
			if (node == e->node) {
				return e;
			}
		}
	} else {
		Error80192BF8 e;
		e.plugin = 0x185;
		e.code   = fn_8019408C(0x80000016);
		fn_80193FE8(&e);
	}
	return 0;
}
}
