#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class ProcessMenager {
    private:
        vector<string> blackList;
        bool isKillerActive=true;
    
    public:
        ProcessMenager(vector<string>& blackList);

        void startProcessBlocker();

        std::vector<std::pair<std::string, long>> getRunningProcesses();
        bool killBlacklistedProcess();
};