extern "C" void fn_8014FF2C(int);
extern "C" void fn_16_16F68(register int* p)
{
	switch (p[2]) {
		case 1:
		case 2:
			fn_8014FF2C(p[10]);
			break;
	}
}
