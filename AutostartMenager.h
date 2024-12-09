#include <windows.h>
#include <string>

class AutostartMenager{
    public:
        void baka(const std::string& appName);
        bool IsInStartup(const std::string& appName);
        bool AddToStartup(const std::string& appName, const std::string& filePath);
};