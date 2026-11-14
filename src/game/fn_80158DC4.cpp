// Recursively tears down a spatial tree node (HYPOTHESIS: world sectors and planes). A sector
// (type -1) runs fn_80197384 on its block at +0x34, releases the entries of its lists at +0x38 and
// +0x40 through fn_8015A58C and of its list at +0x48 through fn_8015A51C, then runs the sector
// plugin destructors (registry lbl_8028D2D0). Type -2 holds nothing; any other node recurses into
// its children at +0x8 and +0xC. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Node80158DC4 {
	s32 type; // 0x0
	s32 f4;
	Node80158DC4* left;  // 0x8
	Node80158DC4* right; // 0xC
	u8 pad10[0x34 - 0x10];
	void* block;       // 0x34
	RwLinkList list38; // 0x38
	RwLinkList list40; // 0x40
	RwLinkList list48; // 0x48
};

extern "C" {
extern RwPluginRegistry lbl_8028D2D0;
void fn_80197384(void* block);
s32 fn_8015A58C(RwLLLink* entry);
s32 fn_8015A51C(RwLLLink* entry);

void fn_80158DC4(Node80158DC4* node)
{
	switch (node->type) {
		case -1: {
			RwLLLink* cur;
			RwLLLink* end;
			if (node->block != 0) {
				fn_80197384(node->block);
			}
			cur = node->list38.link.next;
			end = &node->list38.link;
			while (cur != end) {
				RwLLLink* entry = cur;
				cur             = cur->next;
				fn_8015A58C(entry);
			}
			cur = node->list40.link.next;
			end = &node->list40.link;
			while (cur != end) {
				RwLLLink* entry = cur;
				cur             = cur->next;
				fn_8015A58C(entry);
			}
			cur = node->list48.link.next;
			end = &node->list48.link;
			while (cur != end) {
				RwLLLink* entry = cur;
				cur             = cur->next;
				fn_8015A51C(entry);
			}
			fn_80198E04(&lbl_8028D2D0, node);
			break;
		}
		case -2:
			break;
		default:
			fn_80158DC4(node->left);
			fn_80158DC4(node->right);
			break;
	}
}
}
