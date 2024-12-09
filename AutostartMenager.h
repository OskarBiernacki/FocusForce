#include <windows.h>
#include <string>
#include <shlobj.h>

class AutostartMenager{
    public:
        bool isInTempFolder();
        void moveToTempFolder();

        bool isInStartup(const std::string& appName);
        bool addToStartup(const std::string& appName, const std::string& filePath);
};