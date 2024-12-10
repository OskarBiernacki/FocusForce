#include <windows.h>
#include <string>
#include <shlobj.h>

class AutostartMenager{
    public:
        bool isInTempFolder(std::string argV0);
        std::string moveToTempFolder();

        bool isInStartup(const std::string& appName);
        bool addToStartup(const std::string& appName, const std::string& filePath);
};