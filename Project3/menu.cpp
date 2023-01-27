#include <Windows.h>
#include <stdio.h>
#include "Header.h"

int main() {
    DWORD pid = 0;

    const char windowName[] = "9000lvl.exe";
    HWND hwnd = FindWindowW(NULL, L"9000lvl.exe");
    DWORD processID;
    GetWindowThreadProcessId(hwnd, &processID);
    

    while (true) {
        if (pid != 0) {
            Sleep(500);
            break;
        }
        else {
            pid = GetPIDByName(_T("9000lvl.exe"));
			Sleep(500);
            if (pid == 0)
            {
                printf("not found");
            }
            
        }
}
         
         HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		printf("PID: %d", pid);
    CONTEXT context;
    context.ContextFlags = CONTEXT_CONTROL;
    GetThreadContext(pHandle, &context);
    DWORD rbp = context.Rbp;

    // Calculate the base address
    DWORD offset = 0x25C; // 604
    DWORD adress = rbp + offset;

    printf("Base address: 0x%X", adress);
    unsigned int value = readMem<unsigned int>((rbp + 0x25C), pHandle);
    int z = readMem<int>((0x71FE0C), pHandle);
    printf("", z);
    while (true) {
        if (z == NULL){
            z = readMem<int>((0x71FE0C), pHandle);
        }
        else {
            break;
        }
}
    writeMem((0x71FE0C), 90000, pHandle);
    // Read the value from memory


    CloseHandle(pHandle);
    return 0;
}
