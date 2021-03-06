#pragma once

#include "prerequisites.h"

#include <kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SCE_KERNEL_S_IRWXG
#	define SCE_KERNEL_S_IRWXG S_IRWXG
#endif

#define SCE_KERNEL_MAX_MODULES 256
#define SCE_KERNEL_MAX_NAME_LENGTH 256
#define SCE_KERNEL_MAX_SEGMENTS 4
#define SCE_KERNEL_NUM_FINGERPRINT 20

struct _SceKernelModuleSegmentInfo {
	void* baseAddr;
	uint32_t size;
	int32_t prot;
};
typedef struct _SceKernelModuleSegmentInfo SceKernelModuleSegmentInfo;

struct _SceKernelModuleInfo {
	size_t size;
	char name[SCE_KERNEL_MAX_NAME_LENGTH];
	SceKernelModuleSegmentInfo segmentInfo[SCE_KERNEL_MAX_SEGMENTS];
	uint32_t numSegments;
	uint8_t fingerprint[SCE_KERNEL_NUM_FINGERPRINT];
};
typedef struct _SceKernelModuleInfo SceKernelModuleInfo;

struct _SceKernelModuleInfoEx {
	size_t size;
	char name[SCE_KERNEL_MAX_NAME_LENGTH];
	SceKernelModule handle;
	uint32_t tlsIndex;
	uint64_t tlsInitAddr;
	uint32_t tlsInitSize;
	uint32_t tlsSize;
	uint32_t tlsOffset;
	uint32_t tlsAlign;
	uint64_t initProcAddr;
	uint64_t finiProcAddr;
	void* reserved1;
	void* reserved2;
	uint64_t ehFrameHdrAddr;
	uint64_t ehFrameAddr;
	uint32_t ehFrameHdrSize;
	uint32_t ehFrameSize;
	SceKernelModuleSegmentInfo segmentInfo[SCE_KERNEL_MAX_SEGMENTS];
	uint32_t numSegments;
	uint32_t numRefs;
};
typedef struct _SceKernelModuleInfoEx SceKernelModuleInfoEx;

#define SIZEOF_SCE_NOTIFICATION_REQUEST 0xC30

TYPE_BEGIN(struct _SceNotificationRequest, SIZEOF_SCE_NOTIFICATION_REQUEST);
	TYPE_FIELD(int32_t unk_0x10, 0x10);
	TYPE_FIELD(uint8_t buf[0], 0x2C);
TYPE_END();
typedef struct _SceNotificationRequest SceNotificationRequest;

typedef struct {
  uint64_t unk1;
  char version_string[0x1C];
  uint32_t version;
} SceFwInfo;

int sceKernelError(int error);

const char* sceKernelGetFsSandboxRandomWord(void);

int DLL_EXPORT sceKernelGetModuleInfo(SceKernelModule handle, SceKernelModuleInfo* info);
int DLL_EXPORT sceKernelGetModuleInfoEx(SceKernelModule handle, SceKernelModuleInfoEx* info);

int DLL_EXPORT sceKernelGetModuleInfoByName(const char* name, SceKernelModuleInfo* info);
int DLL_EXPORT sceKernelGetModuleInfoExByName(const char* name, SceKernelModuleInfoEx* info);

int sceKernelSendNotificationRequest(int device, SceNotificationRequest* req, size_t size, int blocking);

int sceKernelGetSystemSwVersion(SceFwInfo* fw_info);

int32_t sceKernelAllocateDirectMemoryForMiniApp(off_t start, off_t end, size_t len, size_t align, int type, off_t *addr);
int32_t sceKernelAllocateTraceDirectMemory(size_t len, size_t align, int type, off_t *addr);
int32_t sceKernelReleaseTraceDirectMemory(off_t start, size_t len);
int32_t sceKernelMapNamedSystemFlexibleMemory(void** addr, size_t len, int prot, int flags, const char *name);
int32_t sceKernelInternalMapDirectMemory(void **addr, size_t len, int prot, int flags, off_t start, size_t align);
int32_t sceKernelInternalMapNamedDirectMemory(void **addr, size_t len, int prot, int flags, off_t start, size_t align, const char *name);
int32_t sceKernelInternalMemoryGetAvailableSize(size_t *size);
int32_t sceKernelSetPhysFmemLimit(size_t size);
int32_t sceKernelGetResidentCount(pid_t pid);
int32_t sceKernelGetResidentFmemCount(pid_t pid);

#define	SYS_getdents 272
#define SYS_dynlib_get_info 593
#define SYS_dynlib_get_info_ex 608

int syscall(int num, ...);

typedef struct DIR DIR;
DIR *opendir(const char *filename);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
int gettimeofday(struct timeval *, struct timezone *);
int settimeofday(const struct timeval *, const struct timezone *);

#ifdef __cplusplus
}
#endif
