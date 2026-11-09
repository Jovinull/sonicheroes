// Installs the C file-I/O callbacks (fn_80194100 and the C library fopen/fclose/fread/fwrite/fgets/fputs/feof/fseek/fflush/ftell) into the table at +0xC4 of lbl_8042C9A4; returns 1.

extern "C" {
struct Glob80194160 {
	unsigned char pad[0xc4];
	void* fc4;
	void* fc8;
	void* fcc;
	void* fd0;
	void* fd4;
	void* fd8;
	void* fdc;
	void* fe0;
	void* fe4;
	void* fe8;
	void* fec;
};
extern Glob80194160* lbl_8042C9A4;
extern unsigned char fn_80194100[];
extern unsigned char fopen[];
extern unsigned char fclose[];
extern unsigned char fread[];
extern unsigned char fwrite[];
extern unsigned char fgets[];
extern unsigned char fputs[];
extern unsigned char feof[];
extern unsigned char fseek[];
extern unsigned char fflush[];
extern unsigned char ftell[];

int fn_80194160(void)
{
	lbl_8042C9A4->fc4 = fn_80194100;
	lbl_8042C9A4->fc8 = fopen;
	lbl_8042C9A4->fcc = fclose;
	lbl_8042C9A4->fd0 = fread;
	lbl_8042C9A4->fd4 = fwrite;
	lbl_8042C9A4->fd8 = fgets;
	lbl_8042C9A4->fdc = fputs;
	lbl_8042C9A4->fe0 = feof;
	lbl_8042C9A4->fe4 = fseek;
	lbl_8042C9A4->fe8 = fflush;
	lbl_8042C9A4->fec = ftell;
	return 1;
}
}
