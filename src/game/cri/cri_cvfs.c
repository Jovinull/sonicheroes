// CRI CVFS (CRI virtual file system), GameCube build "CVFS/GC Ver.2.33".
//
// Range: .text 0x8021D480-0x8021E3D4 (12 functions), .rodata 0x8023F000-0x8023FBC0,
// .bss 0x8041F230-0x8041F6B8. No .data.
//
// Boundary evidence:
//   * The .rodata slice opens with the CVFS version banner and the pointer that
//     keeps it alive; every other string in it is a "cvFs*" diagnostic.
//   * Every .rodata and .bss label in the slice is referenced only from
//     functions in this range, and the range references no other unit's data.
//   * Below 0x8021D480 is the ADXF file system (adx_fs), above 0x8021E3D4 the
//     GCCI file layer (gcci.c, which starts with its empty DVD read callback).
//     The Mortal Kombat: Deception GameCube link map names the object
//     cri_cvfs.o and places it directly after adx_fs.o in a later (2.35) build.
//
// Build: the unit is compiled with -inline deferred. Deferred emission reverses
// the source order, so this file is written in PS2 source order (the CRI PS2
// symbol metadata lists cvFsCallUsrErrFn first and cvFsEntryErrFunc last among
// the surviving functions); it also lays uninitialised statics out in reverse
// declaration order, which is what the retail .bss shows. The private helpers
// (getDevice, toUpperStr, addDevice, ...) exist as symbols in the PS2 build and
// are fully inlined here.

#include "types.h"
#include "MSL_C/string.h"

extern char* strcpy(char* destination, const char* source);
extern int sprintf(char* destination, const char* format, ...);

typedef enum CvFsStatus {
	CVFS_STATUS_IDLE         = 0,
	CVFS_STATUS_COMPLETE     = 1,
	CVFS_STATUS_TRANSFERRING = 2,
	CVFS_STATUS_ERROR        = 3
} CvFsStatus;

typedef struct CvFsInterface CvFsInterface;
typedef struct CvFsObject CvFsObject;
typedef void (*CvFsErrorCallback)(void* object, const char* message, void* handle);
typedef CvFsInterface* (*CvFsInterfaceFactory)(void);

struct CvFsInterface {
	void (*ExecServer)(void);
	void (*EntryErrFunc)(CvFsErrorCallback callback, void* object);
	int (*GetFileSize)(const char* filename);
	int (*GetFreeSize)(void);
	void* (*Open)(const char* filename, void* parameter, int mode);
	void (*Close)(void* object);
	int (*Seek)(void* object, int offset, int origin);
	int (*Tell)(void* object);
	int (*ReqRd)(void* object, int sectors, void* buffer);
	int (*ReqWr)(void* object, int sectors, void* buffer);
	void (*StopTr)(void* object);
	CvFsStatus (*GetStat)(void* object);
	int (*GetSctLen)(void* object);
	void (*SetSctLen)(void* object, int sector_length);
	int (*GetNumTr)(void* object);
	int (*ChangeDir)(const char* dirname);
	int (*IsExistFile)(const char* filename);
	int (*GetNumFiles)(void);
	int (*LoadDirInfo)(const char* dirname, void* info, int count);
	int (*GetMaxByteRate)(void* object);
	int (*MakeDir)(const char* dirname);
	int (*RemoveDir)(const char* dirname);
	int (*DeleteFile)(const char* filename);
	int (*GetFileSizeEx)(const char* filename, void* parameter);
	int (*OptFn1)(void* object, int operation, int arg2, int arg3);
	int (*OptFn2)(void* object, int arg1, int arg2, int arg3);
};

struct CvFsObject {
	CvFsInterface* interface;
	void* object;
};

typedef struct CvFsDevice {
	CvFsInterface* interface;
	char name[9];
} CvFsDevice;

const char* const volatile cvfs_build = "\nCVFS/GC Ver.2.33 Build:May  9 2003 17:09:56\n";

/* The linked object keeps the whole CVFS diagnostic pool, including the
 * messages of the API functions the game never calls and the linker strips. */
static const char path_format[8]                    = "%s:%s";
static const char set_default_volume_bad_device[40] = "cvFsSetDefVol #1:illegal device name";
static const char set_default_volume_bad_volume[40] = "cvFsSetDefVol #2:illegal volume name";
static const char set_default_volume_no_device[36]  = "cvFsSetDefVol #3:device not found";
static const char get_volume_info_bad_device[44]    = "cvFsGetVolumeInfo #1:illegal device name";
static const char get_volume_info_bad_volume[44]    = "cvFsGetVolumeInfo #2:illegal volume name";
static const char get_volume_info_no_device[40]     = "cvFsGetVolumeInfo #3:device not found";
static const char delete_volume_bad_device[40]      = "cvFsDelVolume #1:illegal device name";
static const char delete_volume_bad_volume[40]      = "cvFsDelVolume #2:illegal volume name";
static const char delete_volume_no_device[36]       = "cvFsDelVolume #3:device not found";
static const char add_volume_bad_device[40]         = "cvFsAddVolumeEx #1:illegal device name";
static const char add_volume_bad_volume[40]         = "cvFsAddVolumeEx #2:illegal volume name";
static const char add_volume_bad_handle[40]         = "cvFsAddVolumeEx #3:illegal image handle";
static const char add_volume_no_device[36]          = "cvFsAddVolumeEx #3:device not found";
static const char set_volume_bad_device[40]         = "cvFsSetCurVolume #1:illegal device name";
static const char set_volume_bad_handle[44]         = "cvFsSetCurVolume #2:illegal image handle";
static const char set_volume_no_device[40]          = "cvFsSetCurVolume #3:device not found";
static const char opt2_bad_handle[28]               = "cvFsOptFn2 #1:handle error";
static const char opt2_bad_interface[28]            = "cvFsOptFn2 #2:vtbl error";
static const char opt1_bad_handle[28]               = "cvFsOptFn1 #1:handle error";
static const char opt1_bad_interface[28]            = "cvFsOptFn1 #2:vtbl error";
static const char get_device_name_bad_interface[32] = "cvFsGetDevName #1:vtbl error";
static const char delete_file_bad_name[36]          = "cvFsDeleteFile #1:illegal file name";
static const char delete_file_bad_device[40]        = "cvFsDeleteFile #2:illegal device name";
static const char delete_file_no_device[36]         = "cvFsDeleteFile #3:device not found";
static const char delete_file_bad_interface[32]     = "cvFsDeleteFile #4:vtbl error";
static const char remove_dir_bad_name[40]           = "cvFsRemoveDir #1:illegal directory name";
static const char remove_dir_bad_device[40]         = "cvFsRemoveDir #2:illegal device name";
static const char remove_dir_no_device[36]          = "cvFsRemoveDir #3:device not found";
static const char remove_dir_bad_interface[28]      = "cvFsRemoveDir #4:vtbl error";
static const char make_dir_bad_name[40]             = "cvFsMakeDir #1:illegal directory name";
static const char make_dir_bad_device[36]           = "cvFsMakeDir #2:illegal device name";
static const char make_dir_no_device[32]            = "cvFsMakeDir #3:device not found";
static const char make_dir_bad_interface[28]        = "cvFsMakeDir #4:vtbl error";
static const char max_rate_bad_handle[36]           = "cvFsGetMaxByteRate #1:handle error";
static const char max_rate_bad_interface[36]        = "cvFsGetMaxByteRate #2:vtbl error";
static const char exists_bad_device[40]             = "cvFsIsExistFile #2:illegal device name";
static const char exists_bad_name[40]               = "cvFsIsExistFile #1:illegal file name";
static const char exists_no_device[36]              = "cvFsIsExistFile #3:device not found";
static const char exists_bad_interface[32]          = "cvFsIsExistFile #4:vtbl error";
static const char change_dir_bad_name[40]           = "cvFsChangeDir #1:illegal directory name";
static const char change_dir_bad_device[40]         = "cvFsChangeDir #2:illegal device name";
static const char change_dir_no_device[36]          = "cvFsChangeDir #3:device not found";
static const char change_dir_bad_interface[28]      = "cvFsChangeDir #4:vtbl error";
static const char num_transfers_bad_handle[32]      = "cvFsGetNumTr #1:handle error";
static const char num_transfers_bad_interface[28]   = "cvFsGetNumTr #2:vtbl error";
static const char set_sector_bad_handle[32]         = "cvFsSetSctLen #3:handle error";
static const char set_sector_bad_interface[28]      = "cvFsSetSctLen #4:vtbl error";
static const char get_sector_bad_handle[32]         = "cvFsGetSctLen #1:handle error";
static const char get_sector_bad_interface[28]      = "cvFsGetSctLen #2:vtbl error";
static const char free_size_no_device[36]           = "cvFsGetFreeSize #5:device not found";
static const char free_size_bad_interface[32]       = "cvFsGetFreeSize #6:vtbl error";
static const char size_by_handle_bad_handle[48]  = "cvFsGetFileSizeByHndl #1:illegal file handle";
static const char size_ex_bad_name[40]           = "cvFsGetFileSizeEx #1:illegal file name";
static const char size_ex_bad_device[44]         = "cvFsGetFileSizeEx #2:illegal device name";
static const char size_ex_no_device[40]          = "cvFsGetFileSizeEx #3:device not found";
static const char size_ex_bad_interface[32]      = "cvFsGetFileSizeEx #4:vtbl error";
static const char size_bad_name[40]              = "cvFsGetFileSize #1:illegal file name";
static const char size_bad_device[40]            = "cvFsGetFileSize #2:illegal device name";
static const char size_no_device[36]             = "cvFsGetFileSize #3:device not found";
static const char size_bad_interface[32]         = "cvFsGetFileSize #4:vtbl error";
static const char status_bad_handle[28]          = "cvFsGetStat #1:handle error";
static const char status_bad_interface[28]       = "cvFsGetStat #2:vtbl error";
static const char stop_bad_handle[28]            = "cvFsStopTr #1:handle error";
static const char stop_bad_interface[28]         = "cvFsStopTr #2:vtbl error";
static const char write_bad_handle[28]           = "cvFsReqWr #1:handle error";
static const char write_bad_interface[24]        = "cvFsReqWr #2:vtbl error";
static const char read_bad_handle[28]            = "cvFsReqRd #1:handle error";
static const char read_bad_interface[24]         = "cvFsReqRd #2:vtbl error";
static const char seek_bad_handle[28]            = "cvFsSeek #1:handle error";
static const char seek_bad_interface[24]         = "cvFsSeek #2:vtbl error";
static const char tell_bad_handle[28]            = "cvFsTell #1:handle error";
static const char tell_bad_interface[24]         = "cvFsTell #2:vtbl error";
static const char close_bad_handle[28]           = "cvFsClose #1:handle error";
static const char close_bad_interface[24]        = "cvFsClose #2:vtbl error";
static const char open_bad_name[32]              = "cvFsOpen #1:illegal file name";
static const char open_no_handle[36]             = "cvFsOpen #3:failed handle alloced";
static const char open_bad_device[32]            = "cvFsOpen #2:illegal device name";
static const char open_no_device[32]             = "cvFsOpen #4:device not found";
static const char open_bad_interface[24]         = "cvFsOpen #5:vtbl error";
static const char open_failed[24]                = "cvFsOpen #6:open failed";
static const char set_default_bad_device[40]     = "cvFsSetDefDev #1:illegal device name";
static const char set_default_unknown_device[40] = "cvFsSetDefDev #2:unknown device name";
static const char delete_device_bad_name[36]     = "cvFsDelDev #1:illegal device name";
static const char add_device_bad_name[36]        = "cvFsAddDev #1:illegal device name";
static const char add_device_bad_factory[36]     = "cvFsAddDev #2:illegal I/F func name";
static const char add_device_failed[36]          = "cvFsAddDev #3:failed added a device";

static CvFsErrorCallback cvfs_errfn = NULL;
static void* cvfs_errobj            = NULL;
int cvfs_init_cnt                   = 0;
static CvFsObject cvfs_obj[40];
static CvFsDevice cvfs_tbl[32];
static char cvfs_defdev[9];
static char add_dev_tmp[297];

void cvFsCallUsrErrFn(void* object, const char* message, void* handle);

static inline void cvFsError(const char* message)
{
	if (cvfs_errfn != NULL) {
		cvfs_errfn(cvfs_errobj, message, NULL);
	}
}

static inline void toUpperStr(char* string)
{
	unsigned long i;
	unsigned long length = strlen(string);

	for (i = 0; i < length + 1; i++) {
		if (string[i] >= 'a' && string[i] <= 'z') {
			string[i] -= 'a' - 'A';
		}
	}
}

static inline CvFsInterface* getDevice(char* name)
{
	unsigned long i;
	unsigned long length = strlen(name);

	for (i = 0; i < 32; i++) {
		if (strncmp(name, cvfs_tbl[i].name, length) == 0) {
			return cvfs_tbl[i].interface;
		}
	}
	return NULL;
}

static inline int isExistingDevice(const char* name, int length)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (strncmp(name, cvfs_tbl[i].name, length) == 0) {
			return 1;
		}
	}
	return 0;
}

static inline void getDefaultDevice(void* name)
{
	unsigned long length = strlen(cvfs_defdev);

	if (cvfs_defdev[0] == '\0') {
		((char*)name)[0] = 0;
	} else {
		memcpy(name, cvfs_defdev, length + 1);
	}
}

static inline void splitPath(char* device, char* file, char* path)
{
	int device_index;
	int file_index;

	if (path == NULL) {
		return;
	}

	for (device_index = 0; device_index < 297; device_index++) {
		if (path[device_index] == ':' || path[device_index] == '\0') {
			break;
		}
		device[device_index] = path[device_index];
	}

	if (path[device_index] == '\0') {
		device[device_index] = '\0';
		memcpy(file, device, strlen(device) + 1);
		device[0] = '\0';
		return;
	}

	device[device_index] = '\0';
	device_index++;
	if (device_index == 2) {
		device_index = 0;
		device[0]    = '\0';
	}

	for (file_index = device_index; file_index < 297; file_index++) {
		if (path[file_index] == '\0') {
			break;
		}
		file[file_index - device_index] = path[file_index];
	}
	file[file_index - device_index] = '\0';
	toUpperStr(device);
}

static inline int callPathOption(CvFsInterface* interface)
{
	int result;

	if (interface == NULL) {
		result = 0;
	} else if (interface->OptFn1 != NULL) {
		result = interface->OptFn1(NULL, 100, 0, 0);
	} else {
		result = 0;
	}
	return result;
}

static inline void addDevName(char* file, char* device)
{
	strcpy(add_dev_tmp, file);
	sprintf(file, path_format, device, add_dev_tmp);
}

static inline void addDevNameIfNeed(char* file, char* name)
{
	if (name == NULL) {
		name = cvfs_defdev;
	}
	if (callPathOption(getDevice(name)) == 1) {
		addDevName(file, name);
	}
}

static inline CvFsInterface* resolveDevice(char* device, char* file, char* original_path)
{
	CvFsInterface* interface;
	char* parsed_device = device;

	if (device[0] == '\0') {
		getDefaultDevice(device);
		if (device[0] == '\0') {
			return NULL;
		}
	}

	addDevNameIfNeed(file, parsed_device);

	interface = getDevice(parsed_device);
	if (interface == NULL) {
		getDefaultDevice(parsed_device);
		interface = getDevice(parsed_device);
		if (interface == NULL) {
			return NULL;
		}
		strcpy(file, original_path);
	}
	return interface;
}

static inline void* allocateHandle(void)
{
	int i;

	for (i = 0; i < 40; i++) {
		if (cvfs_obj[i].object == NULL) {
			break;
		}
	}
	if (i == 40) {
		return NULL;
	}
	return &cvfs_obj[i];
}

static inline void releaseHandle(CvFsObject* handle)
{
	handle->object    = NULL;
	handle->interface = NULL;
}

static inline CvFsInterface* addDevice(char* name, CvFsInterfaceFactory factory)
{
	CvFsInterface* interface;
	int i;

	toUpperStr(name);
	interface = factory();
	if (getDevice(name) != NULL) {
		return interface;
	}

	for (i = 0; i < 32; i++) {
		if (cvfs_tbl[i].name[0] == '\0') {
			break;
		}
	}
	if (i == 32) {
		return NULL;
	}

	cvfs_tbl[i].interface = interface;
	memcpy(cvfs_tbl[i].name, name, strlen(name) + 1);
	return interface;
}

void cvFsCallUsrErrFn(void* object, const char* message, void* handle)
{
	(void)object;
	if (cvfs_errfn != NULL) {
		cvfs_errfn(cvfs_errobj, message, handle);
	}
}

void cvFsAddDev(char* name, CvFsInterfaceFactory factory, void* init_parameter)
{
	CvFsInterface* interface;

	(void)init_parameter;
	cvfs_build;

	if (name == NULL) {
		cvFsError(add_device_bad_name);
		return;
	}
	if (factory == NULL) {
		cvFsError(add_device_bad_factory);
		return;
	}

	interface = addDevice(name, factory);
	if (interface == NULL) {
		cvFsError(add_device_failed);
	} else if (interface->EntryErrFunc != NULL) {
		interface->EntryErrFunc(cvFsCallUsrErrFn, NULL);
	}
}

void cvFsSetDefDev(char* name)
{
	unsigned long length;

	if (name == NULL) {
		cvFsError(set_default_bad_device);
		return;
	}
	length = strlen(name);
	if (length == 0) {
		cvfs_defdev[0] = '\0';
		return;
	}

	toUpperStr(name);
	if (isExistingDevice(name, length) == 1) {
		memcpy(cvfs_defdev, name, length + 1);
		return;
	}
	cvFsError(set_default_unknown_device);
}

CvFsObject* cvFsOpen(char* filename, void* parameter, int mode)
{
	CvFsObject* handle;
	char device[297];
	char file[297];

	if (filename == NULL) {
		cvFsError(open_bad_name);
		return NULL;
	}

	splitPath(device, file, filename);
	if (file[0] == '\0') {
		cvFsError(open_bad_name);
		return NULL;
	}

	handle = (CvFsObject*)allocateHandle();
	if (handle == NULL) {
		cvFsError(open_no_handle);
		return NULL;
	}

	handle->interface = resolveDevice(device, file, filename);
	if (device == NULL) {
		releaseHandle(handle);
		cvFsError(open_bad_device);
		return NULL;
	}
	if (handle->interface == NULL) {
		releaseHandle(handle);
		cvFsError(open_no_device);
		return NULL;
	}
	if (handle->interface->Open != NULL) {
		handle->object = handle->interface->Open(file, parameter, mode);
	} else {
		releaseHandle(handle);
		cvFsError(open_bad_interface);
		return NULL;
	}
	if (handle->object == NULL) {
		releaseHandle(handle);
		cvFsError(open_failed);
		return NULL;
	}
	return handle;
}

void cvFsClose(CvFsObject* handle)
{
	if (handle == NULL) {
		cvFsError(close_bad_handle);
	} else if (handle->interface->Close != NULL) {
		handle->interface->Close(handle->object);
		releaseHandle(handle);
	} else {
		cvFsError(close_bad_interface);
	}
}

int cvFsTell(CvFsObject* handle)
{
	int result;

	if (handle == NULL) {
		cvFsError(tell_bad_handle);
		return 0;
	}
	if (handle->interface->Tell != NULL) {
		result = handle->interface->Tell(handle->object);
	} else {
		result = 0;
		cvFsError(tell_bad_interface);
	}
	return result;
}

int cvFsSeek(CvFsObject* handle, int offset, int origin)
{
	int result;

	if (handle == NULL) {
		cvFsError(seek_bad_handle);
		return 0;
	}
	if (handle->interface->Seek != NULL) {
		result = handle->interface->Seek(handle->object, offset, origin);
	} else {
		result = 0;
		cvFsError(seek_bad_interface);
	}
	return result;
}

int cvFsReqRd(CvFsObject* handle, int sectors, void* buffer)
{
	int result;

	if (handle == NULL) {
		cvFsError(read_bad_handle);
		return 0;
	}
	if (handle->interface->ReqRd != NULL) {
		result = handle->interface->ReqRd(handle->object, sectors, buffer);
	} else {
		result = 0;
		cvFsError(read_bad_interface);
	}
	return result;
}

void cvFsStopTr(CvFsObject* handle)
{
	if (handle == NULL) {
		cvFsError(stop_bad_handle);
	} else {
		if (handle->interface->StopTr != NULL) {
			handle->interface->StopTr(handle->object);
			return;
		}
		cvFsError(stop_bad_interface);
	}
}

void cvFsExecServer(void)
{
	int i;
	CvFsInterface* interface;

	for (i = 0; i < 32; i++) {
		interface = cvfs_tbl[i].interface;
		if (interface != NULL && interface->ExecServer != NULL) {
			interface->ExecServer();
		}
	}
}

CvFsStatus cvFsGetStat(CvFsObject* handle)
{
	CvFsStatus status = CVFS_STATUS_ERROR;

	if (handle == NULL) {
		cvFsError(status_bad_handle);
		return status;
	}
	if (handle->interface->GetStat != NULL) {
		status = handle->interface->GetStat(handle->object);
	} else {
		cvFsError(status_bad_interface);
	}
	return status;
}

void cvFsEntryErrFunc(CvFsErrorCallback callback, void* object)
{
	if (callback == NULL) {
		cvfs_errfn  = NULL;
		cvfs_errobj = NULL;
		return;
	}
	cvfs_errfn  = callback;
	cvfs_errobj = object;
}
