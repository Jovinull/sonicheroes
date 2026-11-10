// Shuts down the audio effects, frees the shared mixer state and releases its memory.
struct Mgr8020A05C {
	int f0;
	unsigned char pad4[4];
	int f8;
};

extern "C" {
extern int __OSCurrHeap;
extern int lbl_8042CF68;
extern Mgr8020A05C* lbl_8042CF6C;
extern int lbl_8042CF70;
int OSDisableInterrupts();
void OSRestoreInterrupts(int e);
void OSFreeToHeap(int h, int p);
void ARFree(void* p);
void AXFXChorusShutdown(void* p);
void AXFXDelayShutdown(void* p);
void AXFXReverbHiShutdown(void* p);
void AXFXReverbStdShutdown(void* p);

void fn_8020A05C()
{
	int sp8;
	if (lbl_8042CF6C != 0) {
		int e            = OSDisableInterrupts();
		lbl_8042CF6C->f0 = 0;
		lbl_8042CF6C->f8++;
		OSRestoreInterrupts(e);
	}
	AXFXReverbStdShutdown((char*)lbl_8042CF6C + 0xFE04);
	AXFXReverbHiShutdown((char*)lbl_8042CF6C + 0xFF58);
	AXFXChorusShutdown((char*)lbl_8042CF6C + 0x10138);
	AXFXDelayShutdown((char*)lbl_8042CF6C + 0x101D4);
	if (lbl_8042CF6C != 0) {
		lbl_8042CF6C = 0;
		if (lbl_8042CF70 != 0) {
			lbl_8042CF70 = 0;
		} else {
			OSFreeToHeap(__OSCurrHeap, lbl_8042CF68);
		}
		lbl_8042CF68 = 0;
		ARFree(&sp8);
	}
}
}
