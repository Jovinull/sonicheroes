extern "C" {
void fn_80199F50(void* box, void* point);
void fn_80199F78(void* box, void* point);
}

extern "C" int fn_8015926C(void* arg0, void* arg1)
{
	void* node;
	int depth = 0;
	int first = 0;
	void* stack[64];
	node = *(void**)((char*)arg0 + 0x1c);
	do {
		if (*(int*)node < 0) {
			if (first == 0) {
				fn_80199F50(arg1, (char*)node + 0x74);
				first = 1;
			} else {
				fn_80199F78(arg1, (char*)node + 0x74);
			}
			fn_80199F78(arg1, (char*)node + 0x68);
			node = stack[depth];
			depth--;
		} else {
			void* old      = node;
			node           = *(void**)((char*)old + 0x8);
			stack[++depth] = *(void**)((char*)old + 0xc);
		}
	} while (depth >= 0);
	return 1;
}
