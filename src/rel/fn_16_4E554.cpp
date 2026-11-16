struct Entry {
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

extern "C" {
void fn_16_4E864(int);
void fn_16_4E944(int, int);

void fn_16_4E554(Entry* arg0)
{
	int i = 0;
	while (arg0[i].b != 0) {
		if (arg0[i].a != 0) {
			fn_16_4E864(arg0[i].a);
			fn_16_4E944(arg0[i].a, 1);
		}
		i++;
	}
}
}
