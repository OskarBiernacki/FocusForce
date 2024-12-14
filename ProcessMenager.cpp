#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include "ProcessMenager.h"

#pragma comment(lib, "Psapi.lib")


using namespace std;

std::vector<std::pair<std::string, long>> ProcessMenager::getRunningProcesses() {
    std::vector<std::pair<std::string, long>> processList;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Nie udało się utworzyć zrzutu procesów." << std::endl;
        return processList;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
            if (hProcess) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    std::string processName = pe32.szExeFile;
                    long memoryUsage = static_cast<long>(pmc.WorkingSetSize / 1024 / 1024);
                    processList.emplace_back(processName, memoryUsage);
                }
                CloseHandle(hProcess);
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    std::sort(processList.begin(), processList.end(), [](const auto& a, const auto& b) {return a.second > b.second;});

    return processList;
}

bool ProcessMenager::killBlacklistedProcess(const std::vector<std::string>& blacklist) {
    bool killedAnyProcess = false;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "ERROR PROCESS KILLER" << std::endl;
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            std::string processName = pe32.szExeFile;
            if (std::find(blacklist.begin(), blacklist.end(), processName) != blacklist.end()) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess) {
                    if (TerminateProcess(hProcess, 1)) {
                        std::cout << "Procces kiled: " << processName << " (PID: " << pe32.th32ProcessID << ")" << std::endl;
                        killedAnyProcess = true;
                    } else {
                        std::cerr << "Can't kill process: " << processName << " (PID: " << pe32.th32ProcessID << ")" << std::endl;
                    }
                    CloseHandle(hProcess);
                } else {
                    std::cerr << "Can't open process: " << processName << " (PID: " << pe32.th32ProcessID << ")" << std::endl;
                }
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return killedAnyProcess;
}