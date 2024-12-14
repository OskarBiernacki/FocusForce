#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class ProcessMenager {
    public:
        ProcessMenager(vector<string> blackList);
        vector<string> blackList;
        bool isKillerActive=true;

        void startProcessBlocker();

        std::vector<std::pair<std::string, long>> getRunningProcesses();
        bool killBlacklistedProcess(const std::vector<std::string>& blacklist);
};