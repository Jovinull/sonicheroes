extern "C" {
int CheckMustKill__10TObjSetObjFv(void*);
int CheckRangeOut__10TObjSetObjFv(void*);
int OnEdit__10TObjSetObjFv(void*);
void copyVec3(void*, void*);
void fn_16_1180(void*, void*, void*);
void fn_16_900(void*, void*);
void markSampleForDeletion(void*);
void fn_16_42684(char*);
}

void fn_16_42684(register char* obj)
{
	int sp8 = *(int*)(*(char**)(obj + 0x28) + 0x2C);
	if (CheckRangeOut__10TObjSetObjFv(obj + 0x28) || CheckMustKill__10TObjSetObjFv(obj + 0x28)) {
		markSampleForDeletion(obj);
		return;
	}
	if (OnEdit__10TObjSetObjFv(obj + 0x28)) {
		copyVec3(obj + 0xB8, *(void**)(obj + 0x28));
		fn_16_900(obj + 0xC4, *(char**)(obj + 0x28) + 0xC);
		return;
	}
	fn_16_1180(obj + 0x30, obj + 0xB8, obj + 0xC4);
}
