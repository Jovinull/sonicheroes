typedef signed int s32;
typedef unsigned char u8;

struct Node80159E9C {
	s32 type;                   // 0x0
	u8 pad4[4];                 // 0x4
	struct Node80159E9C* child; // 0x8
	struct Node80159E9C* other; // 0xC
};

struct Object80159E9C {
	u8 pad0[0x1C];
	struct Node80159E9C* root; // 0x1C
};

typedef void* (*Callback80159E9C)(struct Node80159E9C* node, void* data);

extern "C" void* fn_80159E9C(struct Object80159E9C* object, Callback80159E9C callback, void* data)
{
	struct Node80159E9C* stack[64];
	struct Node80159E9C* node = object->root;
	s32 depth                 = 0;

	do {
		if (node->type < 0) {
			if (callback(node, data) == 0) {
				return object;
			}
			node = stack[depth];
			depth -= 1;
		} else {
			struct Node80159E9C* other = node->other;
			depth += 1;
			node         = node->child;
			stack[depth] = other;
		}
	} while (depth >= 0);
	return object;
}
