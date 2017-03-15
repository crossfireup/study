typedef NTSTATUS (*QUERY_INFO_PROCESS) (
        __in HANDLE ProcessHandle,
        __in PROCESSINFOCLASS ProcessInformationClass,
        __out_bcount(ProcessInformationLength) PVOID ProcessInformation,
        __in ULONG ProcessInformationLength,
        __out_opt PULONG ReturnLength
        );

QUERY_INFO_PROCESS ZwQueryInformationProcess;

NTSTATUS GetProcessImageName(HANDLE processId, PUNICODE_STRING ProcessImageName)
{
    NTSTATUS status;
    ULONG returnedLength;
    ULONG bufferLength;
    HANDLE hProcess;
    PVOID buffer;
    PEPROCESS eProcess;
    PUNICODE_STRING imageName;

    PAGED_CODE(); // this eliminates the possibility of the IDLE Thread/Process

    status = PsLookupProcessByProcessId(processId, &eProcess);

    if(NT_SUCCESS(status))
    {
        status = ObOpenObjectByPointer(eProcess,0, NULL, 0,0,KernelMode,&hProcess);
        if(NT_SUCCESS(status))
        {
        } else {
            DbgPrint("ObOpenObjectByPointer Failed: %08x\n", status);
        }
        ObDereferenceObject(eProcess);
    } else {
        DbgPrint("PsLookupProcessByProcessId Failed: %08x\n", status);
    }


    if (NULL == ZwQueryInformationProcess) {

        UNICODE_STRING routineName;

        RtlInitUnicodeString(&routineName, L"ZwQueryInformationProcess");

        ZwQueryInformationProcess =
            (QUERY_INFO_PROCESS) MmGetSystemRoutineAddress(&routineName);

        if (NULL == ZwQueryInformationProcess) {
            DbgPrint("Cannot resolve ZwQueryInformationProcess\n");
        }
    }

    /* Query the actual size of the process path */
    status = ZwQueryInformationProcess( hProcess,
            ProcessImageFileName,
            NULL, // buffer
            0, // buffer size
            &returnedLength);

    if (STATUS_INFO_LENGTH_MISMATCH != status) {
        return status;
    }

    /* Check there is enough space to store the actual process
       path when it is found. If not return an error with the
       required size */
    bufferLength = returnedLength - sizeof(UNICODE_STRING);
    if (ProcessImageName->MaximumLength < bufferLength)
    {
        ProcessImageName->MaximumLength = (USHORT) bufferLength;
        return STATUS_BUFFER_OVERFLOW;   
    }

    /* Allocate a temporary buffer to store the path name */
    buffer = ExAllocatePoolWithTag(NonPagedPool, returnedLength, 'uLT1');

    if (NULL == buffer) 
    {
        return STATUS_INSUFFICIENT_RESOURCES;   
    }

    /* Retrieve the process path from the handle to the process */
    status = ZwQueryInformationProcess( hProcess,
            ProcessImageFileName,
            buffer,
            returnedLength,
            &returnedLength);

    if (NT_SUCCESS(status)) 
    {
        /* Copy the path name */
        imageName = (PUNICODE_STRING) buffer;
        RtlCopyUnicodeString(ProcessImageName, imageName);
    }

    /* Free the temp buffer which stored the path */
    ExFreePoolWithTag(buffer, 'uLT1');

    return status;
}

//Function Call.. Write this piece of code in PreOperation Call back and IRQ should be PASSIVE_LEVEL

PEPROCESS objCurProcess=NULL;
HANDLE hProcess;
UNICODE_STRING fullPath;

objCurProcess=IoThreadToProcess(Data->Thread);//Note: Date is type of FLT_CALLBACK_DATA which is in PreOperation Callback as argument

hProcess=PsGetProcessID(objCurProcess);

fullPath.Length=0;
fullPath.MaximumLength=520;
fullPath.Buffer=(PWSTR)ExAllocatePoolWithTag(NonPagedPool,520,'uUT1');

GetProcessImageName(hProcess,&fullPath);
