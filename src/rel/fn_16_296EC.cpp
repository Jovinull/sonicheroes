struct Node {
	char pad[0x1C];
	int key;
	Node* next;
};
extern "C" Node* fn_16_2A788(int);
extern "C" void fn_16_2A780(int, Node*);
extern "C" void __dl__FPv(void*);
extern "C" Node* fn_16_296EC(Node* self, short flag)
{
	if (self != 0) {
		if (self == fn_16_2A788(self->key)) {
			fn_16_2A780(self->key, self->next);
		} else {
			Node* p = fn_16_2A788(self->key);
			while (self != p->next) {
				p = p->next;
			}
			p->next = self->next;
		}
		if (flag > 0) {
			__dl__FPv(self);
		}
	}
	return self;
}
