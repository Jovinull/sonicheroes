// Calls the handler stored at +0x24 of target with target's context (+0x28) and arg. Returns the
// handler's result. Names are UNKNOWN.
struct Target8017B50C {
	unsigned char pad0[0x24];
	void* (*handler)(void* context, void* arg); // 0x24
	void* context;                              // 0x28
};

extern "C" {
void* fn_8017B50C(void* arg, Target8017B50C* target)
{
	return target->handler(target->context, arg);
}
}
