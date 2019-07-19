#include "windows.h"
#include "stdio.h"

#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define PAGE_SIZE 4 * 1024
#define RTL_MAX_DRIVE_LETTERS 32

typedef enum _SECTION_INFORMATION_CLASS {
	SectionBasicInformation,
		SectionImageInformation,
		MaxSectionInfoClass  // MaxSectionInfoClass should always be the last enum
} SECTION_INFORMATION_CLASS;


typedef struct _UNICODE_STRING{
	USHORT Length;
	USHORT MaxLength;
	PWCHAR pBuff;
}UNICODE_STRING, *PUNICODE_STRING;

typedef struct _ANSI_STRING{
	USHORT Length;
	USHORT MaxLength;
	PCHAR pBuff;
}ANSI_STRING, *PANSI_STRING, STRING, *PSTRING;

typedef struct _OBJECT_ATTRIBUTES{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
}OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK{
	ULONG Status;
	ULONG Information;
}IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _SECTION_IMAGE_INFORMATION{
	PULONG TransferAddress;
	ULONG ZeroBits;
	ULONG MaximumStackSize;
	ULONG CommittedStackSize;
	ULONG SubSysmtemType;
	USHORT SubSystemMinorVersion;
	USHORT SubSystemMajorVersion;
	ULONG GpValue;
	USHORT Imagecharacteristics;
	USHORT DllCharacteristics;
	USHORT Machine;
	UCHAR  ImageContainsCode;
	UCHAR  Spare1;
	ULONG LoaderFlags;
	ULONG ImageFileSize;
	ULONG Reserved;
}SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _INITIAL_TEB{
	PVOID OldStabckBase;
	PVOID OldStackLimit;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID StackAllocationBase;
}INITIAL_TEB, *PINITIAL_TEB;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _CURDIR {
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    ULONG MaximumLength;
    ULONG Length;
	
    ULONG Flags;
    ULONG DebugFlags;
	
    HANDLE ConsoleHandle;
    ULONG  ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
	
    CURDIR CurrentDirectory;        // ProcessParameters
    UNICODE_STRING DllPath;         // ProcessParameters
    UNICODE_STRING ImagePathName;   // ProcessParameters
    UNICODE_STRING CommandLine;     // ProcessParameters
    PVOID Environment;              // NtAllocateVirtualMemory
	
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
	
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;     // ProcessParameters
    UNICODE_STRING DesktopInfo;     // ProcessParameters
    UNICODE_STRING ShellInfo;       // ProcessParameters
    UNICODE_STRING RuntimeData;     // ProcessParameters
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[ RTL_MAX_DRIVE_LETTERS ];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PROCESS_BASIC_INFORMATION {
    LONG ExitStatus;
    PLONG PebBaseAddress;
    PULONG AffinityMask;
    LONG BasePriority;
    PULONG UniqueProcessId;
    PULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

typedef struct _PORT_MESSAGE {
    USHORT DataSize;
    USHORT MessageSize;
    USHORT MessageType;
    USHORT VirtualRangesOffset;
    CLIENT_ID ClientId;
    ULONG MessageId;
    ULONG SectionSize;
    // UCHAR Data[];
} PORT_MESSAGE, *PPORT_MESSAGE;

typedef struct _BASE_CREATEPROCESS_MSG {
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    CLIENT_ID DebuggerClientId;
    ULONG CreationFlags;
    ULONG IsVDM;
    HANDLE hVDM;
} BASE_CREATEPROCESS_MSG, *PBASE_CREATEPROCESS_MSG;

typedef struct _BASE_API_MSG {
    PORT_MESSAGE h;
    PVOID CaptureBuffer;
    ULONG ApiNumber;
    ULONG ReturnValue;
    ULONG Reserved;
    union {
        BASE_CREATEPROCESS_MSG CreateProcessW;
    } u;
} BASE_API_MSG, *PBASE_API_MSG;

ULONG  NTSYSAPI WINAPI ZwCreateSection(
									   OUT PHANDLE SectionHandle, 
									   IN  ACCESS_MASK DesiredAccess,
									   IN  POBJECT_ATTRIBUTES ObjectAttributes,
									   IN  PLARGE_INTEGER SectionSize,
									   IN  ULONG Protect,
									   IN  ULONG Attributes,
									   IN  HANDLE FileHandle
									   );

ULONG NTSYSAPI WINAPI RtlInitUnicodeString(
										   OUT PUNICODE_STRING pDest,
										   IN  PWCHAR pSour
										   );
ULONG NTSYSAPI WINAPI ZwOpenFile(
								 OUT PHANDLE FileHandle, 
								 IN ACCESS_MASK DesiredAccess,
								 IN POBJECT_ATTRIBUTES Objectattributes,
								 OUT PIO_STATUS_BLOCK IoStatusBlock,
								 IN ULONG SharedAccess,
								 IN ULONG OpenOptions
								 );

ULONG NTSYSAPI WINAPI ZwClose(
							  IN HANDLE FileHandle
							  );

ULONG NTSYSAPI WINAPI ZwCreateSection(
									  OUT PHANDLE  SectionHandle,
									  IN ACCESS_MASK  DesiredAccess,
									  IN POBJECT_ATTRIBUTES  ObjectAttributes OPTIONAL,
									  IN PLARGE_INTEGER  MaximumSize OPTIONAL,
									  IN ULONG  SectionPageProtection,
									  IN ULONG  AllocationAttributes,
									  IN HANDLE  FileHandle OPTIONAL
									  ); 
ULONG NTSYSAPI WINAPI ZwQuerySection(
									 IN HANDLE SectionHandle,
									 IN ULONG InformationClass,
									 OUT PVOID SectionInformation,
									 IN  ULONG SectionInformationLength,
									 OUT PULONG ResultLength
									 );

ULONG NTSYSAPI WINAPI ZwAllocateVirtualMemory(
											  IN HANDLE  ProcessHandle,
											  IN OUT PVOID  *BaseAddress,
											  IN ULONG  ZeroBits,
											  IN OUT PSIZE_T  RegionSize,
											  IN ULONG  AllocationType,
											  IN ULONG  Protect
											  ); 

ULONG NTSYSAPI WINAPI ZwCreateProcess(
									  OUT PHANDLE ProcessHandle, 
									  IN  ACCESS_MASK DesiredAccess,
									  IN  POBJECT_ATTRIBUTES ObjectAttributes,
									  IN  HANDLE IneritFromProcessHandle, 
									  IN  BOOLEAN InheritHandle,
									  IN  HANDLE Sectionhandle,
									  IN  HANDLE DebugPort,
									  IN  HANDLE ExceptionPort															  
									  );

#define NtCurrentProcess() (HANDLE)-1

ULONG NTSYSAPI WINAPI ZwProtectVirtualMemory(
											 IN HANDLE ProcessHandle,
											 IN OUT PVOID * BaseAddress,
											 IN OUT PULONG ProtectSize,
											 IN ULONG NewProtect,
											 OUT PULONG OldProtect
											 );
ULONG NTSYSAPI WINAPI ZwCreateThread(
									 OUT PHANDLE ThreadHandle,
									 IN ACCESS_MASK DesiredAccess,
									 IN POBJECT_ATTRIBUTES ObjectAttributes,
									 IN HANDLE ProcessHandle,
									 OUT PCLIENT_ID ClientId,
									 IN PCONTEXT ThreadContext,
									 IN PINITIAL_TEB InitialTeb,
									 IN BOOLEAN CreateSuspended
									 );

ULONG NTSYSAPI WINAPI RtlCreateProcessParameters(
												 OUT PRTL_USER_PROCESS_PARAMETERS *pProcessParameters,
												 IN PUNICODE_STRING ImagePathName,
												 IN PUNICODE_STRING DllPath OPTIONAL,
												 IN PUNICODE_STRING CurrentDirectory OPTIONAL,
												 IN PUNICODE_STRING CommandLine OPTIONAL,
												 IN PVOID Environment OPTIONAL,
												 IN PUNICODE_STRING WindowTitle OPTIONAL,
												 IN PUNICODE_STRING DesktopInfo OPTIONAL,
												 IN PUNICODE_STRING ShellInfo OPTIONAL,
												 IN PUNICODE_STRING RuntimeData OPTIONAL
												 );

ULONG NTSYSAPI WINAPI RtlDestroyProcessParameters(
												  IN PRTL_USER_PROCESS_PARAMETERS pProcessParameters
												  );
ULONG NTSYSAPI WINAPI ZwQueryInformationProcess (
												 IN HANDLE ProcessHandle,
												 IN ULONG ProcessInformationClass,
												 OUT PVOID ProcessInformation,
												 IN ULONG ProcessInformationLength,
												 OUT PULONG ReturnLength
												 );

ULONG NTSYSAPI WINAPI CsrClientCallServer(
										  IN OUT PVOID m,
										  IN OUT PVOID,
										  IN ULONG ApiNumber,
										  IN ULONG ArgLength
										  );
ULONG NTSYSAPI WINAPI ZwWriteVirtualMemory (
											IN HANDLE ProcessHandle,
											IN PVOID BaseAddress,
											IN CONST VOID *Buffer,
											IN SIZE_T BufferSize,
											OUT PSIZE_T NumberOfBytesWritten
											);

ULONG NTSYSAPI WINAPI ZwReadVirtualMemory (
										   IN HANDLE ProcessHandle,
										   IN PVOID BaseAddress,
										   IN CONST VOID *Buffer,
										   IN SIZE_T BufferSize,
										   OUT PSIZE_T NumberOfBytesWritten
										   );

ULONG NTSYSAPI WINAPI ZwResumeThread(
									 IN HANDLE ThreadHandle,
									 OUT PULONG PreviousSuspendCount
									 );


BOOLEAN NTSYSAPI WINAPI RtlDosPathNameToNtPathName_U(
													 IN PCWSTR DosPathName,
													 OUT PUNICODE_STRING NtPathName,
													 OUT PCWSTR *NtFileNamePart,
													 OUT CURDIR *DirectoryInfo
													 );


ULONG NTSYSAPI WINAPI ZwClose(
							  IN HANDLE Handle
							  );

void main()
{
    WCHAR DosPathName[] = L"c:\\calc.exe";
	UNICODE_STRING NtPathName;
	CURDIR DirectoryInfo;
	
	OBJECT_ATTRIBUTES oa;
	HANDLE FileHandle, SectionHandle, ProcessHandle, ThreadHandle;
	ULONG Status;
	IO_STATUS_BLOCK isb;
	SECTION_IMAGE_INFORMATION sii;
	ULONG StackSize;
	INITIAL_TEB  iTeb;
	PVOID p;
	ULONG OldProtect;
	CONTEXT Context;
	CLIENT_ID ClientId;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PROCESS_BASIC_INFORMATION pbi;
	BASE_API_MSG BaseApiMsg;
	ULONG n, envCount;
	PWCHAR penv;
	
	//转换文件名。
	if (!RtlDosPathNameToNtPathName_U(DosPathName, &NtPathName, NULL, &DirectoryInfo)){
		printf("erro!");
		exit(0);
	   }
    else
		printf("NtPathName: %S\n", NtPathName.pBuff);
	
	oa.Length = sizeof(oa);
	oa.Attributes = OBJ_CASE_INSENSITIVE;
	oa.ObjectName = &NtPathName;
	oa.RootDirectory = NULL;
	oa.SecurityDescriptor = NULL;
	oa.SecurityQualityOfService = NULL;
	
	//打开文件, FILE_EXECUTE 不是 FILE_ALL_ACCESS
	Status = ZwOpenFile(&FileHandle, FILE_EXECUTE | FILE_READ_ATTRIBUTES |FILE_READ_DATA | SYNCHRONIZE, &oa, &isb, FILE_SHARE_READ | FILE_SHARE_DELETE, FILE_SYNCHRONOUS_IO_NONALERT |FILE_NON_DIRECTORY_FILE);
	if (Status == 0) 
		printf("ZwOpenFile successfully!\n");
	else
		printf("ZwOpenFile Fail!\n");
	
	//创建SECTION 对象并查询信息
	Status = ZwCreateSection(&SectionHandle, SECTION_ALL_ACCESS, NULL, NULL, PAGE_EXECUTE, SEC_IMAGE, FileHandle);
	if (Status == 0) 
		printf("ZwCreateSection successfully!\n");
	else
		printf("ZwCreateSection Fail!\n");
	ZwClose(FileHandle);
	
	ZwQuerySection(SectionHandle, SectionImageInformation, &sii, sizeof(sii), NULL);
	StackSize = sii.MaximumStackSize; //堆栈大小。	
	
	//创建进程                                                                          (TRUE) 
	Status = ZwCreateProcess(&ProcessHandle, PROCESS_ALL_ACCESS, NULL, NtCurrentProcess(), 4, SectionHandle, 0, 0);
	if (Status == 0) 
		printf("ZwCreateProcess successfully!\n");
	else
		printf("ZwCreateProcess Fail!\n");
	ZwClose(SectionHandle);
	
	//下面为分配堆栈、CONTEXT，创建线程。
	RtlZeroMemory(&iTeb, sizeof(iTeb));
	ZwAllocateVirtualMemory(ProcessHandle, &iTeb.StackAllocationBase, 0, &StackSize, MEM_RESERVE, PAGE_READWRITE); 
	iTeb.StackBase = (PCHAR)iTeb.StackAllocationBase + sii.MaximumStackSize;
	iTeb.StackLimit = (PCHAR)iTeb.StackBase - sii.CommittedStackSize;
	p = (PCHAR)iTeb.StackLimit - PAGE_SIZE;
	
	StackSize = PAGE_SIZE + sii.CommittedStackSize;
	ZwAllocateVirtualMemory(ProcessHandle, &p, 0, &StackSize, MEM_COMMIT, PAGE_READWRITE);
	StackSize = PAGE_SIZE;
	ZwProtectVirtualMemory(ProcessHandle, &p, &StackSize, PAGE_READWRITE | PAGE_GUARD, &OldProtect);
	
	RtlZeroMemory(&Context, sizeof(Context));
	Context.ContextFlags  = CONTEXT_FULL;
	Context.SegGs = 0;
	Context.SegFs = 0x3b;
	Context.SegEs = 0x23;
	Context.SegDs = 0x23;
	Context.SegSs = 0x23;
	Context.SegCs = 0x1B;
	Context.EFlags = 0x3000;
	Context.Esp = (ULONG)iTeb.StackBase - 4;
	Context.Eip = (ULONG)sii.TransferAddress;
	Status = ZwCreateThread(&ThreadHandle, THREAD_ALL_ACCESS, NULL, ProcessHandle, &ClientId, &Context, &iTeb, TRUE);
	if (Status == 0) 
		printf("ZwCreateThread successfully!\n");
	else
		printf("ZwCreateThread Fail!\n");
	
	//进程的参数。
	Status = ZwQueryInformationProcess(ProcessHandle, 0, &pbi, sizeof(pbi), NULL);
	if (Status == 0) 
		printf("ZwQueryInformationProcess successfully peb=%x!\n", pbi.PebBaseAddress);
	else
		printf("ZwQueryInformationProcess Fail!\n");
	
	RtlCreateProcessParameters(&ProcessParameters, &NtPathName, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	penv = (PWCHAR)ProcessParameters->Environment;
	envCount = 0;
	n = 0;
	do{
		n = wcslen(penv);
		envCount += (n + 1) * 2;
		penv = penv + n + 1;
	}while(n != 0);
	p = NULL;
	ZwAllocateVirtualMemory(ProcessHandle, &p, 0, &envCount, MEM_COMMIT, PAGE_READWRITE);
	ZwWriteVirtualMemory(ProcessHandle, p, ProcessParameters->Environment, envCount, NULL);
	ProcessParameters->Environment = p;	
	
	p = NULL;
	n =  ProcessParameters->MaximumLength;
	
	ZwAllocateVirtualMemory(ProcessHandle, &p, 0, &n, MEM_COMMIT, PAGE_READWRITE);
	ZwWriteVirtualMemory(ProcessHandle, p, ProcessParameters, ProcessParameters->MaximumLength, NULL);
	ZwWriteVirtualMemory(ProcessHandle, (PCHAR)pbi.PebBaseAddress + 0x10, &p, sizeof(p), NULL);
    RtlDestroyProcessParameters(ProcessParameters);
	
	//通知Csrss.exe
	RtlZeroMemory(&BaseApiMsg, sizeof(BaseApiMsg));
	BaseApiMsg.u.CreateProcessW.ClientId.UniqueProcess = ClientId.UniqueProcess;
	BaseApiMsg.u.CreateProcessW.ClientId.UniqueThread = ClientId.UniqueThread;
	BaseApiMsg.u.CreateProcessW.ProcessHandle = (HANDLE)((ULONG)ProcessHandle | 3);
    BaseApiMsg.u.CreateProcessW.ThreadHandle = ThreadHandle;
	BaseApiMsg.u.CreateProcessW.CreationFlags = 0xFFFFFFFC;
	Status = CsrClientCallServer(&BaseApiMsg,NULL,0x10000, sizeof(BaseApiMsg)); //参数大小。
	if (Status == 0) 
		printf("CsrClientCallServer successfully!\n");
	else
		printf("CsrClientCallServer Fail!\n");
	
	//恢复Thread的执行
	ZwResumeThread(ThreadHandle, NULL);
}

