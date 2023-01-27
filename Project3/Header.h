#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include <tlhelp32.h>
using namespace std;
#include <tlhelp32.h>
#include <tchar.h>

DWORD GetPIDByName(const TCHAR* processName)
{
    DWORD pid = 0;

    // Take a snapshot of all running processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        // Fill in the size of the structure before using it
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        // Walk the snapshot of the processes
        if (Process32First(hSnapshot, &pe))
        {
            do
            {
                // Compare the process name with the name of the process we're looking for
                if (_tcscmp(pe.szExeFile, processName) == 0)
                {
                    // We've found the process
                    pid = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }

        // Don't forget to clean up the snapshot object
        CloseHandle(hSnapshot);
    }

    return pid;
}

template <typename T>

T readMem(DWORD address, HANDLE pHandle)

{
	T buffer;
ReadProcessMemory(pHandle, (LPVOID)address, &buffer, sizeof(buffer), 0);
return buffer;
}
template <typename T>
void writeMem(DWORD address, T value, HANDLE pHandle)
{
    WriteProcessMemory(pHandle, (LPVOID)address, &value, sizeof(value), 0);
}
